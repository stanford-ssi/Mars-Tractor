/** @file axis.h
 * -----------------------------
 * @author Bartolone, Kai
 * @date July 2020
 */
#include "button.h"
#include <thread>

bool Button::getState() { return this->isDown; }

void Button::setState(bool state) { this->isDown = state; }