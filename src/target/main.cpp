/** @file main.cpp
 * -----------------------------
 * @brief Main function.
 * @author Bartolone, Kai
 * @date May 2020
 *
 * This file determines autonomous functionality or controlled functionality of the Mars tractor.
 */

#include <camera.hpp>
//#include "dualshock.h"
#include <iostream>
#include <opencv2/aruco.hpp>
#include <opencv2/opencv.hpp>
#include <server.hpp>

using namespace std;
using namespace cv;
using namespace cf;

int main()
{
    /** Load Camera Matrix and Distortion Coeffs */
    Mat cameraMatrix, distCoeffs;
    if (!loadCameraCalibration("assets/config/C920_Calibration.json", cameraMatrix, distCoeffs))
        return -1;

    /** Video Capture */
    cv::Mat frame;

    cv::VideoCapture cap(0);
    cv::namedWindow("Camera", cv::WINDOW_NORMAL);

    if (!cap.isOpened())
    {
        std::cerr << "Camera cannot be found." << std::endl;
        return -1;
    }

    bool isRead = cap.read(frame);
    if (!isRead) std::cerr << "Camera cannot be read." << std::endl;

    std::vector<int> markerIds = {7};
    std::vector<std::vector<cv::Point2f>> markerCorners;
    cv::Ptr<cv::aruco::Dictionary> markerDictionary =
        cv::aruco::getPredefinedDictionary(cv::aruco::PREDEFINED_DICTIONARY_NAME::DICT_4X4_50);
    std::vector<cv::Vec3d> rvecs, tvecs;

    while (1)
    {
        // Capture frame-by-frame
        isRead = cap.read(frame);
        if (!isRead) break;

        cv::aruco::detectMarkers(frame, markerDictionary, markerCorners, markerIds);
        cv::aruco::estimatePoseSingleMarkers(markerCorners, MARKER_DIMENSION, cameraMatrix,
                                             distCoeffs, rvecs, tvecs);
        for (int i = 0; i < markerIds.size(); i++)
        {
            cv::aruco::drawAxis(frame, cameraMatrix, distCoeffs, rvecs[i], tvecs[i], 0.1f);
            cf::displayPosition(frame, tvecs[i], rvecs[i]);
        }
        cv::imshow("Camera", frame);
        if (cv::waitKey(30) >= 0) break;
    }

    cap.release();
    cv::destroyAllWindows();

    return 0;
}
// Mat frame;

// VideoCapture cap(0);

// if (!cap.isOpened())
// {
//     cerr << "Camera cannot be found." << endl;
//     return -1;
// }
// namedWindow("Camera", WINDOW_AUTOSIZE);

// vector<Vec3d> rvecs, tvecs;
// vector<Point2f> targetCorners;

// bool isRead = cap.read(frame);
// if (!isRead) cerr << "Camera cannot be read." << endl;

// while (1)
// {
//     // Capture frame-by-frame
//     isRead = cap.read(frame);
//     if (!isRead) break;

//     cf::detectTarget(frame, targetCorners);
//     // cv::imshow("Camera", frame);
//     // if (cv::waitKey(30) >= 0) break;
// }

// cap.release();
// cv::destroyAllWindows();
