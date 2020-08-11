/** @file event.h
 * -----------------------------
 * @brief This file defines a base event class for handling events.
 * @author Bartolone, Kai
 * @date August 2020
 */
 
#ifndef _event_Included
#define _event_Included

#include <boost/signals2.hpp>

class Event
{
    public:
    /**
     * @fn addEventListener
     * -------------------------
     * This method stores a function and its parameters that are called whenever the button is
     * pressed and isDown is set from false to true.
     * @param fn A function pointer to be called. ex: loadCameraCalibration, &Button::setState
     * @param args Any arguments the function takes. Make sure to pass in an object pointer if fn
     is
     * a member function.
     */
    template <typename Fn, typename... Args> void addEventListener(Fn &&fn, Args &&... args)
    {
        signal.connect(std::bind(fn, (args)...));
        hasEvent = true;
    }

protected:
    bool hasEvent = false;
    boost::signals2::signal<void ()> signal;
};


#endif