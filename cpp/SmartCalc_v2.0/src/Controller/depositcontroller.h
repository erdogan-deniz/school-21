/**
 * @file depositcontroller.h
 * @brief Thin controller binding @ref s21::DepositModel to the Qt view.
 *
 * Mirrors the @ref s21::CreditController pattern: a single-method
 * facade that forwards the @ref s21::DepositInfo payload to the model
 * and returns the @ref s21::DepositResult unchanged.
 */

#ifndef SRC_CONTROLLER_DEPOSITCONTROLLER_H
#define SRC_CONTROLLER_DEPOSITCONTROLLER_H

#include "../Model/depositmodel.h"

namespace s21 {

/**
 * @brief Facade over @ref DepositModel for the Qt view.
 */
class DepositController {
 public:
  DepositController() {};
  ~DepositController() {};

  /**
   * @brief Compute deposit profitability given the input parameters.
   * @param deposit_info Input parameters (sum, days/months, interest,
   *                     tax rate, @ref Frequency).
   * @return Reference to the model's @ref DepositResult (income, tax,
   *         end sum). Lifetime tied to the controller instance.
   */
  DepositResult& Run(DepositInfo& deposit_info) {
    return model_.Calculate(deposit_info);
  }

 private:
  DepositModel model_{};
};

}  // namespace s21
#endif  // SRC_CONTROLLER_DEPOSITCONTROLLER_H
