#include <gtest/gtest.h>
#include "../include/lab.h"
#include <cstdint>

TEST(SimpleTest1, SimpleTests) {
    ASSERT_EQ(time_reformat(12, 30, "am"), "1230");
}

TEST(SimpleTest2, SimpleTests) {
    ASSERT_EQ(time_reformat(5, 43, "pm"), "1743");
}

TEST(Simpletest3, SimpleTests) {
    ASSERT_EQ(time_reformat(12, 01, "pm"), "0001");
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}