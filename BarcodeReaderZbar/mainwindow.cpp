#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    vector<decodedObject> decodedObjects;

    std::string fn = "/home/karali/image/test11.png";

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
                cv::Mat image = frame(y_rt);

                int down_width = 300;

                int down_height = 200;

                Mat resized_down;
                float sigma =10;
                float sigma2 =0.15f;
                cv::resize(image, resized_down, Size(down_width, down_height), INTER_LINEAR);
                detailEnhance(resized_down,resized_down,sigma,sigma2);

                cv::imshow("ResizedDown",resized_down);
                cv::imshow("Orijinal",image);

                decode(resized_down, decodedObjects);
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

void MainWindow::decode(Mat &im, vector<decodedObject> &decodedObjects)
{
    qDebug()<<"TEST";
    // Create zbar scanner
    ImageScanner scanner;

    // Configure scanner
    //QR enabled
//    scanner.set_config(ZBAR_QRCODE, ZBAR_CFG_ENABLE, 1);

//    scanner.set_config(ZBAR_CODE39, ZBAR_CFG_ENABLE, 1);


    // Convert image to grayscale
    Mat imGray;
    cvtColor(im, imGray,COLOR_BGR2GRAY);

    // Wrap image data in a zbar image
    Image image(im.cols, im.rows, "Y800", (uchar *)imGray.data, im.cols * im.rows);

    // Scan the image for barcodes and QRCodes
    int n = scanner.scan(image);

    // Print results
    for(Image::SymbolIterator symbol = image.symbol_begin(); symbol != image.symbol_end(); ++symbol)
    {
      decodedObject obj;

      obj.type = symbol->get_type_name();
      obj.data = symbol->get_data();

      // Print type and data
      cout << "Type : " << obj.type << endl;
      cout << "Data : " << obj.data << endl << endl;
      decodedObjects.push_back(obj);
    }
}

