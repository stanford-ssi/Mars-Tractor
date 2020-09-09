/** @file axis.hpp
 * -----------------------------
 * @brief This file defines an axis class for interacting with dualshock joysticks.
 * @author Bartolone, Kai
 * @date June 2020
 */

#ifndef _AXIS_HPP
#define _AXIS_HPP

#include <cstdlib>
#include <iostream>
#include <opencv2/core/types.hpp>
#include <stdexcept>

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
