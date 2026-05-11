/**
 * @file creditmodel.h
 * @brief Credit-calculator model — annuity / differentiated payment
 *        schedule computation.
 */

#ifndef SRC_MODEL_CREDIT_H
#define SRC_MODEL_CREDIT_H

#include <cmath>
#include <string>

namespace s21 {

/**
 * @brief Inputs to a credit calculation: principal, term, rate, plus
 *        period / payment-type discriminators.
 */
struct CreditInfo {
  double sum{};
  double months{};
  double interest{};
  std::string period{};
  std::string payment{};
  // Default constroctur
  CreditInfo() {}
  // Constroctur with parametrs
  CreditInfo(double sum, double months, double interest, std::string period,
             std::string payment)
      : sum(sum),
        months(months),
        interest(interest),
        period(period),
        payment(payment) {}
  // Destructor
  ~CreditInfo() {}
};

/**
 * @brief Outputs of a credit calculation: highest / lowest monthly
 *        payment, total overpayment, total amount paid.
 */
struct CreditResult {
  double max_pay{};
  double min_pay{};
  double overpay{};
  double sum_total{};
  // Default constroctur
  CreditResult() {};
  // Destructor
  ~CreditResult() {};
};

/**
 * @brief Credit-calculator business logic.
 *
 * Dispatches to annuity or differentiated formula based on
 * `info.payment` and writes the result into the owned
 * @ref CreditResult.
 */
class CreditModel {
 public:
  CreditModel() {};
  ~CreditModel() {}

  /**
   * @brief Compute credit schedule from the given @ref CreditInfo.
   * @return Reference to the owned @ref CreditResult (max/min pay,
   *         overpay, total sum).
   */
  CreditResult& CalculateResult(CreditInfo& info);

 private:
  CreditInfo info_;
  CreditResult result_;

  // Calculate credit results using the annual/differentiated payment
  void CalculateAnnually();
  void CalculateDifferentiated();
};
}  // namespace s21

#endif  // SRC_MODEL_CREDIT_H
