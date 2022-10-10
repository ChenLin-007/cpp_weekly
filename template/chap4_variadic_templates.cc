#include <gtest/gtest.h>

template<typename T>
void print(T arg) { std::cout << arg << '\n'; }

template<typename T, typename... Types>
void print(T firstArg, Types... args) {
  print(firstArg);
  print(args...);
}

TEST(chap4_variadic_templates, print_test) {
  std::stringstream oss;

  // start to capture stdout.
  testing::internal::CaptureStdout();

  print("Hello", "world");
  oss << "Hello\nworld\n";

  std::string act_output = testing::internal::GetCapturedStdout();

  EXPECT_TRUE(oss.str() == act_output);
}