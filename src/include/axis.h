/** @file axis.h
 * -----------------------------
 * @brief This file defines an axis class for interacting with dualshock joysticks.
 * @author Bartolone, Kai
 * @date June 2020
 */

#ifndef _axis_Included
#define _axis_Included

#include <cstdlib>
#include <iostream>
#include <opencv2/core/types.hpp>
#include <stdexcept>

/* TODO: implement test case if this function works and throws exception properly
 * write all of the test cases
 * write comments
 *
 */

class Axis
{
public:
    cv::Point2f getState();
    void setState(float x, float y);
    float getX();
    float getY();
    void setX(float x);
    void setY(float y);
    float getDeadzone();
    void setDeadzone(float deadzone);

private:
    float x, y;
    float deadzone = 0.2f;
};

#endif
