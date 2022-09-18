#include <gtest/gtest.h>
#include <iostream>
#include <fstream>
#include <sstream>

void write_something(std::ostream &os) {
  os << "Hi stream, did you know that 3 * 3 = " << 3 * 3 << std::endl;
}

TEST(IOTest, coutTest) {
  std::string expected_str = "Hi stream, did you know that 3 * 3 = 9\n";
  testing::internal::CaptureStdout();
  write_something(std::cout);

  std::string act_output = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(expected_str == act_output);
}


