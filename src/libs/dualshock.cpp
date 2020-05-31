#include <dualshock.h>

Gamepad::Gamepad(int fd)
{
    //do nothing
}

Gamepad::~Gamepad()
{
    //do nothing

    //stop polling from happening
}

void Gamepad::startPolling()
{
    //error checking in case the controller is not connected and the coder tries to begin polling
    isPolling = true;
    while (isPolling)
    {
        //update values of gamepad things
        //make sure event listeners are happening
    }
}