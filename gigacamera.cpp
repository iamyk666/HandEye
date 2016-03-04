#include "gigacamera.h"

GigaCamera::GigaCamera()
{
    //初始化相机运行时环境
    Pylon::PylonAutoInitTerm autoInitTerm;
    try
    {
        //find usable cameras
        CTlFactory& tlFactory = CTlFactory::GetInstance();
        IGigETransportLayer *pTL = dynamic_cast<IGigETransportLayer*>(tlFactory.CreateTl(BaslerGigEDeviceClass));
        if(pTL == NULL)
        {
            throw RUNTIME_EXCEPTION;
        }
        DeviceInfoList_t allDeviceInfos;
        if(pTL->EnumerateDevices(allDeviceInfos) == 0)
        {
            throw RUNTIME_EXCEPTION;
        }
        //将找到的相机放入可用相机数组
        usableDeviceInfos.push_back(allDeviceInfos[0]);
        const String_t subnet(static_cast<const CBaslerGigEDeviceInfo&>(allDeviceInfos[0]).GetSubnetAddress());
        for(size_t i=1;i<allDeviceInfos.size()&&usableDeviceInfos.size()<c_maxCamerasToUse;i++)
        {
            const CBaslerGigEDeviceInfo& gigeinfo=static_cast<const CBaslerGigEDeviceInfo&>(allDeviceInfos[i]);
            if(subnet==gigeinfo.GetSubnetAddress())
            {
                //将找到的可用相机的子网信息放入usableDeviceInfos中
                usableDeviceInfos.push_back(gigeinfo);
            }
            else
            {
                //error info

            }
        }

        cameras(usableDeviceInfos.size());

        for(size_t i=0;i<cameras.GetSize();i++)
        {
            //利用得到的可用相机设别实例化相机，放在cameras中
            cameras[i].Attach(tlFactory.CreateDevice(usableDeviceInfos[i]));
            //cameras[i].RegisterConfiguration(new CActionTriggerConfiguration(DeviceKey,));
            //相机上下文信息，即给相机编号，与获取到的图像信息对应
            cameras[i].SetCameraContext(i);

        }
    }
    catch(GenICam::GenericException &e)
    {
        //异常信息
        qDebug()<<e.GetDescription();

    }

}

GigaCamera::~GigaCamera()
{

}

bool GigaCamera::open()
{
    if(!cameras.IsOpen())
    {
        cameras.Open();
        isGrab = true;
        return true;
    }
}

void GigaCamera::close()
{
    if(cameras.IsOpen())
    {
        isGrab = false;
        cameras.Close();
    }
}

CBaslerGigEGrabResultPtr GigaCamera::getResult()
{
    if(ptrGrabResult->GrabSucceeded())
    {
        return ptrGrabResult;
    }
}

CBaslerGigEDeviceInfo GigaCamera::getCameraInfo(int cameraIndex)
{
    return cameras[cameraIndex].GetDeviceInfo();
}


void GigaCamera::run()
{
    while(isGrab)
    {
        if(cameras.IsOpen())
        {
            if(!cameras.IsGrabbing())
            {
                //相机启动抓取
                cameras.StartGrabbing();
                //获取抓取到的图像
                for(size_t i = 0; i < usableDeviceInfos.size() && cameras.IsGrabbing(); ++i)
                {
                    cameras.RetrieveResult(DefaultTimeout_ms,ptrGrabResult,TimeoutHandling_ThrowException);
                    if(ptrGrabResult->GrabSucceeded())
                    {
                        //图像抓取成功，可以对图像进行操作
                    }
                }
            }

        }
    }
    cameras.StopGrabbing();
}

