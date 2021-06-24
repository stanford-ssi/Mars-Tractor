/**
 * @file gamepad.h
 * -----------------------------
 * @brief Simple gamepad container for overlay.
 * @author Bartolone, Kai
 * @date August 2020
 */

#ifndef _GAMEPAD_H
#define _GAMEPAD_H

#include <string>
#include <unordered_map>

struct Point
{
    float x, y;
};

class Gamepad
{
  public:
    Gamepad();
    ~Gamepad();
    bool getButtonState(const std::string& name);
    void setButtonState(const std::string& name, bool state);

  private:
    std::unordered_map<std::string, bool>* buttons;
    std::unordered_map<std::string, Point>* axes;

    Point touchpad;
    bool isConnected;
};

struct ds4_input
{
    Point rjoy, ljoy, triggers;
    int buttons;
};

#endif
