#ifndef YUN_H
#define YUN_H

#include <opencv2/opencv.hpp>
#include <opencv2/core/types_c.h>
#include <vector>

#define NUM_ANG  18

namespace iy{
    typedef struct
    {
        int cnt;
        bool isStrong;
    } YunOrientation;

    typedef struct
    {
        cv::Rect roi;
        int max_orientation;
    } YunLabel;

    typedef struct
    {
        cv::Point last_pt, first_pt;
        cv::Rect roi;
        int orientation;
        bool isBarcode;
    } YunCandidate;

    typedef struct
    {
        int magT;
        int winSz;
        int minEdgeT;
        int localBlockSz;
        double minDensityEdgeT;
    } YunParams;

    class Yun{
    private:
        // process parameter
        YunParams pam;

        cv::Mat calc_orientation(cv::Mat &src, cv::Mat &mMap, std::vector<YunOrientation> &Vmap);
        cv::Mat calc_saliency(cv::Mat &src, std::vector<YunOrientation> &Vmap, int lbSz);
        cv::Mat calc_integral_image(cv::Mat &src);
        cv::Mat calc_smooth(cv::Mat &src, int WinSz);
        int push(int *stackx, int *stacky, int arr_size, int vx, int vy, int *top);
        int pop(int *stackx, int *stacky, int arr_size, int *vx, int *vy, int *top);
        std::vector<YunLabel> ccl(cv::Mat &src, cv::Mat &oMap, std::vector<YunOrientation> &Vmap);
        std::vector<YunCandidate> calc_candidate(std::vector<YunLabel> &val, cv::Mat &mMap, cv::Mat &oMap);
        YunCandidate sub_candidate(YunLabel val, cv::Mat &mMap, cv::Mat &oMap);
        YunCandidate calc_region_check(YunCandidate val, cv::Size imSz);

    public:
        Yun() {
            // init value
            pam.magT = 30;
            pam.winSz = 25;
            pam.minEdgeT = 30;
            pam.localBlockSz = 15;
            pam.minDensityEdgeT = 0.3;
        }
        ~Yun() {}

        std::vector<YunCandidate> process(cv::Mat &gray_src);
        std::vector<YunCandidate> process(cv::Mat &gray_src, YunParams pams)
        {
            pam = pams;
            std::vector<YunCandidate> result = process(gray_src);
            return result;
        };
    };
}

#endif // YUN_H
