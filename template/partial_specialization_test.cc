#include <gtest/gtest.h>
#include <complex>

/*
 * 函数部分特例化: 
 */

//################# 方式1 : 函数重载 ##################################
template <typename T> inline T my_abs(const T &x) { return x < T(0) ? -x : x; }

template <typename T> inline T my_abs(const std::complex<T> &x) {
  return std::sqrt(std::real(x) * std::real(x) + std::imag(x) * std::imag(x));
}

TEST(partial_specialization, basic_test) {
  std::complex<float> a{3, 4};
  std::stringstream oss;
  testing::internal::CaptureStdout();

  std::cout << "::my_abs(std::complex<float>(3, 4)) = " << ::my_abs(a)
            << std::endl;
  oss << "::my_abs(std::complex<float>(3, 4)) = 5\n";

  std::string act_output = testing::internal::GetCapturedStdout();

  EXPECT_TRUE(act_output == oss.str());          
}