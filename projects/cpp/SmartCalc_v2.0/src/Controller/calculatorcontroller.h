#ifndef SRC_CONTROLLER_CALCULATORCONTROLLER_H
#define SRC_CONTROLLER_CALCULATORCONTROLLER_H

#include "../Model/calculatormodel.h"

namespace s21 {
class CalculatorController {
 public:
  CalculatorController(){};
  ~CalculatorController(){};
  // Getters
  double GetResult() const { return model_.GetResult(); }
  int GetError() const { return model_.GetError(); }

  // Setter
  void SetError(int number) { model_.SetError(number); }

  // Calculate result
  void Run(std::string problem, std::string value) {
    model_.RunModelCalculation(problem, value);
  }

 private:
  CalculatorModel model_;
};
}  // namespace s21
#endif  // SRC_CONTROLLER_CALCULATORCONTROLLER_H
