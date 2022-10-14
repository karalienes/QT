#include "mainwindow.h"
#include "ui_mainwindow.h"

#define saveImages 1
//定义是否记录视频
#define recordVideo 1

// 加载OpenCV API
#include <opencv4/opencv2/core.hpp>
#include <opencv4/opencv2/highgui/highgui.hpp>
#include <opencv4/opencv2/video/video.hpp>

//加载PYLON API.
#include <pylon/PylonIncludes.h>

#include<iostream>

#ifdef PYLON_WIN_BUILD
#include <pylon/PylonGUI.h>
#endif

//命名空间.
using namespace Pylon;
using namespace std;
//定义抓取的图像数
static const uint32_t c_countOfImagesToGrab = 10;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    //Pylon自动初始化和终止
    Pylon::PylonAutoInitTerm autoInitTerm;
    try
    {
        //创建相机对象（以最先识别的相机）
        CInstantCamera camera(CTlFactory::GetInstance().CreateFirstDevice());
        // 打印相机的名称
        std::cout << "Using device " << camera.GetDeviceInfo().GetModelName() << endl;
        //获取相机节点映射以获得相机参数
        GenApi::INodeMap& nodemap = camera.GetNodeMap();
        //打开相机
        camera.Open();
        //获取相机成像宽度和高度
        GenApi::CIntegerPtr width = nodemap.GetNode("Width");
        GenApi::CIntegerPtr height = nodemap.GetNode("Height");

        //设置相机最大缓冲区,默认为10
        camera.MaxNumBuffer = 5;
        // 新建pylon ImageFormatConverter对象.
        CImageFormatConverter formatConverter;
        //确定输出像素格式
        formatConverter.OutputPixelFormat = PixelType_BGR8packed;
        // 创建一个Pylonlmage后续将用来创建OpenCV images
        CPylonImage pylonImage;

        //声明一个整形变量用来计数抓取的图像，以及创建文件名索引
        int grabbedlmages = 0;

        // 新建一个OpenCV video creator对象.
        CVideoWriter cvVideoCreator;
        //新建一个OpenCV image对象.

        cv::Mat openCvImage;
        // 视频文件名

        std::string videoFileName = "openCvVideo.avi";
        // 定义视频帧大小
        cv::Size frameSize = cv::Size((int)width->GetValue(), (int)height->GetValue());

        //设置视频编码类型和帧率，有三种选择
        // 帧率必须小于等于相机成像帧率
//        cvVideoCreator.open(videoFileName);
        //cvVideoCreator.open(videoFileName, CV_F0URCC('M','P',,4','2’), 20, frameSize, true);
        //cvVideoCreator.open(videoFileName, CV_FOURCC('M', '3', 'P', 'G'), 20, frameSize, true);


        // 开始抓取c_countOfImagesToGrab images.
        //相机默认设置连续抓取模式
        camera.StartGrabbing(c_countOfImagesToGrab, GrabStrategy_LatestImageOnly);

        //抓取结果数据指针
        CGrabResultPtr ptrGrabResult;

        // 当c_countOfImagesToGrab images获取恢复成功时，Camera.StopGrabbing()
        //被RetrieveResult()方法自动调用停止抓取

        while (camera.IsGrabbing())

        {
            // 等待接收和恢复图像，超时时间设置为5000 ms.
            camera.RetrieveResult(5000, ptrGrabResult, TimeoutHandling_ThrowException);

            //如果图像抓取成功
            if (ptrGrabResult->GrabSucceeded())
            {
                // 获取图像数据
                cout <<"SizeX: "<<ptrGrabResult->GetWidth()<<endl;
                cout <<"SizeY: "<<ptrGrabResult->GetHeight()<<endl;

                //将抓取的缓冲数据转化成pylon image.
                formatConverter.Convert(pylonImage, ptrGrabResult);

                // 将 pylon image转成OpenCV image.
                openCvImage = cv::Mat(ptrGrabResult->GetHeight(), ptrGrabResult->GetWidth(), CV_8UC3, (uint8_t *) pylonImage.GetBuffer());

                //如果需要保存图片
                if (saveImages)
                {
                   std::ostringstream s;
                    // 按索引定义文件名存储图片
                   s << "image_" << grabbedlmages << ".jpg";
                   std::string imageName(s.str());
                    //保存OpenCV image.
                   imwrite(imageName, openCvImage);
                   grabbedlmages++;
                }

                //如果需要记录视频
                if (recordVideo)
                {

//                    cvVideoCreator.write(openCvImage);
                }

                //新建OpenCV display window.
                namedWindow("OpenCV Display Window", cv::WINDOW_NORMAL); // other options: CV_AUTOSIZE, CV_FREERATIO
                //显示及时影像.
                imshow("OpenCV Display Window", openCvImage);

                // Define a timeout for customer's input in
                // '0' means indefinite, i.e. the next image will be displayed after closing the window.
                // '1' means live stream
                cv::waitKey(0);

            }

        }

    }
    catch (GenICam::GenericException &e)
    {
        // Error handling.
        cerr << "An exception occurred." << endl
            << e.GetDescription() << endl;
    }
    return;
}

MainWindow::~MainWindow()
{
    delete ui;
}

