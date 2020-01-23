#include "camwidget.h"
#include <QPainter>
#include <iostream>

CamWidget::CamWidget(QWidget *parent)
    : QWidget(parent),
      _timer_id(0),
      _auto_start_f(true)
{
}

CamWidget::~CamWidget()
{
    _vcam.close();
}

void CamWidget::timerEvent(QTimerEvent *)
{
    capture();
    repaint();
}

void CamWidget::paintEvent(QPaintEvent*)
{
    if(_auto_start_f)
    {
        _auto_start_f = false;
        start();
    }

    QPainter painter(this);
    painter.fillRect(this->rect(), QColor(0,0,0));

    //draw centered
    QRect rect(_image.rect());
    rect.moveCenter( this->rect().center() );
    painter.drawImage(rect.topLeft(),_image);

    _fps.update();

    QString text;
    text.sprintf("Size(%dx%d) FPS %.1f %.1f",
                 _vcam.width(), _vcam.height(),
                 _fps.value, _fps_vcam.value);

    painter.setPen(QColor(255,0,0));
    painter.drawText(1,height()-1,text);
}

void CamWidget::start()
{
    if(!_vcam.is_opened())
    {
        _vcam.open(width(),height());
        _timer_id = startTimer(0);
        _fps.start();
        _fps_vcam.start();
    }
}

void CamWidget::stop()
{
    if(_vcam.is_opened())
    {
        killTimer(_timer_id);
        _vcam.close();
    }
}

void CamWidget::capture()
{
    if(_vcam.is_opened())
    {
        const void* frame_buf = _vcam.capture();
        if(frame_buf)
        {
            const void* image_buf = _vcam.yuv2rgb(frame_buf);
            QImage image((const uchar*)image_buf, _vcam.width(), _vcam.height(), _vcam.width()*3, QImage::Format_RGB888);

            _image = image.copy();

            _fps_vcam.update();
        }
    }
}
