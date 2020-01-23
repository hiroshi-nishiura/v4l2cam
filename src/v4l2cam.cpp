#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>

#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>		/* low-level i/o */
#include <sys/mman.h>
#include <sys/ioctl.h>

#include <mutex>

#include "v4l2cam.h"

v4l2cam::v4l2cam()
    :_fd(0),_rgb_buffer(0)
{
    _mutex_ptr = new std::mutex;
}
v4l2cam::~v4l2cam()
{
    close();
    delete _mutex_ptr;
}

int v4l2cam::error(const char* str, ...)
{
    va_list ap;
    va_start(ap,str);
    vfprintf(stderr,str,ap);
    va_end(ap);
    fprintf(stderr,"\n");
    
    if(_fd>0) ::close(_fd);
    return 0;
}

int v4l2cam::wait_buffer(time_t sec, suseconds_t usec)
{
    // wait until buffer ready
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(_fd, &fds);

    // timeout
    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 0;

    return select(_fd + 1, &fds, NULL, NULL, &tv);
}

int v4l2cam::open(int w, int h, int req_buffers, const char* device)
{
    std::lock_guard<std::mutex> lock(*_mutex_ptr);

    if(_fd>0)
        error("already opened device\n");
    if(!device)
        device = "/dev/video0";
  
    _fd = ::open(device,O_RDWR);
    if(_fd<=0)
        return error("can not open device: %s\n",device);

    // Retrieve the device's capabilities
    struct v4l2_capability cap;
    if(ioctl(_fd, VIDIOC_QUERYCAP, &cap) < 0)
        return error("error VIDIOC_QUERYCAP");
    if(!(cap.capabilities & V4L2_CAP_VIDEO_CAPTURE))
        return error("error V4L2_CAP_VIDEO_CAPTURE");

    // Choose formats
    struct v4l2_fmtdesc fmtdesc;
    memset(&fmtdesc,0,sizeof(fmtdesc));
    fmtdesc.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    while(ioctl(_fd, VIDIOC_ENUM_FMT, &fmtdesc)==0)
    {
        if(fmtdesc.pixelformat == V4L2_PIX_FMT_YUYV)
            break; // accept
        else
            fmtdesc.index++;
    }
    
    // video format
    memset(&_format,0,sizeof(_format));
    _format.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    _format.fmt.pix.width = w;
    _format.fmt.pix.height = h;
    _format.fmt.pix.pixelformat = fmtdesc.pixelformat;
    _format.fmt.pix.field = V4L2_FIELD_NONE;

    if(ioctl(_fd, VIDIOC_S_FMT, &_format) < 0 || _format.fmt.pix.pixelformat != fmtdesc.pixelformat)
        return error("error VIDIOC_S_FMT");
        
    // request buffer
    struct v4l2_requestbuffers bufrequest;
    bufrequest.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    bufrequest.memory = V4L2_MEMORY_MMAP;
    bufrequest.count = req_buffers;

    if(ioctl(_fd, VIDIOC_REQBUFS, &bufrequest) < 0)
        return error("error VIDIOC_REQBUFS");

    _num_buffers = bufrequest.count;
    printf("buffer count=%d\n", _num_buffers);

    // Allocate buffers
    _buffers = (Buffer*)calloc(_num_buffers, sizeof(*_buffers));
    //
    for(int i=0; i<_num_buffers; i++)
    {
        memset(&_bufferinfo, 0, sizeof(_bufferinfo));
        _bufferinfo.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        _bufferinfo.memory = V4L2_MEMORY_MMAP;
        _bufferinfo.index = i;

        if(ioctl(_fd, VIDIOC_QUERYBUF, &_bufferinfo) < 0)
            return error("error VIDIOC_QUERYBUF");

        // mmap
        _buffers[i].addr = mmap(NULL,
                                _bufferinfo.length,
                                PROT_READ | PROT_WRITE, MAP_SHARED,
                                _fd, _bufferinfo.m.offset);
        if(_buffers[i].addr == MAP_FAILED)
            return error("error MAP_FAILED");

        _buffers[i].length = _bufferinfo.length;
        memset(_buffers[i].addr, 0, _bufferinfo.length);

        // queue
        if(ioctl(_fd, VIDIOC_QBUF, &_bufferinfo) < 0)
            return error("error VIDIOC_QBUF");
    }

    // start streaming
    if(ioctl(_fd, VIDIOC_STREAMON, &_bufferinfo.type) < 0)
        return error("error VIDIOC_STREAMON");

    // pre read frame
    if(wait_buffer(2,0)<0)
    {
        return error("error wait_buffer");
    }
    if(ioctl(_fd, VIDIOC_DQBUF, &_bufferinfo) < 0)
        return error("error VIDIOC_DQBUF");

    _next_queue_id = _bufferinfo.index;

    return 1;
}

int v4l2cam::close()
{
    std::lock_guard<std::mutex> lock(*_mutex_ptr);

    if(_fd>0)
    {
        // stop streaming
        if(ioctl(_fd, VIDIOC_STREAMOFF, &_bufferinfo.type) < 0)
            return error("error VIDIOC_STREAMOFF");
        ::close(_fd);
        _fd = 0;

        if(_buffers)
        {
            for(int i=0; i<_num_buffers; i++)
            {
                munmap(_buffers[i].addr, _buffers[i].length);
            }
            free(_buffers);
            _buffers = 0;
        }
        if(_rgb_buffer)
        {
            free(_rgb_buffer);
            _rgb_buffer = 0;
        }
    }
    return 1;
}

const void* v4l2cam::capture(bool async)
{
    std::lock_guard<std::mutex> lock(*_mutex_ptr);

    if(async && wait_buffer(0,0)==0)
    {
        return 0; // not yet
    }

    // Dequeue
    if(ioctl(_fd, VIDIOC_DQBUF, &_bufferinfo) < 0)
    {
        error("error VIDIOC_DQBUF");
        return 0;
    }
    //printf("DQ:%d Q:%d\n", _bufferinfo.index, _next_queue_id);

    void* addr = _buffers[_bufferinfo.index].addr;
    _captured_size = _bufferinfo.bytesused;

    // Queue
    _bufferinfo.index = _next_queue_id;
    if(ioctl(_fd, VIDIOC_QBUF, &_bufferinfo) < 0)
    {
        error("error VIDIOC_QBUF");
        return 0;
    }

    _next_queue_id = (_next_queue_id + 1) % _num_buffers;

    return addr;
}

int v4l2cam::width()
{
    return (int)_format.fmt.pix.width;
}
    
int v4l2cam::height()
{
    return (int)_format.fmt.pix.height;
}
    
unsigned v4l2cam::format()
{
    return _format.fmt.pix.pixelformat;
}
bool v4l2cam::is_opened()
{
    return _fd>0;
}

// Color space conversion for RGB
#define R(y,u,v) ((298*y+409*v+128)>>8)
#define G(y,u,v) ((298*y-100*u-208*v+128)>>8)
#define B(y,u,v) ((298*y+516*u+128)>>8)
#define CLAMP(t) (((t)>255)?255:(((t)<0)?0:(t)))

const void* v4l2cam::yuv2rgb(const void* yuv_buffer)
{
    if(!yuv_buffer) return 0;
    if(!_rgb_buffer) _rgb_buffer = malloc(3 * width() * height());

    unsigned char* src = (unsigned char*)yuv_buffer;
    unsigned char* dst = (unsigned char*)_rgb_buffer;
        
    for(unsigned i = 0; i<_captured_size/4; i++)
    {
        int y0 = *src++ - 16;
        int u = *src++ - 128;
        int y1 = *src++ - 16;
        int v = *src++ - 128;

        *dst++ = CLAMP(R(y0, u, v));
        *dst++ = CLAMP(G(y0, u, v));
        *dst++ = CLAMP(B(y0, u, v));

        *dst++ = CLAMP(R(y1, u, v));
        *dst++ = CLAMP(G(y1, u, v));
        *dst++ = CLAMP(B(y1, u, v));
    }

    return _rgb_buffer;
}
