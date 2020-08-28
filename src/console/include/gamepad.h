/** @file gamepad.h
 * -----------------------------
 * @brief Simple gamepad container for overlay.
 * @author Bartolone, Kai
 * @date August 2020
 */

#ifndef _GAMEPAD_H
#define _GAMEPAD_H

#include <QPoint>
#include <unordered_map>

// struct Point
// {
//     double x, y;
// };

class Gamepad
{

  private:
    std::unordered_map<std::string, bool> buttons;
    std::unordered_map<std::string, QPoint> axes;

    QPoint touchpad;
};

#endif
