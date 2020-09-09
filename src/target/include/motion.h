/** @file motion.h
 * -----------------------------
 * @brief This file defines an motion class for interacting with dualshock motion controls.
 * @author Bartolone, Kai
 * @date June 2020
 */

#ifndef _MOTION_H
#define _MOTION_H

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
