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