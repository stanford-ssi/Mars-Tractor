/** @file trigger.h
 * -----------------------------
 * @author Bartolone, Kai
 * @date June 2020
 */

#ifndef _TRIGGER_H
#define _TRIGGER_H

#include <iostream>
#include <stdexcept>

class Trigger
{
    public:
        float getValue();
        void setValue(float z);
        bool isDown();
        float getThreshold();
        void setThreshold(float threshold);
    private:
        int id;
        float z;
        float threshold = .75;
};

#endif