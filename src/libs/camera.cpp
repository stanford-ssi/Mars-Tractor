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

int cf::capture(const cv::Mat &cameraMatrix, const cv::Mat &distortionCoefficients,
                float markerDimensions)
{
    cv::Mat frame;
    std::vector<int> markerIds = {7};

    std::vector<std::vector<cv::Point2f>> markerCorners, rejects;
    cv::aruco::DetectorParameters parameters;

    cv::Ptr<cv::aruco::Dictionary> markerDictionary =
        cv::aruco::getPredefinedDictionary(cv::aruco::PREDEFINED_DICTIONARY_NAME::DICT_4X4_50);

    cv::VideoCapture cap(0);

    if (!cap.isOpened())
    {
        std::cerr << "Camera cannot be found." << std::endl;
        return -1;
    }
    cv::namedWindow("Camera", cv::WINDOW_AUTOSIZE);

    std::vector<cv::Vec3d> rotationVectors, translationVectors;

    bool isRead = cap.read(frame);
    if (!isRead) std::cerr << "Camera cannot be read." << std::endl;

    while (1)
    {
        // Capture frame-by-frame
        isRead = cap.read(frame);
        if (!isRead) break;

        cv::aruco::detectMarkers(frame, markerDictionary, markerCorners, markerIds);
        cv::aruco::estimatePoseSingleMarkers(markerCorners, markerDimensions, cameraMatrix,
                                             distortionCoefficients, rotationVectors,
                                             translationVectors);
        for (int i = 0; i < markerIds.size(); i++)
        {
            cv::aruco::drawAxis(frame, cameraMatrix, distortionCoefficients, rotationVectors[i],
                                translationVectors[i], 0.1f);
        }
        cv::imshow("Camera", frame);
        if (cv::waitKey(30) >= 0) break;
    }

    cap.release();
    cv::destroyAllWindows();

    return 0;
}

void cf::createArucoMarkers()
{
    cv::Mat outputMarker;

    cv::Ptr<cv::aruco::Dictionary> markerDictionary =
        cv::aruco::getPredefinedDictionary(cv::aruco::PREDEFINED_DICTIONARY_NAME::DICT_4X4_50);

    for (int i = 0; i < 50; i++)
    {
        std::string filename = "assets/markers/marker" + std::to_string(i) + ".jpg";
        cv::aruco::drawMarker(markerDictionary, i, 500, outputMarker, 1);
        cv::imwrite(filename, outputMarker);
    }
}

bool cf::loadCameraCalibration(const std::string& filename, cv::Mat &cameraMatrix,
                               cv::Mat &distortionCoefficients)
{
    std::ifstream inStream(filename);
    if (!inStream.is_open()) return false;

    Json::Value calib;
    inStream >> calib;

    cameraMatrix = cv::Mat(cv::Size(3, 3), CV_64F);
    distortionCoefficients = cv::Mat::zeros(cv::Size(5, 1), CV_64F);

    for (int i = 0; i < cameraMatrix.rows; i++)
    {
        for (int j = 0; j < cameraMatrix.cols; j++)
        {
            double value = calib["cameraMatrix"][3 * i + j].asDouble();
            cameraMatrix.at<double>(i, j) = value;
        }
    }

    for (int i = 0; i < distortionCoefficients.cols; i++)
    {
        double value = calib["distortionCoefficients"][i].asDouble();
        distortionCoefficients.at<double>(distortionCoefficients.rows - 1, i) = value;
    }

    inStream.close();
    return true;
}