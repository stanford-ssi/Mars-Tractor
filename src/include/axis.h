#ifndef axis_Included
#define axis_Included

class Axis
{
    public:
        Axis();
        float getX();
        float getY();
        //TODO: getState returns point with float values
    private:
        float x, y;
        float deadzone = 0;
};

#endif
