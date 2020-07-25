/** @file main.cpp
 * -----------------------------
 * @brief Main testing file.
 * @author Bartolone, Kai
 * @date June 2020
 */

#include <gtest/gtest.h>
#include "camera.h"


int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}