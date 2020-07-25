/** @file axis.h
 * -----------------------------
 * @brief This file defines an button class for interacting with dualshock buttons.
 * @author Bartolone, Kai
 * @date June 2020
 */

#ifndef _button_Included
#define _button_Included

class Button
{
public:
    bool getState();
    void setState(bool state);

    template <typename _Fn, typename... _Args> void addEventListener(_Fn &&_Fx, _Args &&... _Ax);

private:
    bool isDown = false;
};

#endif