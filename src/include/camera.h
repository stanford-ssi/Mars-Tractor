#ifndef _camera_Included
#define _camera_Included

#include <cmath>
#include <fstream>
#include <json/json.h>
#include <opencv2/aruco.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/opencv.hpp>
#include <vector>

// Namespace for camera functions
namespace cf
{
    /** Camera Constants */
    const float MARKER_DIMENSION = .15f;    // Square side length of marker in meters

    /** Functions */

    /**
     * Function: createArucoMarkers
     * -------------------------
     * Generates 50 4x4 aruco markers and saves them to assets/makers as .jpg images.
     */
    void createArucoMarkers();

    /**
     * Function: loadCameraCalibration
     * -------------------------
     * Loads camera matrix and distortion coefficients from json (commonly found in assets/confix)
     * into cv::Mat objects.
     */
    bool loadCameraCalibration(const std::string &filename, cv::Mat &cameraMatrix,
                               cv::Mat &distortionCoefficients);

    /**
     * Function: locateTarget
     * -------------------------
     * Takes a cv::Mat frame and attempts to locate target. If no target is found, something
     * happens. If target is found, the function solves for the targets rotation and translation
     * relative to camera position.
     */
    void locateTarget(const cv::Mat &src, cv::Mat &dst);

    /**
     * Function: displayImage
     * -------------------------
     * Helper function DELETE
     */
    void displayImage(const cv::Mat &img, int delay);

    /**
     * Function: capture
     * Opens video stream and searches for aruco marker #7
     */
    int capture(const cv::Mat &cameraMatrix, const cv::Mat &distortionCoefficients,
                float markerDimensions);
    /**
     * Function: calibrateChessboard
     * -------------------------
     * Opens video stream from a webcam that takes many photos of an opencv 9 by 6 chessboard at
     * different angles and distances. These photos are used to produce a camera matrix and
     * distortion coefficients that account for rotational and tangential distortion. These values
     * are saved to a json in assets/config/<cameraname>.json.
     */
    void calibrateChessboard(const std::string &name);

}    // namespace cf

#endif