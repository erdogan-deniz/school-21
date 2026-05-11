/**
 * @file calculatorcontroller.h
 * @brief Thin controller binding the calculator @ref s21::CalculatorModel
 *        to the Qt view (MVC's "C").
 *
 * The controller contains **no business logic** — it only forwards user
 * input to the model and exposes the model's state to the view. This
 * keeps the view ignorant of the model's internals: swapping the view
 * (e.g. CLI → web) requires no controller change.
 */

#ifndef SRC_CONTROLLER_CALCULATORCONTROLLER_H
#define SRC_CONTROLLER_CALCULATORCONTROLLER_H

#include "../Model/calculatormodel.h"

namespace s21 {

/**
 * @brief Facade over @ref CalculatorModel for the Qt view.
 *
 * Holds one model instance and exposes its result / error / Run entry
 * points. Every method delegates to the model — no logic lives here.
 */
class CalculatorController {
 public:
  CalculatorController() {};
  ~CalculatorController() {};

  /** @brief Last computed numeric result (0 on uninitialised). */
  double GetResult() const { return model_.GetResult(); }

  /** @brief Error code from the most recent Run; 0 = OK, non-zero = parse / domain error. */
  int GetError() const { return model_.GetError(); }

  /** @brief Override the error flag (useful for clearing prior error state from the view). */
  void SetError(int number) { model_.SetError(number); }

  /**
   * @brief Evaluate an arithmetic expression.
   * @param problem Infix expression possibly containing the literal `x`.
   * @param value String form of the value substituted for `x` (empty
   *              string if `problem` has no `x`).
   */
  void Run(std::string problem, std::string value) {
    model_.RunModelCalculation(problem, value);
  }

 private:
  CalculatorModel model_;  ///< Owned model — controller's only state.
};

}  // namespace s21
#endif  // SRC_CONTROLLER_CALCULATORCONTROLLER_H
