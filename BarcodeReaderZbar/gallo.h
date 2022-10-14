#ifndef GALLO_H
#define GALLO_H


#include <opencv2/opencv.hpp>

namespace iy{
    class Gallo {
    private:
        cv::Mat calc_gradient(cv::Mat &src);
        cv::Mat calc_integral_image(cv::Mat &src);
        cv::Point find_max_point_with_smooth(cv::Mat &src, cv::Mat &smooth_map, int WinSz);
        cv::Rect box_detection(cv::Mat &src, cv::Point cp);
    public:
        Gallo(){}
        ~Gallo(){}

        cv::Rect process(cv::Mat &gray_src, int WinSz = 20);
    };
};

#endif // GALLO_H
