#ifndef ROTATEDCLASS_H
#define ROTATEDCLASS_H

#include <opencv2/text/ocr.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/dnn.hpp>
#include <cpprest/json.h>
#include <iostream>
#include <string>
#include <iomanip>
#include <QDebug>
#include <tesseract/baseapi.h>

using namespace cv;
class RotatedClass
{
public:
    RotatedClass();
    void rotatedImgProcessing();
};

#endif // ROTATEDCLASS_H
