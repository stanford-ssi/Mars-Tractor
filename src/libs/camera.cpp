/** @file camera.cpp
 * -----------------------------
 * @author Bartolone, Kai
 * @date July 2020
 */

#include "camera.h"

void cf::locateTarget(const cv::Mat &src, cv::Mat &dst) {}

int cf::capture(const cv::Mat &cameraMatrix, const cv::Mat &distCoeffs, float markerDimensions)
{
    cv::Mat frame;
    std::vector<int> markerIds = {7};

    std::vector<std::vector<cv::Point2f>> markerCorners, rejects;

    cv::Ptr<cv::aruco::Dictionary> markerDictionary =
        cv::aruco::getPredefinedDictionary(cv::aruco::PREDEFINED_DICTIONARY_NAME::DICT_4X4_50);

    cv::VideoCapture cap(0);

    if (!cap.isOpened())
    {
        std::cerr << "Camera cannot be found." << std::endl;
        return -1;
    }
    cv::namedWindow("Camera", cv::WINDOW_AUTOSIZE);

    std::vector<cv::Vec3d> rvecs, tvecs;

    bool isRead = cap.read(frame);
    if (!isRead) std::cerr << "Camera cannot be read." << std::endl;

    while (1)
    {
        // Capture frame-by-frame
        isRead = cap.read(frame);
        if (!isRead) break;

        cv::aruco::detectMarkers(frame, markerDictionary, markerCorners, markerIds);
        cv::aruco::estimatePoseSingleMarkers(markerCorners, markerDimensions, cameraMatrix,
                                             distCoeffs, rvecs, tvecs);
        for (int i = 0; i < markerIds.size(); i++)
        {
            cv::aruco::drawAxis(frame, cameraMatrix, distCoeffs, rvecs[i], tvecs[i], 0.1f);
            std::string translationText = "x: " + std::to_string(tvecs[i][0]) +
                                          ", y: " + std::to_string(tvecs[i][1]) +
                                          ", z: " + std::to_string(tvecs[i][2]);
            std::string rotationText = "row: " + std::to_string(rvecs[i][0]) +
                                       ", theta: " + std::to_string(rvecs[i][1]) +
                                       ", psi: " + std::to_string(rvecs[i][2]);
            cv::putText(frame, translationText, cv::Point(0, 20), cv::FONT_HERSHEY_PLAIN, 1,
                        cv::Scalar(0, 0, 0));
            cv::putText(frame, rotationText, cv::Point(0, 50), cv::FONT_HERSHEY_PLAIN, 1,
                        cv::Scalar(0, 0, 0));
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

bool cf::loadCameraCalibration(const std::string &filename, cv::Mat &cameraMatrix,
                               cv::Mat &distCoeffs)
{
    std::ifstream inStream(filename);
    if (!inStream.is_open()) return false;

    Json::Value calib;
    inStream >> calib;

    cameraMatrix = cv::Mat(cv::Size(3, 3), CV_64F);
    distCoeffs = cv::Mat::zeros(cv::Size(5, 1), CV_64F);

    for (int i = 0; i < cameraMatrix.rows; i++)
    {
        for (int j = 0; j < cameraMatrix.cols; j++)
        {
            double value = calib["cameraMatrix"][3 * i + j].asDouble();
            cameraMatrix.at<double>(i, j) = value;
        }
    }

    for (int i = 0; i < distCoeffs.cols; i++)
    {
        double value = calib["distCoeffs"][i].asDouble();
        distCoeffs.at<double>(distCoeffs.rows - 1, i) = value;
    }

    inStream.close();
    return true;
}

bool cf::detectTarget(const cv::Mat &src, std::vector<cv::Point2f> &targetCorners)
{
    // Greyscale image
    cv::Mat grey;
    cv::cvtColor(src, grey, cv::COLOR_BGR2GRAY);

    // // STEP 1: Detect target candidates
    // std::vector<std::vector<cv::Point2f>> candidates;
    // std::vector<std::vector<cv::Point>> contours;
    // std::vector<std::vector<std::vector<cv::Point2f>>> candidatesSet;
    // std::vector<std::vector<std::vector<cv::Point>>> contoursSet;

    // cv::Mat blur;
    // cv::GaussianBlur(grey, blur, cv::Size(5, 5), 0);

    // STEP 2: Detect target candidates

    // Apply adaptive thresholding
    cv::Mat bin;
    cv::adaptiveThreshold(grey, bin, 255, cv::ADAPTIVE_THRESH_GAUSSIAN_C, cv::THRESH_BINARY, 5, 0);
    // cv::threshold(grey, bin, 100, 255, cv::THRESH_BINARY);

    // Find contours
    std::vector<std::vector<cv::Point>> contours;
    std::vector<std::vector<cv::Point>> candidates;
    std::vector<cv::Point> approxShape;
    cv::findContours(bin, contours, cv::RETR_TREE, cv::CHAIN_APPROX_NONE);

    // Remove contours with small number of points (noise)
    for (int i = 0; i < contours.size(); i++)
    {
        bool isValidShape = checkContour(src, contours[i], .03, 4., .05, 3);
        if (isValidShape)
        {
            cv::approxPolyDP(contours[i], approxShape, 3, true);
            candidates.push_back(approxShape);
        }
        // // Approximate polygonal shape of remaining borders and keep concaves with 4 corners
        // cv::approxPolyDP(contours[i], approxShape, 3, true);

        // if (approxShape.size() == 4 && cv::isContourConvex(approxShape))
        // {
        // candidates.push_back(approxShape);
        // }
    }
    cv::Mat img = cv::Mat::ones(cv::Size(bin.rows, bin.cols), 0);
    img.setTo(cv::Scalar(255, 255, 255));

    cv::drawContours(src, candidates, -1, cv::Scalar(66, 135, 245));
    displayMat(src, 30);

    // Remove internal rectangles

    // Remove projection perspective
    // Threshold with Otsu's algorithm
    // Detect rotation and return target corners

    // cf::displayImage(blur, 3);

    return false;
}

bool cf::checkContour(const cv::Mat &src, const std::vector<cv::Point> &contour,
                      double minPerimeterRate, double maxPerimeterRate,
                      double minCornerDistanceRate, int minDistanceToBorder)
{
    unsigned int minPerimeterPixels =
        (unsigned int)(minPerimeterRate * std::max(src.cols, src.rows));
    unsigned int maxPerimeterPixels =
        (unsigned int)(maxPerimeterRate * std::max(src.cols, src.rows));
    // check perimeter
    if (contour.size() < minPerimeterPixels || contour.size() > maxPerimeterPixels) return false;

    // check is square and is convex
    std::vector<cv::Point> approxShape;
    cv::approxPolyDP(contour, approxShape, 3, true);
    if (approxShape.size() != 4 || !cv::isContourConvex(approxShape)) return false;

    // check min distance between corners
    double minDistSq = std::max(src.cols, src.rows) * std::max(src.cols, src.rows);
    for (int j = 0; j < 4; j++)
    {
        double d = (double)(approxShape[j].x - approxShape[(j + 1) % 4].x) *
                       (double)(approxShape[j].x - approxShape[(j + 1) % 4].x) +
                   (double)(approxShape[j].y - approxShape[(j + 1) % 4].y) *
                       (double)(approxShape[j].y - approxShape[(j + 1) % 4].y);
        minDistSq = std::min(minDistSq, d);
    }
    double minCornerDistancePixels = double(contour.size()) * minCornerDistanceRate;
    if (minDistSq < minCornerDistancePixels * minCornerDistancePixels) return false;

    // check if it is too near to the image border
    bool tooNearBorder = false;
    for (int j = 0; j < 4; j++)
    {
        if (approxShape[j].x < minDistanceToBorder || approxShape[j].y < minDistanceToBorder ||
            approxShape[j].x > src.cols - 1 - minDistanceToBorder ||
            approxShape[j].y > src.rows - 1 - minDistanceToBorder)
            tooNearBorder = true;
    }
    if (tooNearBorder) return false;

    // if it passes all the test, return true
    return true;
}

Position cf::estimatePose(const std::vector<cv::Point2f> &targetCorners, float targetDimension,
                          const cv::Mat &cameraMatrix, const cv::Mat &distCoeffs)
{
    std::vector<cv::Point2f> cameraPoints;
    cv::Vec3d rvecs, tvecs;
    cv::solvePnP(targetCorners, cameraPoints, cameraMatrix, distCoeffs, rvecs, tvecs);

    return Position(tvecs[0], tvecs[1], tvecs[2], rvecs[0], rvecs[1], rvecs[2]);
}

void cf::displayPosition(cv::Mat &src, Position position)
{
    std::string translationText = "x: " + std::to_string(position.x) +
                                  ", y: " + std::to_string(position.y) +
                                  ", z: " + std::to_string(position.z);
    std::string rotationText = "row: " + std::to_string(position.row) +
                               ", theta: " + std::to_string(position.theta) +
                               ", psi: " + std::to_string(position.psi);
    cv::putText(src, translationText, cv::Point(0, 20), cv::FONT_HERSHEY_PLAIN, 1,
                cv::Scalar(0, 0, 0));
    cv::putText(src, rotationText, cv::Point(0, 50), cv::FONT_HERSHEY_PLAIN, 1,
                cv::Scalar(0, 0, 0));
}

Position::Position(double x, double y, double z, double row, double theta, double psi)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->row = row;
    this->theta = theta;
    this->psi = psi;
}

void cf::displayMat(const cv::Mat &img, int delay)
{
    cv::namedWindow("Image", cv::WINDOW_AUTOSIZE);
    cv::imshow("Image", img);
    if (cv::waitKey(delay) >= 0) return;
}

cv::Vec3d cf::rotationMatrixToEulerAngles(const cv::Mat &R)
{

    //assert(isRotationMatrix(R));

    double sy =
        std::sqrt(R.at<double>(0, 0) * R.at<double>(0, 0) + R.at<double>(1, 0) * R.at<double>(1, 0));

    bool singular = sy < 1e-6;    // If

    double x, y, z;
    if (!singular)
    {
        x = std::atan2(R.at<double>(2, 1), R.at<double>(2, 2)) * 180 / 3.14;
        y = std::atan2(-R.at<double>(2, 0), sy)* 180 / 3.14;
        z = std::atan2(R.at<double>(1, 0), R.at<double>(0, 0))* 180 / 3.14;
    }
    else
    {
        x = std::atan2(-R.at<double>(1, 2), R.at<double>(1, 1));
        y = std::atan2(-R.at<double>(2, 0), sy);
        z = 0;
    }

    return cv::Vec3d(x, y, z);
}

void cf::displayPosition(cv::Mat &img, const cv::Vec3d &tvecs, const cv::Vec3d &rvecs)
{
    cv::Mat R;
    cv::Rodrigues(rvecs, R);
    cv::Vec3d angles = rotationMatrixToEulerAngles(R);

    double degreeConstant = 180 / 3.1416;
    std::string translationText = "x: " + std::to_string(tvecs[0]) +
                                  ", y: " + std::to_string(tvecs[1]) +
                                  ", z: " + std::to_string(tvecs[2]);
    std::string rotationText = "row: " + std::to_string(angles[0]) +
                               ", theta: " + std::to_string(angles[1]) +
                               ", psi: " + std::to_string(angles[2]);
    cv::putText(img, translationText, cv::Point(0, 20), cv::FONT_HERSHEY_PLAIN, 1.25,
                cv::Scalar(66, 135, 245));
    cv::putText(img, rotationText, cv::Point(0, 50), cv::FONT_HERSHEY_PLAIN, 1.25,
                cv::Scalar(66, 135, 245));
}