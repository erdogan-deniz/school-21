#include "calculatormodel.h"

namespace s21 {
// Reverse current stack
void CalculatorModel::ReverseStack() {
  std::stack<Token> tempStack;
  while (!stack_.empty()) {
    tempStack.push(stack_.top());
    stack_.pop();
  }
  stack_ = std::move(tempStack);
}

// Check if the top token in the stack is either an opening bracket or has a
// high priority
int CalculatorModel::IsFunctionOrBracket() {
  return stack_.top().type == kOpenBrackets || stack_.top().priority == kHigh;
}

// Paste the value of x to math problem
void CalculatorModel::PasteValue(std::string& problem, std::string& number) {
  size_t index = problem.find('x');
  while (index != std::string::npos) {
    if ((index == 0 || !isalpha(problem[index - 1])) &&
        (index == problem.size() - 1 || !isalpha(problem[index + 1]))) {
      problem.replace(index, 1, number);
    }
    index = problem.find('x', index + 1);
  }
}

// Validate string
void CalculatorModel::ValidateString(std::string& problem) {
  int brackets = 0;
  for (int step = 0; step < (int)problem.length(); step++) {
    if (isdigit(problem[step]) && problem[step + 1] == '.' &&
        isdigit(problem[step + 2]) && problem[step + 3] == '.') {
      error_ = 1;
    }
    if (problem[step] == '(') {
      brackets++;
      if (problem[step - 1] == '.') {
        error_ = 1;
      } else if (problem[step + 1] == '.') {
        error_ = 1;
      } else if (problem[step + 1] == ')') {
        error_ = 1;
      } else if (problem[step + 1] == '-' && problem[step + 2] == ')') {
        error_ = 1;
      }
    }
    if (problem[step] == ')') {
      brackets--;
      if (isdigit(problem[step + 1])) {
        error_ = 1;
      }
    }
  }
  if (brackets != 0) {
    error_ = 1;
  }
}

//  Determine is it unar plus or minus
int CalculatorModel::IsUnar(std::string& problem, int& step) {
  if (stack_.empty()) {
    return 0;
  }
  int result = 0, type = stack_.top().type;
  if ((type > 1 && type < 9) || type == kOpenBrackets) {
    if (strchr("0123456789aclst(", problem[step + 1])) {
      if (problem[step] == '+') {
        result = 2;
      } else if (problem[step] == '-') {
        result = 1;
      }
    }
  }
  return result;
}

// Handle with exponent
int CalculatorModel::HandleExponentPrefix(const std::string& problem,
                                          int startIndex) {
  size_t endIndex = startIndex;

  if (isdigit(problem[endIndex]) && problem[endIndex + 1] == 'e' &&
      (problem[endIndex + 2] == '-' || problem[endIndex + 2] == '+')) {
    endIndex += 3;
  }

  if (endIndex + 1 < problem.length() && isdigit(problem[endIndex]) &&
      problem[endIndex + 1] == 'e') {
    endIndex += 2;
  }

  return endIndex;
}

// Parses numbers from a string
void CalculatorModel::ParseNumber(std::string& problem, int& step) {
  int endIndex = step;

  endIndex = HandleExponentPrefix(problem, endIndex);

  bool foundExponent = false;
  while (endIndex < problem.length() &&
         (isdigit(problem[endIndex]) || problem[endIndex] == '.' ||
          problem[endIndex] == 'e' ||
          (problem[endIndex] == '-' &&
           (endIndex == step || problem[endIndex - 1] == 'e')) ||
          (problem[endIndex] == '+' &&
           (endIndex == step || problem[endIndex - 1] == 'e')))) {
    if (problem[endIndex] == 'e' && !foundExponent) {
      foundExponent = true;
    } else if (problem[endIndex] == 'e' && foundExponent) {
      break;
    }
    endIndex++;
  }

  std::string numberStr = problem.substr(step, endIndex - step);

  double number = std::stod(numberStr);
  stack_.push({number, kNumber, kLow});
  step = endIndex - 1;
}

// Parse and convert string to stack
void CalculatorModel::ParseString(std::string& problem) {
  for (int step = 0; step < problem.length(); step++) {
    if (problem[step] == ' ') {
      continue;
    } else if (problem[step] == '-' && step == 0) {
      stack_.push({-1, kNumber, kLow});
      stack_.push({0, kMultiply, kUnary});
    } else if (problem[step] == '+' && step == 0) {
      stack_.push({1, kNumber, kLow});
      stack_.push({0, kMultiply, kUnary});
    } else if (isdigit(problem[step])) {
      ParseNumber(problem, step);
    } else if (IsUnar(problem, step) == 1) {
      stack_.push({-1, kNumber, kLow});
      stack_.push({0, kMultiply, kUnary});
    } else if (IsUnar(problem, step) == 2) {
      stack_.push({1, kNumber, kLow});
      stack_.push({0, kMultiply, kUnary});
    } else if (problem[step] == '+') {
      stack_.push({0, kPlus, kLow});
    } else if (problem[step] == '-') {
      stack_.push({0, kMinus, kLow});
    } else if (problem[step] == '*') {
      stack_.push({0, kMultiply, kMiddle});
    } else if (problem[step] == '/') {
      stack_.push({0, kDivide, kMiddle});
    } else if (problem.compare(step, 3, "mod") == 0) {
      stack_.push({0, kMod, kMiddle});
      step += 2;
    } else if (problem[step] == '^') {
      stack_.push({0, kPow, kUnary});
    } else if (problem.compare(step, 3, "cos") == 0) {
      stack_.push({0, kCos, kHigh});
      step += 2;
    } else if (problem.compare(step, 3, "sin") == 0) {
      stack_.push({0, kSin, kHigh});
      step += 2;
    } else if (problem.compare(step, 3, "tan") == 0) {
      stack_.push({0, kTan, kHigh});
      step += 2;
    } else if (problem.compare(step, 4, "acos") == 0) {
      stack_.push({0, kAcos, kHigh});
      step += 3;
    } else if (problem.compare(step, 4, "asin") == 0) {
      stack_.push({0, kAsin, kHigh});
      step += 3;
    } else if (problem.compare(step, 4, "atan") == 0) {
      stack_.push({0, kAtan, kHigh});
      step += 3;
    } else if (problem.compare(step, 2, "ln") == 0) {
      stack_.push({0, kLn, kHigh});
      step += 1;
    } else if (problem.compare(step, 4, "sqrt") == 0) {
      stack_.push({0, kSqrt, kHigh});
      step += 3;
    } else if (problem.compare(step, 3, "log") == 0) {
      stack_.push({0, kLog, kHigh});
      step += 2;
    } else if (problem[step] == '(') {
      stack_.push({0, kOpenBrackets, kBracket});
    } else if (problem[step] == ')') {
      stack_.push({0, kCloseBrackets, kBracket});
    }
  }
}

//  Perform the calculation of an arithmetic or trigonometric operation.
void CalculatorModel::Calculate(std::stack<Token>& numbers, int operation) {
  if (!numbers.empty()) {
    Calculator calc(operation);
    if (calc.operation < 7) {
      calc.left_operand = numbers.top().value;
      numbers.pop();
      if (!numbers.empty()) {
        calc.right_operand = numbers.top().value;
        numbers.pop();
      }
      calc.ArithmeticCalculation();
    } else {
      calc.left_operand = numbers.top().value;
      numbers.pop();
      calc.TrigonometricCalculation();
    }
    numbers.push({calc.result, kNumber, kLow});
  }
}

// Check if the top token in the stack and the top token in the given stack of
// operands are both of type kPow
int CalculatorModel::IsDoublePow(std::stack<Token>& operands) {
  return stack_.top().type == kPow && operands.top().type == kPow;
}

// Check if the top token in the given stack of numbers is either an opening or
// closing bracket
int CalculatorModel::IsBracket(std::stack<Token>& numbers) {
  return !numbers.empty() && (numbers.top().type == kOpenBrackets ||
                              numbers.top().type == kCloseBrackets);
}

// Perform the main calculation using the Reverse Polish Notation
void CalculatorModel::MainCalculation() {
  std::stack<Token> numbers{};
  std::stack<Token> operands{};

  ReverseStack();

  while (!stack_.empty()) {
    if (stack_.top().type == kNumber) {
      numbers.push(stack_.top());
    } else {
      if (operands.empty() || IsFunctionOrBracket()) {
        operands.push(stack_.top());
      } else if (stack_.top().type == kCloseBrackets) {
        while (operands.top().type != kOpenBrackets) {
          Calculate(numbers, (int)operands.top().type);
          operands.pop();
        }
        operands.pop();
        stack_.pop();
        continue;
      } else if (IsDoublePow(operands) ||
                 stack_.top().priority > operands.top().priority) {
        operands.push(stack_.top());
      } else if (stack_.top().priority <= operands.top().priority) {
        while (!operands.empty() &&
               stack_.top().priority <= operands.top().priority) {
          if (operands.top().type == kOpenBrackets) {
            break;
          }
          Calculate(numbers, (int)operands.top().type);
          operands.pop();
        }
        if (!stack_.empty()) {
          operands.push(stack_.top());
        }
      }
    }
    stack_.pop();
  }
  if (IsBracket(numbers)) {
    numbers.pop();
  }

  while (!operands.empty()) {
    Calculate(numbers, (int)operands.top().type);
    operands.pop();
  }
  result_ = numbers.top().value;
}

void CalculatorModel::RunModelCalculation(std::string problem,
                                          std::string value) {
  ValidateString(problem);
  if (error_ != 1) {
    PasteValue(problem, value);
    ParseString(problem);
    MainCalculation();
  }
}
}  // namespace s21