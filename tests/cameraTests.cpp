/** @file cameraTests.cpp
 * -----------------------------
 * @brief Tests camera functions.
 * @author Bartolone, Kai
 * @date June 2020
 */

#include <gtest/gtest.h>
#include <opencv2/opencv.hpp>
#include "camera.h"

TEST(CameraTest1, returnsPoints)
{
    cv::Mat img = cv::imread("assets/image.jpeg");
    cv::Mat dst;
}