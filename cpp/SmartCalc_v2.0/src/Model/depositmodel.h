/**
 * @file depositmodel.h
 * @brief Deposit-calculator model — interest accrual + tax adjustment.
 */

#ifndef SRC_MODEL_DEPOSIT_H
#define SRC_MODEL_DEPOSIT_H

#include <cmath>
#include <iostream>

namespace s21 {

/**
 * @brief Interest-accrual frequency selector for @ref DepositModel.
 *
 * `kEnd` means accrue once at maturity; the others compound at the
 * stated cadence.
 */
enum Frequency { kDaily, kMonthly, kQuarterly, kHalfYearly, kYearly, kEnd };

/**
 * @brief Inputs to a deposit calculation: principal, term, rate, tax
 *        rate, accrual @ref Frequency.
 */
struct DepositInfo {
  int days{};
  int months{};
  double start_sum{};
  double interest{};
  double tax{};
  Frequency frequency{};

  DepositInfo() {}
  ~DepositInfo() {}
};

/**
 * @brief Outputs of a deposit calculation: accrued interest, tax due,
 *        principal-plus-interest end balance.
 */
struct DepositResult {
  int income{};
  int tax{};
  int end_sum{};

  DepositResult() {}
  ~DepositResult() {}
};

/**
 * @brief Deposit-calculator business logic.
 *
 * Dispatches to one of @ref CalculateDaily / @ref CalculateMonthly /
 * @ref CalculateQuarterly / @ref CalculateHalfYear /
 * @ref CalculateYearly / @ref CalculateEnd based on `info.frequency`,
 * then applies the tax adjustment.
 */
class DepositModel {
 public:
  DepositModel() {};

  /** @brief Copy constructor — defensive (the controller passes by &). */
  DepositModel(const DepositModel& other)
      : info_(other.info_), result_(other.result_) {}

  ~DepositModel() {};

  /**
   * @brief Compute deposit profitability for the given inputs.
   * @return Reference to the owned @ref DepositResult.
   */
  DepositResult& Calculate(DepositInfo& info_);

 private:
  DepositInfo info_{};
  DepositResult result_{};

  // Functions for deposit and tax calculations, as well as tax adjustment.
  void CalculateEnd();
  void CalculateDaily();
  void CalculateMonthly();
  void CalculateQuarterly();
  void CalculateHalfYear();
  void CalculateYearly();
  void CalculateTax();
  void AddTax();
};
}  // namespace s21
#endif  // SRC_MODEL_DEPOSIT_H
