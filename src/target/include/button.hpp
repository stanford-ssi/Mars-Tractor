/** @file button.hpp
 * -----------------------------
 * @brief This file defines an button class for interacting with dualshock buttons.
 * @author Bartolone, Kai
 * @date June 2020
 */

#ifndef _BUTTON_H
#define _BUTTON_H

#include <thread>
#include "event.hpp"

/** @class Button */
class Button : public Event
{
public:
    /**
     * @fn getState
     * -------------------------
     * @return isDown
     */
    bool getState();

    /**
     * @fn setState
     * -------------------------
     * This method sets isDown and should only be accessed by the dualshock class when polling. If
     * isDown is set to true, setState will call the function provided from addEventListener if one
     * is provided.
     */
    void setState(bool state);

    // /**
    //  * @fn addEventListener
    //  * -------------------------
    //  * This method stores a function and its parameters that are called whenever the button is
    //  * pressed and isDown is set from false to true.
    //  * @param fn A function pointer to be called. ex: loadCameraCalibration, &Button::setState
    //  * @param args Any arguments the function takes. Make sure to pass in an object pointer if fn
    //  is
    //  * a member function.
    //  */
    // template <typename Fn, typename... Args> void addEventListener(Fn &&fn, Args &&... args)
    // {
    //     signal.connect(std::bind(fn, (args)...));
    //     hasEvent = true;
    // }

private:
    bool isDown = false;
    // bool hasEvent = false;
    // boost::signals2::signal<void ()> signal;
    // Action event;
};

#endif