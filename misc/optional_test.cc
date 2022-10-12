#include <gtest/gtest.h>
#include <optional>
#include <vector>

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

/////  std::in_place test /////

struct CharInfo {
  CharInfo(char c, int i) : Upper(c), Pos(i) {}
  char Upper;
  int Pos;
};

std::vector<std::optional<CharInfo>>
findFirstUpper(const std::vector<std::string> &V) {
  std::vector<std::optional<CharInfo>> Ret; 

  // 对象所有权转移，左值引用转化为右值引用。
  // 右值引用不能取地址。
  for(auto &&T : V) {
    int i;
    for (i = 0; i < T.length(); ++i) {
      if (char c = T[i]; isupper(c)) {
        Ret.push_back(std::in_place, c, i);
        // 使用 std::in_place 指示在原地进行构造对象。
        // push_back 有构造和移动的操作，性能低。
        break; 
      }

      if (i == T.length())
        Ret.emplace_back();
    }
  }
  return Ret;
}

TEST(std_optional_test, in_place_test) {
  std::vector<std::string> Strs{"Nothing", "found"};
  std::vector<std::optional<CharInfo>> Res = findFirstUpper(Strs);

  std::stringstream oss;
  testing::internal::CaptureStdout();

  if (Res.has_value()) {
    std::cout << Res[0]->Upper << "at" << Res[0]->Pos << "\n";
  } else {
    std::cout << "Nothing found\n";
  }

  oss << "N at 0\n";

  std::string act_output = testing::internal::GetCapturedStdout();

  EXPECT_TRUE(oss.str() == act_output);
}