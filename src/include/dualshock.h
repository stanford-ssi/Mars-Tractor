#ifndef dualshock_Included
#define dualshock_Included

#include <linux/joystick.h>
#include <fcntl.h>
#include <string>
#include <unordered_map>
#include "button.h"
#include "trigger.h"
#include "axis.h"
#include "touchpad.h"

class Gamepad
{
    public:
        /**
        * Creates instance of gamepad. If dualshock controller cannot be found, returns false.
        */
        Gamepad(int fd);

        /**
        * Cleans up all memory allocated for gamepad
        */
        ~Gamepad();

        /**
          * Begins thread that continously reads from /dev/js0 to update gamepad values and 
        */
        void startPolling();

        /**
         * Returns gamepad button with provided name.
        */
        Button getButton(string name);

        /**
         * Returns gamepad button state with provided name.
        */
        bool getButtonState(string name);

        /**
         * Returns gamepad trigger with provided id.
        */
        Trigger getTrigger(int id);

        /**
         * Returns value of gamepad trigger with provided id.
        */
        float getTriggerValue(int id);

        /**
         * Returns state gamepad trigger with provided id.
        */
        float getTriggerState(int id);

        /**
         * Returns gamepad axis with provided id.
        */
        Axis getAxis(int id);

        /**
         * Returns values of gamepad axis with provided id.
        */
        Point<float x, float y> getAxisState(int id);

    private:
        int id;
        const unordered_map<string, Button> buttons;
        bool isPolling = false;
};

#endif