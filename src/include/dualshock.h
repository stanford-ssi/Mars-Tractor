#ifndef _dualshock_Included
#define _dualshock_Included

#include <linux/joystick.h>
#include <linux/input.h>
#include <linux/input-event-codes.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>
#include <thread>
#include "button.h"
#include "trigger.h"
#include "axis.h"
#include "touchpad.h"

class Dualshock
{
  public:
    /**
    * Creates instance of duslshock. If dualshock controller cannot be found, returns false.
    * Parameter values are usually "/dev/input/jsX" and "/dev/input/eventX" where X is a
    * number.
    */
    Dualshock(const char *joystickPath, const char *touchpadPath, const char *motionPath);

    /**
    * Cleans up all memory allocated for gamepad
    */
    ~Dualshock();

    /**
     * Sets dualshock leds.
    */
    void setLed();

    /**
      * Begins thread that continously reads from /dev/js0 to update gamepad values and 
    */
    void startPolling();

    /**
     * Returns gamepad button with provided name.
    */
    Button getButton(std::string id);

    /**
     * Returns gamepad button state with provided name.
    */
    bool getButtonState(std::string id);

    /**
     * Returns gamepad trigger with provided id.
    */
    Trigger getTrigger(std::string id);

    /**
     * Returns value of gamepad trigger with provided id.
    */
    float getTriggerValue(std::string id);

    /**
     * Returns gamepad axis with provided id.
    */
    Axis getAxis(std::string id);

    /**
     * Returns values of gamepad axis with provided id.
    */
    //Point<float x, float y> getAxisState(int id);

    void stopPolling();

    /**
     * Prints out state of Dualshock.
     */
    void printOut();

  private:
    //std::thread* jsThread;
    int jfd;
    int tfd;
    int mfd;
    input_event tp;
    input_event mo;
    const std::vector<std::string> buttonNames = {"X", "O", "TRIANGLE", "SQUARE", "LB",
                                                    "RB", "LT", "RT", "SHARE", "OPTIONS", 
                                                    "PS", "LJSB", "RJSB", "LEFT", "RIGHT",
                                                    "UP", "DOWN"};
    const std::vector<std::string> axisNames = {"LJS", "RJS"};
    const std::vector<std::string> triggerNames = {"LT", "RT"};
    
    std::unordered_map<std::string, Button> buttons;
    std::unordered_map<std::string, Trigger> triggers;
    std::unordered_map<std::string, Axis> axes;
    std::unordered_map<__u8, std::string> codes = {
												  {BTN_SOUTH, "X"}, {BTN_EAST, "O"}, {BTN_NORTH, "TRIANGLE"},
                          {BTN_WEST, "SQUARE"}, {BTN_TL, "LB"}, {BTN_TR, "RB"},
                          {BTN_TL2, "LT"}, {BTN_TR2, "RT"}, {BTN_SELECT, "SHARE"},
                          {BTN_START, "OPTIONS"}, {BTN_MODE, "PS"}, {BTN_THUMBL, "LJSB"},
                          {BTN_THUMBR, "RJSB"},

                          {ABS_X, "LJSX"}, {ABS_Y, "LJSY"}, {ABS_Z, "LTZ"},
                          {ABS_RX, "RJSX"}, {ABS_RY, "RJSY"}, {ABS_RZ, "RTZ"},
                          {ABS_HAT0X, "DPADX"}, {ABS_HAT0Y, "DPADY"}
 	  	  	  	  	  	  	};
    bool isPolling;

    void readJoystick();
    void readTouchpad();
    void readMotion();
    void generateMaps();
    void writeDPAD(char type, int value);
    void writeAxes(std::string id, char type, float value);
};

#endif