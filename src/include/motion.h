/*
 * File: motion.h
 * -------------
 * This file defines an motion class for interacting with dualshock motion controls.
 */

#ifndef _motion_Included
#define _motion_Included

#include <stdexcept>
#include <iostream>

class Motion
{
    public:
        void setState(int x, int y, int z);
        int getX();
        int getY();
        int getZ();
        void setX(int x);
        void setY(int y);
        void setZ(int z);
    private:
        int x, y, z;
};

#endif
