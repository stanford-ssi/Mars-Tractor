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

class ButtonTests : public ::testing::Test
{
protected:
    void check1() { return; }

    bool check2() { return true; }

    bool check3(int num, bool ran)
    {
        if (ran)
            return true;
        else
            return ran;
    }

    void check4(bool &change) { change = false; }

    void initial()
    {
        Button button = Button();
        EXPECT_NO_THROW(button.addEventListener(&ButtonTests::check1, this));
    }

    void returns()
    {
        Button button = Button();
        EXPECT_NO_THROW(button.addEventListener(&ButtonTests::check2, this));
    }

    void parameters()
    {
        Button button = Button();
        bool run = true;
        EXPECT_NO_THROW(button.addEventListener(&ButtonTests::check3, this, 7, run));
    }

    void reference()
    {
        bool run = true;
        Button button = Button();
        ASSERT_NO_THROW(button.addEventListener(&ButtonTests::check4, this, std::ref(run)));
        EXPECT_FALSE(run);
    }
};

TEST_F(ButtonTests, SetState_IsSetting)
{
    Button button = Button();
    EXPECT_FALSE(button.getState());

    button.setState(true);
    EXPECT_TRUE(button.getState());

    button.setState(false);
    EXPECT_FALSE(button.getState());
}

TEST_F(ButtonTests, AddEventListener_NoThrow) { initial(); }
TEST_F(ButtonTests, AddEventListener_NoThrowWithParameters) { parameters(); }
TEST_F(ButtonTests, AddEventListener_CanReturn) { returns(); }
TEST_F(ButtonTests, AddEventListener_TakenByReference) { reference(); }