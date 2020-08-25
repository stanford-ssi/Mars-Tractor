/** @file cameraTests.cpp
 * -----------------------------
 * @brief Tests camera functions.
 * @author Bartolone, Kai
 * @date June 2020
 */

#include <gtest/gtest.h>
#include <opencv2/opencv.hpp>
#include <camera.hpp>

TEST(camera_calibration, regression)
{
    cv::Mat img = cv::imread("assets/image.jpeg");
    cv::Mat dst;
}

TEST(CameraTests, returnsPoints)
{
    cv::Mat img = cv::imread("assets/image.jpeg");
    cv::Mat dst;
    cf::locateTarget(img, dst);
}
