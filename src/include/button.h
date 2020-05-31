#ifndef _button_Included
#define _button_Included

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