#ifndef CAMERA_H
#define CAMERA_H

#include <QThread>
#include <QSize>

/*相机类*/

class Camera
{
public:
    Camera(){}
    virtual ~Camera(){}

    virtual bool open()=0;
    virtual void close()=0;
    virtual bool isOpen()=0;
    virtual bool startCapture(){return true;}
    virtual bool stopCapture(){return true;}

    virtual QSize getImageSize()=0;

};

#endif // CAMERA_H
