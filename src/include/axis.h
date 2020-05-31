#ifndef _axis_Included
#define _axis_Included

#include <cstdlib>
#include "point.h"

class Axis
{
    public:
        Axis();
        Axis(float x, float y);
        float getX();
        float getY();
        //TODO: getState returns point with float values
    private:
        float x, y;
        float deadzone = 0;
        void setX(float x);
        void setY(float y);
};

#endif
