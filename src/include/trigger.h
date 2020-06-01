#ifndef _trigger_Included
#define _trigger_Included

#include <iostream>
#include <stdexcept>

class Trigger
{
    public:
        Trigger(int id);
        Trigger(int id, float threshold);
        float getValue();
        void setValue(float z);
        bool isDown();
        float getThreshold();
        void setThreshold(float threshold);
    private:
        int id;
        float z;
        float threshold = .75;
};

#endif