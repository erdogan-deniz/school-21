/**
 * @file calculatormodel.h
 * @brief Calculator model — Dijkstra's shunting-yard tokeniser +
 *        infix-to-RPN converter + RPN evaluator.
 *
 * The model is the entire business logic of `SmartCalc_v2.0`: it
 * accepts a textual infix expression (optionally containing the
 * literal `x`), tokenises it, applies the shunting-yard algorithm to
 * convert to Reverse Polish Notation, then evaluates the RPN stack.
 * Error state is exposed via @ref GetError; the numeric result via
 * @ref GetResult.
 *
 * The arithmetic and trigonometric sub-evaluations live in
 * @ref Calculator (helper struct). @ref Token + @ref TokenType +
 * @ref TokenPriority form the parser's vocabulary.
 */

#ifndef SRC_MODEL_CALCULATORMODEL_H
#define SRC_MODEL_CALCULATORMODEL_H

#include <math.h>

#include <cstring>
#include <iostream>
#include <stack>

namespace s21 {

/**
 * @brief Token kinds emitted by the tokeniser and consumed by the
 *        shunting-yard / RPN evaluator.
 */
enum TokenType {
  kNumber,         ///< Numeric literal (value lives in @ref Token::value).
  kPlus,           ///< Addition operator.
  kMinus,          ///< Subtraction operator.
  kMultiply,       ///< Multiplication operator.
  kDivide,         ///< Division operator.
  kMod,            ///< Modulus operator.
  kPow,            ///< Exponentiation operator.
  kSqrt,           ///< Square-root function.
  kCos,            ///< Cosine function.
  kSin,            ///< Sine function.
  kTan,            ///< Tangent function.
  kAcos,           ///< Arc-cosine function.
  kAsin,           ///< Arc-sine function.
  kAtan,           ///< Arc-tangent function.
  kLn,             ///< Natural logarithm function.
  kLog,            ///< Base-10 logarithm function.
  kOpenBrackets,   ///< Opening bracket `(`.
  kCloseBrackets,  ///< Closing bracket `)`.
};

/**
 * @brief Operator priorities used by the shunting-yard algorithm.
 *
 * Higher value = binds tighter. Brackets sit above everything so they
 * always stay on the stack until their matching close.
 */
enum TokenPriority {
  kLow,     ///< Low priority (+, -).
  kMiddle,  ///< Medium priority (*, /, mod).
  kUnary,   ///< Unary +/− priority.
  kHigh,    ///< High priority (^, functions).
  kBracket  ///< Brackets — top of the priority stack.
};

/**
 * @brief Single token: a numeric value (if @ref TokenType is
 *        @ref kNumber), an operator, a function, or a bracket.
 */
struct Token {
  double value{};
  TokenType type{};
  TokenPriority priority{};

  Token(double value, TokenType type, TokenPriority priority)
      : value(value), priority(priority), type(type) {}
  ~Token() {}
};

/**
 * @brief Stateless-ish helper bundling left / right operand and the
 *        operation kind; performs one arithmetic or trigonometric
 *        evaluation per invocation.
 */
struct Calculator {
  int operation{};
  double left_operand{};
  double right_operand{};
  double result{};

  Calculator(int operation) : operation(operation) {}
  ~Calculator() {};

  /** @brief Evaluate the binary arithmetic operation in @ref operation. */
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

  /** @brief Evaluate the unary trigonometric / log / sqrt operation. */
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

/**
 * @brief Calculator business logic — the **M** of `SmartCalc_v2.0`'s
 *        MVC layering.
 *
 * Owns the parser stack and the result / error flag. Public API is
 * intentionally minimal: feed an expression with
 * @ref RunModelCalculation, read @ref GetResult and @ref GetError.
 */
class CalculatorModel {
 public:
  CalculatorModel() {}
  ~CalculatorModel() {}

  /** @brief Last computed numeric result. */
  double GetResult() const { return result_; }

  /** @brief Error flag from the most recent @ref RunModelCalculation;
   *         0 = OK, non-zero = parse / domain error. */
  int GetError() const { return error_; }

  /** @brief Override the error flag (used by the controller to clear state). */
  void SetError(int number) { error_ = number; }

  /**
   * @brief Tokenise, convert to RPN, evaluate.
   * @param problem Infix expression; may contain the literal `x`.
   * @param value Stringified value substituted for every `x` occurrence.
   */
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
