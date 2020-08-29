/** @file gamepad.cpp
 * -----------------------------
 * @author Bartolone, Kai
 * @date August 2020
 */

#include <gamepad.h>

Gamepad::Gamepad()
{
    using namespace std;

    buttons = new unordered_map<string, bool>({{"dpad_down", false},
                                               {"dpad_left", false},
                                               {"dpad_right", false},
                                               {"dpad_up", false},
                                               {"home", false},
                                               {"left_bumper", false},
                                               {"left_stick_pressed", false},
                                               {"left_trigger", false},
                                               {"o_button", false},
                                               {"right_bumper", false},
                                               {"right_stick_pressed", false},
                                               {"right_trigger", false},
                                               {"square_button", false},
                                               {"share", false},
                                               {"options", false},
                                               {"touchpad", false},
                                               {"triangle_button", false},
                                               {"x_button", false}});
}

Gamepad::~Gamepad() { delete buttons; }

bool Gamepad::getButtonState(const std::string& name)
{
    if (buttons->count(name))
    {
        return (*buttons)[name];
    }
    else
    {
        return false;
    }
}

void Gamepad::setButtonState(const std::string& name, bool state)
{
    if (buttons->count(name)) (*buttons)[name] = state;
}