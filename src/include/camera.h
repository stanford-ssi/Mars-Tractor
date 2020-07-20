#ifndef _camera_Included
#define _camera_Included

#include <opencv2/opencv.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/aruco.hpp>
#include <cmath>

// Namespace for camera functions
namespace cf
{
    void locateTarget(const cv::Mat &src, cv::Mat &dst);
    void displayImage(const cv::Mat &img, int delay);
    struct Position
    {
        int x, y, z;
        int row, theta, psi;
    };

    int position(std::vector<std::vector<cv::Point>> targets[3]);
}    // namespace cf

#endif