#include "button.h"

bool Button::getState()
{
    return this->isDown;
}

void Button::setState(bool state)
{
    this->isDown = state;
}