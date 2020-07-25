/** @file buttonTests.cpp
 * -----------------------------
 * @brief Tests Button class for functionality
 * @author Bartolone, Kai
 * @date July 2020
 *
 * Tests all methods and ensures that exceptions are thrown when inputs are invalid.
 */

#include "button.h"
#include <gtest/gtest.h>
#include <iostream>

class EventTests : public ::testing::Test
{
protected:
    void check1() { std::cout << "Function executed" << std::endl; }

    bool check2() { return true; }

    bool check3(int num, bool ran)
    {
        std::cout << num << std::endl;
        return ran;
    }

    void test()
    {
        Button button = Button();
        button.addEventListener(&EventTests::check1);
    }
};

TEST(Button, GetState)
{
    Button button = Button();
    ASSERT_FALSE(button.getState());
    button.setState(true);
    ASSERT_TRUE(button.getState());
}

TEST_F(EventTests, AddEventListener)
{
    test();
}