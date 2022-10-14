#ifndef DECODE_H
#define DECODE_H

#include <opencv2/imgproc.hpp>
#include <iostream>
#include <QDebug>

using namespace std;
using namespace cv;

class Decode
{
public:
    Decode();
    static void decode(const Mat &scores, const Mat &geometry, float scoreThresh,
                vector<RotatedRect> &detections, vector<vector<RotatedRect>> &line_detections,
                vector<float> &confidences, vector<vector<float>> &box_confidences);
};

#endif // DECODE_H
