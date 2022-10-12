#include <gtest/gtest.h>
#include <optional>

TEST(std_optional_test, value_or_test) {
  std::optional<int> offset{10};  // offset 的值只能是10。
  std::optional<int> total;       // total 只能是int 类型。

  std::stringstream oss;
  testing::internal::CaptureStdout();

  std::cout << offset.value_or(0) << std::endl;
  std::cout << total.value_or(1000.1) << std::endl;
  std::cout << total.value_or('a') << std::endl;

  oss << "10\n"
      << "1000\n"
      << "97\n";

  std::string act_output = testing::internal::GetCapturedStdout();

  EXPECT_TRUE(oss.str() == act_output);
}