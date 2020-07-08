#include <gtest/gtest.h>

TEST(gtest, check)
{
    bool thing = false;
    ASSERT_FALSE(thing);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}