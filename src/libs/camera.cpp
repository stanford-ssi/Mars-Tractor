#include "camera.h"

void cf::locateTarget(const cv::Mat &src, cv::Mat &dst)
{
    cv::Mat grey;
    cv::cvtColor(src, grey, cv::COLOR_BGR2GRAY);
    // cf::displayImage(grey, 3);

    cv::Mat blur;
    cv::GaussianBlur(grey, blur, cv::Size(5, 5), 0, 0);
    // cf::displayImage(blur, 3);

    cv::Mat bin;
    double threshold = 50;
    cv::threshold(blur, bin, threshold, 255, cv::THRESH_BINARY);
    cf::displayImage(bin, 0);

    cv::Mat contours;
    cv::findContours(bin, contours, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);
    cf::displayImage(contours, 0);

    cv::Scalar color = cv::Scalar(0, 255, 0);
    cv::drawContours(contours, dst, cv::CHAIN_APPROX_SIMPLE, color);
    cf::displayImage(dst, 3);
}

void cf::displayImage(const cv::Mat &img, int delay)
{
    cv::namedWindow("image", cv::WINDOW_AUTOSIZE);
    cv::imshow("image", img);
    cv::waitKey(delay * 1000);
}

int cf::position(std::vector<std::vector<cv::Point>> targets[3])
{
    for (int i = 0; i < 3; i++)
    {
        targets[i];
    }
    return 0;
}