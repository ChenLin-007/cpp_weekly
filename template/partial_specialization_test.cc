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

//############### 方式2：重载操作符 ###################################
template <typename T> struct abs_functor {
  T operator()(const T &X) { return X < T(0) ? -X : X; }
};

template <typename T> struct abs_functor<std::complex<T>> {
  T operator() (const std::complex<T> &X) {
    return std::sqrt(std::real(X) * std::real(X) + std::imag(X) * std::imag(X));
  }
};

template <typename T> decltype(auto) my_abs_functor(const T &X) {
  return abs_functor<T>()(X);
}

TEST(partial_specialization, reload_operator) {
  std::complex<float> a{3, 4};
  std::stringstream oss;
  testing::internal::CaptureStdout();

  std::cout << "::my_abs_functor(std::complex<float>(3, 4)) = "
            << my_abs_functor(a)
            << std::endl;
  oss << "::my_abs_functor(std::complex<float>(3, 4)) = 5\n";

  std::cout << "::my_abs_functor(-2) = "
            << my_abs_functor(-2)
            << std::endl;
  oss << "::my_abs_functor(-2) = 2\n";

  std::string act_output = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(act_output == oss.str());
}