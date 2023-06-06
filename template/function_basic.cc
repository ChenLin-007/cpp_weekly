#include <iostream>
#include <gtest/gtest.h>

template <typename T>
constexpr T add(T a, T b) {
	return a + b;
}

// C++11 使用decltype辅助推导返回类型。
template<typename T, typename U>
auto decladd(T const & a, U const & b) -> decltype(a + b)
{
	return a + b;
}

TEST(BASIC, constexpr) {
	auto sum = add(1, 2);
	EXPECT_EQ(sum, 3);
}

TEST(BASIC, decltype) {
	auto re = decladd(1, 3.0);
	std::cout << "type: " << typeid(re).name() << std::endl;
}
