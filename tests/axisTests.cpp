/**
 * tests for every method and check that exceptions are throwing properly
 */
#include <gtest/gtest.h>
#include "button.h"
#include "axis.h"

TEST(gtest, button)
{
    Button button = Button();
    ASSERT_FALSE(button.getState());
    button.setState(true);
    ASSERT_TRUE(button.getState());
}
TEST(gtest2, axis)
{
    Axis axis = Axis();
    axis.setX(.4);
    axis.setY(-1);
    ASSERT_EQ(axis.getX(), (float).4);
    ASSERT_EQ(axis.getY(), -1);
}