#ifndef IMAGEGRABBER_H
#define IMAGEGRABBER_H

#include <QThread>


/*图像抓取操作类*/
/*实现不同种类相机的抓取图像操作*/

class ImageGrabber : public QThread
{
    Q_OBJECT
public:
    ImageGrabber();
    ~ImageGrabber();
};

#endif // IMAGEGRABBER_H
