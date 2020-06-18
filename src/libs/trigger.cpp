#include "trigger.h"
/*
Trigger::Trigger(float threshold)
{
    threshold = threshold;
}
*/

float Trigger::getValue()
{
    return z;
}

void Trigger::setValue(float z)
{
    if (z < 0 || z > 1)
    {
        std::cerr << "Invalid argument value z: " << z << std::endl;
        throw std::invalid_argument("Trigger value can only be set from -1 to 1.");
    }

    this->z = z;
}

bool Trigger::isDown() //I do not know if it is the other way around
{
    return z < threshold;
}

float Trigger::getThreshold()
{
    return threshold;
}



void Trigger::setThreshold(float threshold)
{
    if (threshold < 0 || threshold > 1)
    {
        std::cerr << "Invalid argument value threshold: " << threshold << std::endl;
        throw std::invalid_argument("Threshold value can only be set from -1 to 1.");
    }
        
    this->threshold = threshold;
}