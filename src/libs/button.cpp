/** @file axis.h
 * -----------------------------
 * @author Bartolone, Kai
 * @date July 2020
 */
#include "button.h"
#include <thread>

bool Button::getState() { return this->isDown; }

void Button::setState(bool state) { this->isDown = state; }

template <typename _Fn, typename... _Args> void addEventListener(_Fn &&_Fx, _Args &&... _Ax)
{
    std::thread event(_Fx, _Ax);
    event.join();
}