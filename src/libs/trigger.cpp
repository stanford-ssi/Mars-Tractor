#include "trigger.h"

Trigger::Trigger()
{
    //nothing much
}

Trigger::Trigger(float threshold)
{
    threshold = threshold;
}

float Trigger::getValue()
{
    return z;
}

bool Trigger::isDown()
{
    return z < threshold;
}

void Trigger::setThreshold(float threshold)
{
    //add error checking
    threshold = threshold;
}