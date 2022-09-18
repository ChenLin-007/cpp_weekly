//
// Created by CL on 2022/9/18.
//

#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <string_view>

TEST(string_view_test, basic) {
  std::stringstream oss;

  testing::internal::CaptureStdout();

  const char *cstr = "string_view test";
  std::string_view sv1(cstr);
  std::string_view sv2(cstr, 4);
  std::cout << "sv1: " << sv1 << ", sv2: " << sv2 << std::endl;
  oss << "sv1: string_view test, sv2: stri" << std::endl;

  std::string str = "string_view test";
  std::string_view  sv3{str.data()};
  std::string_view  sv4{str.data(), 4};
  std::cout << "sv3: " << sv3 << ", sv4: " << sv4 << std::endl;
  oss<< "sv3: string_view test, sv4: stri" << std::endl;

  std::string act_output = testing::internal::GetCapturedStdout();

  EXPECT_TRUE(act_output == oss.str());
}

class Timer {
private:
  std::string Title;
  std::chrono::high_resolution_clock::time_point Start, Stop;

public:
  Timer(const std::string &Title) : Title(Title) {
    Start = std::chrono::high_resolution_clock::now();
  }

  ~Timer() {stop();}

  void stop() {
    Stop = std::chrono::high_resolution_clock::now();
    std::chrono::milliseconds ms = 
        std::chrono::duration_cast<std::chrono::milliseconds>(Stop - Start);

    std::cout << "Title " << (ms.count()) * 0.001 << "s\n";
  }
};

void FunctionWithString(const std::string &Str) {}
void FunctionWithString(const std::string_view &Sv) {}

TEST(string_view_test, time_test) {
  {
    Timer T("std::string");
    for (unsigned i = 0; i < 1000000; ++i) {
      std::string Name = "Lin Chen";
      std::string FirstName = Name.substr(0, 3);
      std::string LastName = Name.substr(4, 4);
      FunctionWithString(FirstName);
      FunctionWithString(LastName);
    }
  }

  {
    Timer T("std::string_view");
    for (unsigned i = 0; i < 1000000; ++i) {
      std::string Name = "Lin Chen";
      std::string_view FirstName = std::string_view(Name.data(), 3);
      std::string_view LastName = std::string_view(Name.data(), 4);
      FunctionWithString(FirstName);
      FunctionWithString(LastName);
    }
  }
}