#ifndef _camera_Included
#define _camera_Included

#include <opencv2/opencv.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/aruco.hpp>
#include <cmath>
#include <vector>
#include <json/value.h>

// Namespace for camera functions
namespace cf
{
    /**
     * Camera Constants
     */
    const cv::Mat CAMERA_MATRIX_C920;
    const cv::Mat DISTORTION_COEFFS_C920;
    //const float MARKER_DIMENSION;

    void createArucoMarkers();
    bool loadCameraCalibration(std::string filename, cv::Mat& cameraMatrix, cv::Mat& distortionCoefficients);)
    void locateTarget(const cv::Mat &src, cv::Mat &dst);
    void displayImage(const cv::Mat &img, int delay);
    int video();
    struct Position
    {
        int x, y, z;
        int row, theta, psi;
    };

    int position(std::vector<std::vector<cv::Point>> targets[3]);
}    // namespace cf

#endif