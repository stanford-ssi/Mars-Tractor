#include <gtest/gtest.h>
#include "point.h"

TEST(gtest, Check)
{
    ASSERT_EQ(1, 1);
    ASSERT_EQ(1, 2);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}