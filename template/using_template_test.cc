#include <gtest/gtest.h>

template<unsigned Order, typename Value> class Tensor {
  Value V[Order];

public:
  Tensor() = default;

  Value getV(unsigned Idx) {
    return (Idx >= Order ) ? V[Order - 1] : V[Idx];
  }
};

template<typename Value> using vector = Tensor<1, Value>;
template<typename Value> using matrix = Tensor<2, Value>;

TEST(using_template, basic_test) {
  std::stringstream oss;

  testing::internal::CaptureStdout();

  std::cout << "type of vector<float> is " << typeid(vector<float>).name() << "\n";
  oss << "type of vector<float> is 6TensorILj1EfE\n";

  std::cout << "type of matrix<float> is " << typeid(matrix<float>).name() << "\n";
  oss << "type of matrix<float> is 6TensorILj2EfE\n";

  std::string act_output = testing::internal::GetCapturedStdout();

  EXPECT_TRUE(act_output == oss.str());
}