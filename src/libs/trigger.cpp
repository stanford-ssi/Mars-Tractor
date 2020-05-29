#include "trigger.h"

Trigger::Trigger()
{
    //nothing much
}

Trigger::Trigger(float threshold)
{
    threshold = threshold;
}

Trigger::getValue()
{
    return z;
}

Trigger::isDown()
{
    return z < threshold;
}

Trigger::setThreshold(float threshold)
{
    threshold = threshold;
}