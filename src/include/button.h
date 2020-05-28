#ifndef button_Included
#define button_Included

class Button
{
    public:
        Button();
        bool getState();
        void whenPressed(int function);
    private:
        bool isDown;
};

#endif