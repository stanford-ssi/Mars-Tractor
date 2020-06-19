//#include <camera.h>
#include <dualshock.h>
#include <iostream>
using namespace std;

int main()
{
    
    //Dualshock ds = Dualshock("/dev/input/event20", "/dev/input/event18", "/dev/input/event19");
    Dualshock ds = Dualshock();
    ds.startPolling();
    ds.rumble(3);
    sleep(10);
    //bool controlMode = true;
    //open joystick if it cannot be found run autonomous mode
    return 0;
}