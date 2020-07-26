/** @file axis.h
 * -----------------------------
 * @brief This file defines an button class for interacting with dualshock buttons.
 * @author Bartolone, Kai
 * @date June 2020
 */

#ifndef _button_Included
#define _button_Included

#include <thread>

class Button
{
public:
    bool getState();
    void setState(bool state);

    template <typename _Fn, typename... _Args> void addEventListener(_Fn&& fn, _Args... args)
    {
        std::thread event(fn, (args)...);
        event.join();
    }

private:
    bool isDown = false;
};

#endif