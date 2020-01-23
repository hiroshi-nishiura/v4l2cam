#ifndef _V4L2CAM_
#define _V4L2CAM_

//#include <mutex>
#include <linux/videodev2.h>

namespace std { class mutex; }

//tolua_begin
class v4l2cam
{
public:
    v4l2cam();
    virtual ~v4l2cam();

    int open(int w, int h, int req_buffers =3, const char* device =0);
    int close();

    const void* capture(bool async =true);
    const void* yuv2rgb(const void* buffer);

    int width();
    int height();
    unsigned format();
    bool is_opened();

//tolua_end

protected:
    int _fd;
    struct v4l2_buffer _bufferinfo;
    struct v4l2_format _format;

    int _next_queue_id;
    int _num_buffers;
    struct Buffer
    {
        size_t length;
        void* addr;
    } *_buffers;

    size_t _captured_size;
    void* _rgb_buffer;

    int wait_buffer(time_t sec, suseconds_t usec);
    int error(const char* str, ...);

private:
    std::mutex* _mutex_ptr;
//tolua_begin
};
//tolua_end

#endif//_V4L2CAM_
