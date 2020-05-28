#include <camera.h>
#include <dualshock.h>
#include <iostream>


int main()
{
    bool controlMode = true;
    //open joystick if it cannot be found run autonomous mode
    int fd;
    Gamepad ds = Gamepad(fd);
    //if it is connected run controller mode
    return 0;
}