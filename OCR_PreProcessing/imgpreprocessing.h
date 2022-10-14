#ifndef IMGPREPROCESSING_H
#define IMGPREPROCESSING_H


#include <iostream>
#include <string>
#include <set>
#include <chrono>
#include <mutex>
#include <vector>
#include <fstream>
#include <sstream>
#include <thread>
#include <map>
#include <functional>
#include <algorithm>
#include <random>
#include <iterator>
#include <math.h>

#include <leptonica/allheaders.h>
#include <opencv2/opencv.hpp>
#include "opencv2/core/core.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <tesseract/baseapi.h>


#include <iostream>
#include "opencv2/text.hpp"
#include <opencv2/opencv.hpp>
#include <tesseract/baseapi.h>
//#include <tesseract/strngs.h>

using namespace std;
using namespace cv;
using namespace cv::text;

#include<QDebug>

using namespace std;
using namespace cv;
class ImgPreProcessing
{
public:
    ImgPreProcessing();
    ~ImgPreProcessing();
    void Binarization();
    void skewCorrention();


private:
    Mat colorImg;
    Mat grayImg;

    void deskew(Mat& imgIn, double angle);
    double computeSkewByAreaBox(Mat& imgIn);
    double computeSkewByHoughLines(Mat& imgIn);
    void getContours(Mat& imgIn);
    void rotate_bound(Mat& image, double angle);
    bool isRepetitive(const string& s);
    void er_draw(vector<Mat> &channels, vector<vector<ERStat> > &regions, vector<Vec2i> group, Mat& segmentation);
    std::vector<Mat> extractTableFromImage(Mat src);
    Mat labelPreprocessing(Mat image);
    void endToEndSceneTextDetectionAndRecognition(Mat image);



};

#endif // IMGPREPROCESSING_H
