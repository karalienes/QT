#ifndef OCRPROCESSING_H
#define OCRPROCESSING_H

#include <opencv2/text/ocr.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/dnn.hpp>
#include <cpprest/json.h>
#include <iostream>
#include <string>
#include <iomanip>
#include "decode.h"
#include <QDebug>
#include <tesseract/baseapi.h>

#define TESSDATA_PATH "/home/karali/tessdata/"

using namespace web;
using namespace std;
using namespace cv;
using namespace cv::dnn;
using namespace cv::text;

class OCRProcessing
{
public:
    OCRProcessing();

    const string keys =
        "{ input i     | | Path to input image or video file. Skip this argument to capture frames from a camera.}"
        "{ model m     | | Path to a binary .pb file contains trained network.}"
        "{ detect d     | | to detect word or line.}"
        "{ width       | 800 | Preprocess input image by resizing to a specific width. It should be multiple by 32. }"
        "{ height      | 800 | Preprocess input image by resizing to a specific height. It should be multiple by 32. }"
        "{ thr         | 0.6 | Confidence threshold. }"
        "{ nms         | 0.4 | Non-maximum suppression threshold. }";

    struct Triplets
    {
        long unsigned int idx;
        vector<RotatedRect> box;
        vector<int> ind;
    };
    struct RotatedStruct{
        int angle;
        int detectionboxcounter;
    };
    RotatedStruct rotateddata[36];
    int angle =0;
    int detectioncounter =0;
    Decode *decodeobj;
    void rotatedImgProcessing();
    void dataImgProcessing(int i, Mat img);
};

#endif // OCRPROCESSING_H
