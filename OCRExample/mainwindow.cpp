#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ocr.h"
#include <leptonica/allheaders.h>
#define TESSDATA_PATH "/home/karali/QT_CodeExample/OCRExample/testdata"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    Ocr *deneme = new Ocr(this);
//    Mat image =imread("/home/karali/image/OCR/karali20-Tem-22-09-19-53-789000000ÖÖ.png");
//    imwrite("/home/karali/test.png",image);
//    QString deneme2 = "enes";

//    deneme->getText(deneme2,image);
//    deneme();
    deneme2();
//      deneme3();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::deneme()
{
    // initilize tesseract OCR engine
    tesseract::TessBaseAPI *myOCR =
      new tesseract::TessBaseAPI();

    printf("Tesseract-ocr version: %s\n",
           myOCR->Version());
    // printf("Leptonica version: %s\n",
    //        getLeptonicaVersion());

    if (myOCR->Init(TESSDATA_PATH, "eng")) {
      fprintf(stderr, "Could not initialize tesseract.\n");
      exit(1);
    }

    tesseract::PageSegMode pagesegmode = static_cast<tesseract::PageSegMode>(7); // treat the image as a single text line
    myOCR->SetPageSegMode(pagesegmode);

    // read iamge
    namedWindow("tesseract-opencv", 0);
    Mat image = imread("/home/karali/tesseractimg.jpg", 0);

    // set region of interest (ROI), i.e. regions that contain text
    Rect text1ROI(400, 400, 150 ,70);
    Rect text2ROI(0, 0, image.cols, image.rows);

    // recognize text
    myOCR->TesseractRect( image.data, 1, image.step1(), text1ROI.x, text1ROI.y, text1ROI.width, text1ROI.height);
    const char *text1 = myOCR->GetUTF8Text();

    myOCR->TesseractRect( image.data, 1, image.step1(), text2ROI.x, text2ROI.y, text2ROI.width, text2ROI.height);
    const char *text2 = myOCR->GetUTF8Text();

    // remove "newline"
    String t1(text1);

    t1.erase(std::remove(t1.begin(), t1.end(), '\n'), t1.end());

    String t2(text2);
    t2.erase(std::remove(t2.begin(), t2.end(), '\n'), t2.end());

    // print found text
    printf("found text1: \n");
    printf("%s", t1.c_str());
    printf("\n");

    printf("found text2: \n");
    printf("%s", t2.c_str());
    printf("\n");

    // draw text on original image
    Mat scratch = imread("/home/karali/tesseractimg.jpg");

    int fontFace = FONT_HERSHEY_PLAIN;
    double fontScale = 2;
    int thickness = 2;
    putText(scratch, t1, Point(text1ROI.x, text1ROI.y), fontFace, fontScale, Scalar(0, 255, 0), thickness, 8);
    putText(scratch, t2, Point(text2ROI.x, text2ROI.y), fontFace, fontScale, Scalar(0, 255, 0), thickness, 8);

    rectangle(scratch, text1ROI, Scalar(0, 0, 255), 2, 8, 0);
    rectangle(scratch, text2ROI, Scalar(0, 0, 255), 2, 8, 0);

    imshow("tesseract-opencv", scratch);
    waitKey(0);

    delete [] text1;
    delete [] text2;

    // destroy tesseract OCR engine
    myOCR->Clear();
    myOCR->End();




}

void MainWindow::deneme2()
{
    Mat colorImg = imread("/home/karali/image/TestOCR/of.png");
    Mat grayImg;
    Mat gausssianImg;
    cvtColor(colorImg,grayImg,COLOR_BGR2GRAY);
    threshold(colorImg,grayImg,0,255,0);
    cvtColor(colorImg, colorImg, COLOR_RGBA2GRAY, 0);
    GaussianBlur(colorImg,gausssianImg,Size(5,5),0,0,BORDER_DEFAULT);
    adaptiveThreshold(gausssianImg,grayImg,125,ADAPTIVE_THRESH_GAUSSIAN_C,THRESH_BINARY,11,12);

    imshow("Gray",grayImg);



    Mat img;
    colorImg.copyTo(img);
    Size size(3,3);
    cvtColor(img,img, COLOR_RGBA2GRAY, 0);
    GaussianBlur(img,img,size,0);
    adaptiveThreshold(img, img, 0, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY_INV, 55, 10);
    bitwise_not(img,img);

    imshow("getcountours",img);


    Mat img2 = img.clone();

    vector<cv::Point> points;
    Mat_<uchar>::iterator it = img.begin<uchar>();
    Mat_<uchar>::iterator end = img.end<uchar>();

    for(; it!=end;++it){
        if(*it){
            points.push_back(it.pos());
        }
    }

    RotatedRect box = minAreaRect(Mat(points));

    double angle = box.angle;

    if(angle<-45.){
        angle+=90.;
    }

    Point2f vertices[4];
    box.points(vertices);

    for(int i=0;i<4;++i){
        line(img, vertices[i], vertices[(i + 1) % 4],Scalar(255, 0, 0), 1, LINE_8);
    }

    imshow("Line",img);


    cv::Mat rot_mat = cv::getRotationMatrix2D(box.center, angle, 1);

    cv::Mat rotated;
    cv::warpAffine(img2, rotated, rot_mat, img.size(), cv::INTER_CUBIC);


    cv::imshow("rotated", rotated);

    qDebug()<<rotated.data[307209]<<"karali";
    qDebug()<<rotated.cols<<"karali2";
    qDebug()<<rotated.rows<<"karali3";


    char *outText;

    tesseract::TessBaseAPI *api = new tesseract::TessBaseAPI();
    // Initialize tesseract-ocr with English, without specifying tessdata path
    if (api->Init(TESSDATA_PATH, "tur")) {
        fprintf(stderr, "Could not initialize tesseract.\n");
        exit(1);
    }

    // Open input image with leptonica library

    api->SetImage(rotated.data, rotated.cols, rotated.rows, 4, 4*rotated.cols);
    // Get OCR result
    outText = api->GetUNLVText();
    printf("OCR output:\n%s", outText);

    // Destroy used object and release memory
    api->End();
    delete api;
    delete [] outText;
//    pixDestroy(&image);


}

void MainWindow::deneme3()
{
    tesseract::TessBaseAPI *api = new tesseract::TessBaseAPI();
    // Initialize tesseract-ocr with English, without specifying tessdata path
        if (api->Init(TESSDATA_PATH, "tur")) {
            fprintf(stderr, "Could not initialize tesseract.\n");
            exit(1);
        }
    // Open input image with leptonica library
      Pix *image = pixRead("/home/karali/image/TestOCR/test.png");
      api->SetImage(image);
    // Set lstm_choice_mode to alternative symbol choices per character, bbox is at word level.
      api->SetVariable("lstm_choice_mode", "2");
      api->Recognize(0);
      tesseract::PageIteratorLevel level = tesseract::RIL_WORD;
      tesseract::ResultIterator* res_it = api->GetIterator();
    // Get confidence level for alternative symbol choices. Code is based on
    // https://github.com/tesseract-ocr/tesseract/blob/main/src/api/hocrrenderer.cpp#L325-L344
      std::vector<std::vector<std::pair<const char*, float>>>* choiceMap = nullptr;
      if (res_it != 0) {
        do {
          const char* word;
          float conf;
          int x1, y1, x2, y2, tcnt = 1, gcnt = 1, wcnt = 0;
         res_it->BoundingBox(level, &x1, &y1, &x2, &y2);
         choiceMap = res_it->GetBestLSTMSymbolChoices();
          for (auto timestep : *choiceMap) {
            if (timestep.size() > 0) {
              for (auto & j : timestep) {
                conf = int(j.second * 100);
                word =  j.first;
                printf("%d  symbol: '%s';  \tconf: %.2f; BoundingBox: %d,%d,%d,%d;\n",
                            wcnt, word, conf, x1, y1, x2, y2);
               gcnt++;
              }
              tcnt++;
            }
          wcnt++;
          printf("\n");
          }
        } while (res_it->Next(level));
      }
    // Destroy used object and release memory
        api->End();
        pixDestroy(&image);


}

