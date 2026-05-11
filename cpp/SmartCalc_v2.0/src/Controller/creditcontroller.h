/**
 * @file creditcontroller.h
 * @brief Thin controller binding @ref s21::CreditModel to the Qt view.
 *
 * Mirrors the @ref s21::CalculatorController pattern: a single-method
 * facade that forwards the @ref s21::CreditInfo payload to the model
 * and returns the @ref s21::CreditResult unchanged.
 */

#ifndef SRC_CONTROLLER_CREDITCONTROLLER_H
#define SRC_CONTROLLER_CREDITCONTROLLER_H

#include "../Model/creditmodel.h"

namespace s21 {

/**
 * @brief Facade over @ref CreditModel for the Qt view.
 */
class CreditController {
 public:
  CreditController() {};
  ~CreditController() {};

  /**
   * @brief Compute annuity or differentiated credit payments.
   * @param info Input parameters (sum, months, interest, period, payment type).
   * @return Reference to the model's @ref CreditResult (max/min payment,
   *         overpay, total). Lifetime tied to the controller instance.
   */
  CreditResult& Run(CreditInfo& info) { return model_.CalculateResult(info); }

 private:
  CreditModel model_{};
};

}  // namespace s21
#endif  // SRC_CONTROLLER_CREDITCONTROLLER_H
