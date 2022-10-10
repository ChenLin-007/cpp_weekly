#include <gtest/gtest.h>
#include <iostream>

TEST(Chap_1_Function_Template, max1_test) {
  std::stringstream oss;
  
  // 使用 CaptureStdout 捕获标准输出.
  testing::internal::CaptureStdout();

  int i = 42;
  std::cout << "max(7, i): " << std::max(7, i) << "\n";
  oss << "max(7, i): 42\n";

  std::string act_output = testing::internal::GetCapturedStdout();
  std::cout << "Expected output: \n" << oss.str() << "\n"
            << "Actual output: \n" << act_output << "\n";

  EXPECT_TRUE(oss.str() == act_output);
}