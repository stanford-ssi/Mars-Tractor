#ifndef dualshock_Included
#define dualshock_Included

#include <linux/joystick.h>
#include <fcntl.h>

class Gamepad
{
    public:
        /**
        * Creates instance of gamepad. If dualshock controller canntot be found, returns false.
        */
        Gamepad(int fd);

        /**
        * Cleans up all memory allocated for gamepad
        */
        ~Gamepad();
    private:
        int id;
};

#endif