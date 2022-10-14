#ifndef SOROS_H
#define SOROS_H


#include <opencv2/opencv.hpp>

namespace iy{
    class Soros {
    private:
        cv::Mat SaliencyMapbyAndoMatrix(cv::Mat &src, bool is1D = true);
        cv::Mat calc_integral_image(cv::Mat &src);
        cv::Point find_max_point_with_smooth(cv::Mat &src, cv::Mat &smooth_map, int WinSz = 20);
        cv::Rect box_detection(cv::Mat &src, cv::Point cp);
    public:
        Soros() {}
        ~Soros() {}

        cv::Rect process(cv::Mat &gray_src, bool is1D = true, int WinSz = 20);
    };
}

#endif // SOROS_H
