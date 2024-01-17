#ifndef SRC_MODEL_CALCULATORMODEL_H
#define SRC_MODEL_CALCULATORMODEL_H

#include <math.h>

#include <cstring>
#include <iostream>
#include <stack>

namespace s21 {
// Token types used to represent different elements of a mathematical
// expression.
enum TokenType {
  kNumber,         // Number
  kPlus,           // Addition operator
  kMinus,          // Subtraction operator
  kMultiply,       // Multiplication operator
  kDivide,         // Division operator
  kMod,            // Modulus operator
  kPow,            // Exponentiation operator
  kSqrt,           // Square root function
  kCos,            // Cosine function
  kSin,            // Sine function
  kTan,            // Tangent function
  kAcos,           // Arccosine function
  kAsin,           // Arcsine function
  kAtan,           // Arctangent function
  kLn,             // Natural logarithm function
  kLog,            // Base-10 logarithm function
  kOpenBrackets,   // Opening bracket
  kCloseBrackets,  // Closing bracket
};

// Token priorities that determine their significance during calculations.
enum TokenPriority {
  kLow,     // Low priority
  kMiddle,  // Medium priority
  kUnary,   // Unary operators
  kHigh,    // High priority
  kBracket  // Brackets
};

// Structure representing a token in the mathematical expression.
struct Token {
  double value{};
  TokenType type{};
  TokenPriority priority{};

  Token(double value, TokenType type, TokenPriority priority)
      : value(value), priority(priority), type(type) {}
  ~Token() {}
};

struct Calculator {
  int operation{};
  double left_operand{};
  double right_operand{};
  double result{};

  // Constructor
  Calculator(int operation) : operation(operation) {}
  // Destructor
  ~Calculator(){};

  // Perform arithmetic calculations based on the selected operation.
  void ArithmeticCalculation() {
    switch (operation) {
      case kPlus:
        result = right_operand + left_operand;
        break;
      case kMinus:
        result = right_operand - left_operand;
        break;
      case kMultiply:
        result = right_operand * left_operand;
        break;
      case kDivide:
        result = right_operand / left_operand;
        break;
      case kPow:
        result = pow(right_operand, left_operand);
        break;
      case kMod:
        result = fmod(right_operand, left_operand);
        break;
    }
  }

  // Perform trigonometric calculations based on the selected operation.
  void TrigonometricCalculation() {
    switch (operation) {
      case kCos:
        result = cos(left_operand);
        break;
      case kSin:
        result = sin(left_operand);
        break;
      case kTan:
        result = tan(left_operand);
        break;
      case kAcos:
        result = acos(left_operand);
        break;
      case kAsin:
        result = asin(left_operand);
        break;
      case kAtan:
        result = atan(left_operand);
        break;
      case kSqrt:
        result = sqrt(left_operand);
        break;
      case kLn:
        result = log(left_operand);
        break;
      case kLog:
        result = log10(left_operand);
        break;
    }
  }
};

class CalculatorModel {
 public:
  CalculatorModel() {}
  ~CalculatorModel() {}

  double GetResult() const { return result_; }
  int GetError() const { return error_; }

  void SetError(int number) { error_ = number; }

  void RunModelCalculation(std::string problem, std::string value);

 private:
  int error_{};
  double result_{};
  std::stack<Token> stack_{};

  void MainCalculation();
  // Parsing and Tokenizing Functions
  int IsUnar(std::string& problem, int& step);
  int HandleExponentPrefix(const std::string& problem, int startIndex);
  void ParseNumber(std::string& problem, int& step);
  void PasteValue(std::string& problem, const std::string& number);
  void ParseOperators(std::string& problem, int& step);
  void ValidateString(std::string& problem);
  void PasteValue(std::string& problem, std::string& number);
  void ParseString(std::string& problem);
  // Stack and Calculation Functions
  void ReverseStack();
  int IsFunctionOrBracket();
  int IsDoublePow(std::stack<Token>& operands);
  int IsBracket(std::stack<Token>& numbers);
  void Calculate(std::stack<Token>& numbers, int operation);
};
}  // namespace s21

#endif  // SRC_MODEL_CALCULATORMODEL_H
