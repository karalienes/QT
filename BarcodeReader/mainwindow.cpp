#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    std::string fn = "/home/karali/image/logi1.png";

    iy::Gallo mGallo;
    iy::Soros mSoros;
    iy::Yun mYun;

    cv::Mat frame_gray;
    cv::Mat frame = cv::imread(fn.c_str());

    if(frame.data == NULL) {
        std::cerr << "error! read image" << std::endl;
        return ;
    }

    cv::cvtColor(frame, frame_gray, cv::COLOR_RGBA2GRAY);

    cv::Rect g_rt = mGallo.process(frame_gray, 20);
    cv::rectangle(frame, g_rt, cvScalar(0, 255, 0), 2);

    cv::Rect s_rt = mSoros.process(frame_gray, 20);
    cv::rectangle(frame, s_rt, cvScalar(255,0,0), 2);

    std::vector<iy::YunCandidate> list_barcode = mYun.process(frame_gray);
    if (!list_barcode.empty())
    {
        for (std::vector<iy::YunCandidate>::iterator it = list_barcode.begin(); it < list_barcode.end(); it++)
        {
            if (it->isBarcode)
            {
                cv::Rect y_rt = it->roi;
                cv::rectangle(frame, y_rt, cvScalar(0, 255, 255), 2);
                imshow("Deneme",frame(y_rt));

            }
        }

        list_barcode.clear();
    }

    cv::imshow("frame", frame);
    cv::waitKey(0);

    cv::destroyAllWindows();

}

MainWindow::~MainWindow()
{
    delete ui;
}

