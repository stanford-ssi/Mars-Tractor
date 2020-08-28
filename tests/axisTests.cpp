/** @file axisTests.cpp
 * -----------------------------
 * @brief Tests Axis class for functionality
 * @author Bartolone, Kai
 * @date June 2020
 *
 * Tests all methods and ensures that exceptions are thrown when inputs are invalid.
 */

#include <axis.hpp>
#include <gtest/gtest.h>

/**
 * @test Set_Get
 * -----------------------------
 * Checks if axis setters and getters are working properly.
 */
TEST(AxisTests, axis)
{
    Axis axis();
    axis.setX(.4f);
    axis.setY(-1);
    ASSERT_EQ(axis.getX(), .4f);
    ASSERT_EQ(axis.getY(), -1);
}