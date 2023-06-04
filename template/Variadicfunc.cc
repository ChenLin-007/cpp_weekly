
#include <iostream>
#include <gtest/gtest.h>

template <typename T>
T add(T a, T b)
{
return a + b;
}
template <typename T, typename ...Ts> // [1]
T add(T t, Ts ... rest) // [2]
{
return t + add(rest...); // [3]
}

TEST(ClassTemplate, VariadicTest) {
  int sum = add(1, 2, 3, 4);

  EXPECT_EQ(sum, 10);
}
