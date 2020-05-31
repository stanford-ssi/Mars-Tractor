#ifndef trigger_Included
#define trigger_Included

class Trigger
{
    public:
        Trigger();
        Trigger(float threshold);
        float getValue();
        bool isDown();
        void setThreshold(float threshold);
    private:
        float z;
        float threshold = .75;
};

#endif