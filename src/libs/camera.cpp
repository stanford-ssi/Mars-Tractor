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

int cf::video()
{
    cv::Mat frame;
    std::vector<int> markerIds;

    std::vector<std::vector<cv::Point2f>> markerCorners, rejects;
    cv::aruco::DetectorParameters parameters;

    cv::Ptr<cv::aruco::Dictionary> markerDictionary =
        cv::aruco::getPredefinedDictionary(cv::aruco::PREDEFINED_DICTIONARY_NAME::DICT_4X4_50);

    cv::VideoCapture cap(0);
    cap.open(0, cv::CAP_ANY);

    if (!cap.isOpened())
    {
        std::cerr << "Camera cannot be found." << std::endl;
        return -1;
    }
    cv::namedWindow("Camera", cv::WINDOW_AUTOSIZE);

    std::vector<cv::Vec3d> rotationVectors, translationVectors;

    while (cap.read(frame) && !frame.empty())
    {
        cv::aruco::detectMarkers(frame, markerDictionary, markerCorners, markerIds);
        cv::aruco::estimatePoseSingleMarkers(markerCorners, 0,
                                             cf::CAMERA_MATRIX_C920, cf::DISTORTION_COEFFS_C920,
                                             rotationVectors, translationVectors);
        for (int i = 0; i < markerIds.size(); i++)
        {
            cv::aruco::drawAxis(frame, cf::CAMERA_MATRIX_C920, cf::DISTORTION_COEFFS_C920,
                                rotationVectors, translationVectors, 0.1f);
        }
        cv::imshow("Camera", frame);
        if (cv::waitKey(30) >= 0) break;
    }

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

bool cf::loadCameraCalibration(std::string filename, cv::Mat& cameraMatrix, cv::Mat& distortionCoefficients)
{
    std::ifstream inStream(filename);
    inStream >> calib;
    if (inStream)
    {
        uin16_t rows;
        uint16_t columns;
    }
}