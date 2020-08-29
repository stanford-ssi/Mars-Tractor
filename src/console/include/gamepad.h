/** @file gamepad.h
 * -----------------------------
 * @brief Simple gamepad container for overlay.
 * @author Bartolone, Kai
 * @date August 2020
 */

#ifndef _GAMEPAD_H
#define _GAMEPAD_H

#include <unordered_map>

struct Point
{
    double x, y;
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

#endif
