#include <gtest/gtest.h>

#include "../Controller/calculatorcontroller.h"

class CalculatorControllerTest : public ::testing::Test {
 protected:
  s21::CalculatorController calculator;
};

TEST_F(CalculatorControllerTest, Test_1) {
  calculator.Run("(2+3)*5^2", "");
  ASSERT_EQ(calculator.GetError(), 0);
  ASSERT_DOUBLE_EQ(calculator.GetResult(), 125.0);
}

TEST_F(CalculatorControllerTest, Test_2) {
  calculator.Run("1/2+(2+3)/(sin(9-2)^2-6/7)", "");
  ASSERT_EQ(calculator.GetError(), 0);
  ASSERT_NEAR(calculator.GetResult(), -11.250565, 1e-6);
}

TEST_F(CalculatorControllerTest, Test_3) {
  calculator.Run("(-12.3)+4", "");
  ASSERT_EQ(calculator.GetError(), 0);
  ASSERT_NEAR(calculator.GetResult(), -8.3, 1e-6);
}

TEST_F(CalculatorControllerTest, Test_4) {
  calculator.Run("(12)+(-12.00006)", "");
  ASSERT_EQ(calculator.GetError(), 0);
  ASSERT_NEAR(calculator.GetResult(), -0.00006, 1e-6);
}

TEST_F(CalculatorControllerTest, Test_5) {
  calculator.Run("(-(-(-10)))-(-(-10))", "");
  ASSERT_EQ(calculator.GetError(), 0);
  ASSERT_NEAR(calculator.GetResult(), -20, 1e-6);
}

TEST_F(CalculatorControllerTest, Test_6) {
  calculator.Run("(-1.2)-1.2-2.4-4.8", "");
  ASSERT_EQ(calculator.GetError(), 0);
  ASSERT_NEAR(calculator.GetResult(), -9.6, 1e-6);
}

TEST_F(CalculatorControllerTest, Test_7) {
  calculator.Run("(12)*(-1.0006)", "");
  ASSERT_EQ(calculator.GetError(), 0);
  ASSERT_NEAR(calculator.GetResult(), -12.0072, 1e-6);
}

TEST_F(CalculatorControllerTest, Test_8) {
  calculator.Run("((12)*(-1.0006)", "");
  ASSERT_EQ(calculator.GetError(), 1);
}

TEST_F(CalculatorControllerTest, Test_9) {
  calculator.Run("1.1.1 + 2", "");
  ASSERT_EQ(calculator.GetError(), 1);
}

TEST_F(CalculatorControllerTest, Test_10) {
  calculator.Run("(.1.1.1 + 2.)2", "");
  ASSERT_EQ(calculator.GetError(), 1);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
