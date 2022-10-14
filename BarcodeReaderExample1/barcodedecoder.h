#ifndef BARCODEDECODER_H
#define BARCODEDECODER_H

#include <leptonica/allheaders.h>
#include <opencv2/opencv.hpp>
#include "opencv2/core/core.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <tesseract/baseapi.h>
#include "opencv2/text.hpp"
#include <iostream>
#include <QMap>
#include <QVariant>

using namespace std;
using namespace cv;

class BarcodeDecoder
{
public:
    #define SPACE 0
    #define BAR 255
    #define Ob(x)  ((unsigned)Ob_(0 ## x ## uL))
    #define Ob_(x) (x & 1 | x >> 2 & 2 | x >> 4 & 4 | x >> 6 & 8 |		\
    x >> 8 & 16 | x >> 10 & 32 | x >> 12 & 64 | x >> 14 & 128)
    typedef std::map<unsigned, char> pattern_map;
    BarcodeDecoder();
    void setup_map(pattern_map& table);
    void align_boundary(const Mat &img, cv::Point& cur, int begin, int end);

};

#endif // BARCODEDECODER_H
