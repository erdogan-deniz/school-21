#ifndef SRC_MODEL_CREDIT_H
#define SRC_MODEL_CREDIT_H

#include <cmath>
#include <string>

namespace s21 {

// Struct to hold credit information.
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

// Struct to hold calculated credit results.
struct CreditResult {
  double max_pay{};
  double min_pay{};
  double overpay{};
  double sum_total{};
  // Default constroctur
  CreditResult(){};
  // Destructor
  ~CreditResult(){};
};

// Class representing a credit calculation.
class CreditModel {
 public:
  // Constructors
  CreditModel(){};
  ~CreditModel() {}

  // Calculate result using CreditInfo struct
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
