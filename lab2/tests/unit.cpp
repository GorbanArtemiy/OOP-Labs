#include <gtest/gtest.h>
#include "../include/lab.h"
#include <iostream>

TEST(ThreeBehavior, Addition) {
  Three t1("201");
  Three t2("1");
  Three t3 = t1 + t2;
  ASSERT_EQ(t3, Three("202"));
}

TEST(ThreeBehavior, Subtraction) {
  Three t1("102");
  Three t2("101");
  Three t3 = t1 - t2;
  ASSERT_EQ(t3, Three("1"));
}

TEST(ThreeBehavior, InvalidInitListException) {
  ASSERT_THROW(Three t1({'1', '2', '9'}), std::invalid_argument);
}
1
TEST(ThreeBehavior, InvalidStringException) {
  ASSERT_THROW(Three t1("999"), std::invalid_argument);
}

TEST(ThreeBehavior, SubtractionException) {
  Three t1("012");
  Three t2("100000");
  ASSERT_THROW(t1 -= t2, std::invalid_argument);
}

TEST(ThreeBehavior, Comparison) {
  Three t1("102");
  Three t2("200");
  Three t3("102");
  ASSERT_TRUE(t1 < t2);
  ASSERT_TRUE(t2 > t1);
  ASSERT_TRUE(t1 <= t3);
  ASSERT_TRUE(t1 >= t3);
  ASSERT_TRUE(t1 == t3);
  ASSERT_TRUE(t1 != t2);
}

TEST(ThreeBehavior, Output) {
  Three t("120");
  std::stringstream ss;
  ss << t;
  ASSERT_EQ(ss.str(), "120");
}

TEST(ThreeBehavior, Zero) {
  Three t("0");
  ASSERT_EQ(t + t, t);
  ASSERT_EQ(t - t, t);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}