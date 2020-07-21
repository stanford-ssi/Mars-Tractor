#ifndef _camera_Included
#define _camera_Included

#include <opencv2/opencv.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/aruco.hpp>
#include <cmath>
#include <vector>
#include <json/json.h>
#include <fstream>

// Namespace for camera functions
namespace cf
{
    /**
     * Camera Constants
     */
    const float MARKER_DIMENSION = .05f; //Square side length of marker in meters

    void createArucoMarkers();
    bool loadCameraCalibration(std::string filename, cv::Mat& cameraMatrix, cv::Mat& distortionCoefficients);
    void locateTarget(const cv::Mat &src, cv::Mat &dst);
    void displayImage(const cv::Mat &img, int delay);
    int capture(const cv::Mat& cameraMatrix, const cv::Mat& distortionCoefficients, float markerDimensions);

    int position(std::vector<std::vector<cv::Point>> targets[3]);
}    // namespace cf

#endif