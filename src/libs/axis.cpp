#include "axis.h"

cv::Point2f Axis::getState()
{
    cv::Point2f result = cv::Point2f(x, y);
    if (std::abs(x) < deadzone)
    {
        result.x = 0;
    }
    else if (std::abs(x) < deadzone)
    {
        result.y = 0;
    }

    return result;
}

void Axis::setState(float x, float y)
{
    if (std::abs(x) > 1 || std::abs(y) > 1)
    {
        std::cerr << "Invalid argument values x, y: " << x << ", " << y << std::endl;
        throw std::invalid_argument("Axis values can only be set from -1 to 1.");
    }

    this->x = x;
    this->y = y;
}

float Axis::getX()
{
    if (std::abs(x) < deadzone)
    {
        return 0;
    }
    else
    {
        return x;
    }
}

float Axis::getY()
{
    if (std::abs(y) < deadzone)
    {
        return 0;
    }
    else
    {
        return y;
    }
}

void Axis::setX(float x)
{
    if (std::abs(x) > 1)
    {
        std::cerr << "Invalid argument value x: " << x << std::endl;
        throw std::invalid_argument("Axis values can only be set from -1 to 1.");
    }

    this->x = x;
}

void Axis::setY(float y)
{
    if (std::abs(y) > 1)
    {
        std::cerr << "Invalid argument value y: " << y << std::endl;
        throw std::invalid_argument("Axis values can only be set from -1 to 1.");
    }

    this->y = y;
}

float Axis::getDeadzone() { return deadzone; }

void setDeadzone(float deadzone)
{
    if (deadzone > 1)
    {
        std::cerr << "Invalid argument value deadzone: " << deadzone << std::endl;
        throw std::invalid_argument("Deadzone value can only be set from 0 to 1.");
    }

    deadzone = deadzone;
}