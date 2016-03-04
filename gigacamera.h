#ifndef GIGACAMERA_H
#define GIGACAMERA_H

#include <pylon/PylonIncludes.h>
#include <pylon/gige/PylonGigEIncludes.h>
#include <QDebug>

using namespace Pylon;
//using namespace GenApi;

class GigaCamera
{
public:
    GigaCamera();
    ~GigaCamera();

    bool open();
    void close();
    bool startCapture();
    bool stopCapture();

    CBaslerGigEGrabResultPtr getResult();
    CBaslerGigEDeviceInfo getCameraInfo(int cameraIndex);

protected:
    void run();
private:

    //gigaE相机数组
    CBaslerGigEInstantCameraArray cameras;
    //可用相机设备信息
    DeviceInfoList_t usableDeviceInfos;
    CImageFormatConverter formatConverter;
    //GigE相机抓取结果
    CBaslerGigEGrabResultPtr ptrGrabResult;

    static const uint32_t c_maxCamerasToUse = 2;
    //默认超时时间
    const int DefaultTimeout_ms = 5000;

    bool isGrab;

};

#endif // GIGACAMERA_H
