#include <camera.h>
//#include "dualshock.h"
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/aruco.hpp>
using namespace std;
using namespace cv;
using namespace cf;

int main()
{
    Mat cameraMatrix, distortionCoefficients;
    if (!loadCameraCalibration("assets/config/C920_Calibration.json", cameraMatrix, distortionCoefficients)) return -1;

    cout << capture(cameraMatrix, distortionCoefficients, MARKER_DIMENSION);
    
    return 0;
}