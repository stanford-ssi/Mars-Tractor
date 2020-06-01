#include "trigger.h"

Trigger::Trigger(int id)
{
    id = id;
}

Trigger::Trigger(int id, float threshold)
{
    id = id;
    threshold = threshold;
}


float Trigger::getValue()
{
    return z;
}

void Trigger::setValue(float z)
{
    if (std::abs(z) > 1)
    {
        std::cerr << "Invalid argument value z: " << z << std::endl;
        throw std::invalid_argument("Trigger value can only be set from -1 to 1.");
    }

    z = z;
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
    if (std::abs(threshold) > 1)
    {
        std::cerr << "Invalid argument value threshold: " << threshold << std::endl;
        throw std::invalid_argument("Threshold value can only be set from -1 to 1.");
    }
        
    threshold = threshold;
}