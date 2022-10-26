#include <algorithm>
#include <fmt/format.h>
#include <functional>
#include <ranges>
#include <utility>
#include <gtest/gtest.h>

namespace std {
template<typename Func, typename... Param>
auto bind_back(Func &&func, Param &&... param) {
  // std::forward 原封不动的传递参数
  return [func = std::forward<Func>(func),
          ... param = std::forward<Param>(param)]<typename... Inner>(
          Inner &&...inner) -> decltype(auto) {
    return std::invoke(func, std::forward<Inner>(inner)..., param...);
  };
}
}

struct Point {
  int x;
  int y;

  void displace(int x_displacement, int y_displacement) {
    x += x_displacement;
    y += y_displacement;
  }

  Point operator+(Point displacement) const {
    return Point{x + displacement.x, y + displacement.y};
  }

  void print() const {
    fmt::format("{{{}, {}}}\n", x, y);
  }
};

std::vector<Point> get_data() { return {{1,2}, {3,4}, {5,6}, {42,78}}; }

TEST(std_bind_back, basic) {
  auto data = get_data();
  std::stringstream oss;
  testing::internal::CaptureStdout();

  std::ranges::for_each(data, std::bind_back(&Point::displace, 6, 5));
  std::ranges::for_each(data, &Point::print);

  oss << "{7, 7}\n"
      << "{9, 9}\n"
      << "{11, 11}\n"
      << "{48, 83}\n";

  std::string act_output = testing::internal::GetCapturedStdout();

  EXPECT_TRUE(act_output == oss.str());
}