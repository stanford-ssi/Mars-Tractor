#include <axis.h>

Axis::Axis(float x, float y)
{
    x = x;
    y = y;
}

float Axis::getX() 
{
    if (x < deadzone) 
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
    if (x < deadzone) 
    {
        return 0;
    }
    else
    {
        return y;
    }
}
