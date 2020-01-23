#ifndef CAMWIDGET_H
#define CAMWIDGET_H

#include <QWidget>
#include <QTime>
#include "v4l2cam.h"

typedef struct FPS
{
    FPS():counter(0),value(0) {}

    void start()
    {
        time.start();
        counter = 0;
    }

    void update()
    {
        counter++;
        if(time.elapsed() > 1000)
        {
            value = counter / (time.elapsed()/1000.0f);
            time.start();
            counter = 0;
        }
    }

    QTime time;
    int counter;
    float value;
} FPS;

class CamWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CamWidget(QWidget *parent = 0);
    ~CamWidget();

protected:
    void timerEvent(QTimerEvent*);
    void paintEvent(QPaintEvent*);

private:
    v4l2cam _vcam;
    QImage _image;
    int _timer_id;
    FPS _fps;
    FPS _fps_vcam;
    bool _auto_start_f;

signals:

public slots:
    void start();
    void stop();
    void capture();
};

#endif // CAMWIDGET_H
