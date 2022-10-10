#include <gtest/gtest.h>
#include <functional>
#include <iostream>

/*
  使用 std::ref 在模板传参的时候传入引用。结合 std::bind 一起使用
*/

void f(int &n1, int &n2, const int &n3) {
  std::cout << "In function: " << n1 << ' ' << n2 << " " << n3 << "\n";
  ++n1;
  ++n2; 
}

TEST(ref_cref_test, basic_test) {
  int n1 = 1, n2 = 2, n3 = 3;
  std::function<void()> bound_f = std::bind(f, n1, std::ref(n2), std::cref(n3));

  n1 = 10;
  n2 = 11;
  n3 = 12;

  std::stringstream oss;
  testing::internal::CaptureStdout();

  std::cout << "Before function: " << n1 << ' ' << n2 << ' ' << n3 << '\n';
  oss << "Before function: 10 11 12\n";

  bound_f();
  oss << "In function: 1 11 12\n";

  std::cout << "After function: " << n1 << ' ' << n2 << ' ' << n3 << '\n';
  oss << "After function: 10 12 12\n";

  std::string act_output = testing::internal::GetCapturedStdout();

  EXPECT_TRUE(oss.str() == act_output);
}