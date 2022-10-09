#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <iostream>
#include <string_view>

class Timer {
  std::string_view Title;
  std::chrono::high_resolution_clock::time_point Start;
  std::chrono::high_resolution_clock::time_point Stop;

public:
  Timer(const std::string_view &Title_) : Title(Title_) {
    Start = Stop = std::chrono::high_resolution_clock::now();
  }

  ~Timer() { stop(); }

  uint64_t eclipse() {
    Stop = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(Stop - Start).count();
  }

private:
  void stop() {
    if (Stop == Start)
      Stop = std::chrono::high_resolution_clock::now();
    std::chrono::nanoseconds ns =
            std::chrono::duration_cast<std::chrono::nanoseconds>(Stop - Start);
#ifndef NDEBUG
    std::cout << Title << " " << (ns.count()) * 0.001 << "s\n";
#endif
  }
};

#endif // TIMER_H