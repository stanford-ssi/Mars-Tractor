/*
 * File: axis.h
 * -------------
 * This file defines an axis class for interacting with dualshock joysticks.
 */

#ifndef _axis_Included
#define _axis_Included

#include <cstdlib>
#include <opencv2/core/types.hpp>
#include <stdexcept>
#include <iostream>

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
        int getDeadzone();
        void setDeadzone(float deadzone);
    private:
        float x, y;
        float deadzone = 0.2;
};

#endif
