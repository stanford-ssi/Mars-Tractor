/** @file button.cpp
 * -----------------------------
 * @author Bartolone, Kai
 * @date July 2020
 */

#include <button.hpp>

bool Button::getState() { return this->isDown; }

void Button::setState(bool state)
{
    this->isDown = state;
    if (this->hasEvent && this->isDown)
    {
        this->signal();
        return;
    }
}