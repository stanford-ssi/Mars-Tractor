#include <gtest/gtest.h>
#include "camera.h"

TEST(gtest, check)
{
    bool thing = false;
    ASSERT_FALSE(thing);
}

TEST(CameraTests, returnsPoints)
{
    cv::Mat img = cv::imread("assets/image.jpeg");
    cv::Mat dst;
    cf::locateTarget(img, dst);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}