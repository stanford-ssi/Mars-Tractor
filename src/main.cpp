//#include <camera.h>
#include <dualshock.h>
#include <iostream>
using namespace std;

int main()
{
    
    Dualshock ds = Dualshock("/dev/input/event22", "/dev/input/event20", "/dev/input/event21");
    //std::thread t1(&Dualshock::startPolling, ds);
    /*
    for (int i = 0; i < 100; i++)
    {
        ds.startPolling();
        sleep(.5);
        ds.stopPolling();
        ds.printOut();
        sleep(.5);
    }
    */
    ds.startPolling();
    ds.stopPolling();
    ds.~Dualshock();
    //t1.join();
    bool controlMode = true;
    //open joystick if it cannot be found run autonomous mode
    //Gamepad ds = Gamepad(fd);
    //if it is connected run controller mode
    return 0;
}