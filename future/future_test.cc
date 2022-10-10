//
// Created by CL on 2022/9/28.
//
#include "timer.h"
#include <gtest/gtest.h>
#include <future>
#include <random>

std::set<int> make_sorted_random(const size_t num_elems) {
  std::set<int> retval;
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, num_elems - 1);


  std::generate_n(std::inserter(retval, retval.end()), num_elems, [&]() {return dis(gen);});

  return retval;
}

/*
  async & future
  std::async 开启一个异步任务，后续调用其结果. 返回一个future 对象。

  如果获取异步任务结果，std::future::get. 阻塞当前任务，知道获取异步任务的结果。
*/
TEST(std_future_test, basic_test) {
  {
    Timer("std::future");
    auto f1 = std::async(make_sorted_random, 1000000);
    f1.get();
    std::cout << std::async(make_sorted_random, 1000000).get().size() << "\n";
  }
}

int add(int a, int b) {
  std::cout << "work thread = " << std::this_thread::get_id() << std::endl;
  std::this_thread::sleep_for(std::chrono::milliseconds(3000));
  return a + b;
}

/*
  std::launch::deferred 挂起任务。
*/
TEST(std_future_test, deferred_task_test) {
  Timer("future deferred task test.");
  std::cout << "main thread = " << std::this_thread::get_id() << std::endl;
  std::future<int> result = std::async(std::launch::deferred, add , 2, 3);
  std::this_thread::sleep_for(std::chrono::milliseconds(3000));

  std::cout << result.get() << std::endl;
}

TEST(std_future_test, async_task_test) {
  Timer("future deferred task test.");
  std::cout << "\nmain thread = " << std::this_thread::get_id() << std::endl;

  // exection when start.
  std::future<int> result = std::async(std::launch::async, add, 2, 3);
  
  // main thread sleep 3s.
  std::this_thread::sleep_for(std::chrono::milliseconds(3000));

  std::cout << "sub thread's result = " << result.get() << std::endl;
}