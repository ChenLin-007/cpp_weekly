#include <gtest/gtest.h>
#include <iostream>
#include <valarray>

TEST(StlTest, ValarrayTest) {
  std::valarray<int> v = {1, 2, 3}, w = {7, 8, 9}, s = v + 2 * w;
  // v = sin(s); // = {sin(s[0]), sin(s[1]), sin(s[2])}

  EXPECT_EQ(s[0], 15);
  EXPECT_EQ(s[1], 18);
  EXPECT_EQ(s[2], 21);
}
