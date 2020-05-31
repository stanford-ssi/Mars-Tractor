#ifndef axis_Included
#define axis_Included

//#include <stdlib>

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
};

#endif
