#include <dualshock.h>

Gamepad::Gamepad(int fd)
{
    //do nothing
}

Gamepad::~Gamepad()
{
    //do nothing
}

Axis::Axis(float x, float y)
{
    x = x;
    y = y;
}

float Axis::getX() 
{
    return x;
}

float Axis::getY() 
{
    return y;
}
