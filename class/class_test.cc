//
// Created by CL on 2022/9/17.
//

#include <gtest/gtest.h>
#include <iostream>
#include <initializer_list>

class Complex{
public:
  Complex(double rnew, double inew) : r(rnew), i(inew) {};

private:
  double r;
  double i;
};

