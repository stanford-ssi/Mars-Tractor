#include <camera.h>
#include <dualshock.h>
#include <iostream>

int main()
{
    int fd;
    Gamepad ds = Gamepad(fd);
    //if it is connected run controller mode
    while() //gamepad is connected get all input events
    {
        //iterate over all input events and print out their values
    }
    return 0;
}