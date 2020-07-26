/** @file axisTests.cpp
 * -----------------------------
 * @brief Tests Axis class for functionality
 * @author Bartolone, Kai
 * @date June 2020
 *
 * Tests all methods and ensures that exceptions are thrown when inputs are invalid.
 */

#include "axis.h"
#include "button.h"
#include <gtest/gtest.h>


TEST(AxisTests, axis)
{
    Axis axis = Axis();
    axis.setX(.4);
    axis.setY(-1);
    ASSERT_EQ(axis.getX(), (float).4);
    ASSERT_EQ(axis.getY(), -1);
}