#include "motion.h"

void Motion::setState(int x, int y, int z)
{
    if (x * y * z > 46656000 || x * y * z < 0)
    {
        std::cerr << "Invalid argument values x, y, z: " << x << ", " << y << ", " << z << std::endl;
        throw std::invalid_argument("Motion values can only be set from 0 to 360.");
    }

    this->x = x;
    this->y = y;
    this->z = z;
}

void Motion::setX(int x)
{
    if (x > 360 || x < 0)
    {
        std::cerr << "Invalid argument value x: " << x << std::endl;
        throw std::invalid_argument("Motion values can only be set from 0 to 360.");
    }

    this->x = x;
}

void Motion::setY(int y)
{
    if (y > 360 || y < 0)
    {
        std::cerr << "Invalid argument value : " << y << std::endl;
        throw std::invalid_argument("Motion values can only be set from 0 to 360.");
    }

    this->y = y;
}

void Motion::setZ(int z)
{
    if (z > 360 || z < 0)
    {
        std::cerr << "Invalid argument value z: " << z << std::endl;
        throw std::invalid_argument("Motion values can only be set from 0 to 360.");
    }

    this->z = z;
}

int Motion::getX() 
{
   return this->x;
}

int Motion::getY() 
{
   return this->y;
}

int Motion::getZ() 
{
   return this->z;
}