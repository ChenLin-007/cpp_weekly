#include <iostream>
#include <gtest/gtest.h>

template <typename T>
constexpr T add(T a, T b) {
	return a + b;
}

TEST(BASIC, constexpr) {
	auto sum = add(1, 2);
	EXPECT_EQ(sum, 3);
}
