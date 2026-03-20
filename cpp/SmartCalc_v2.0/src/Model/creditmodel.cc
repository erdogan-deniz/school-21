#include "creditmodel.h"

#include <iostream>

namespace s21 {
// Calculate credit results based on the specified period and payment type.
CreditResult& CreditModel::CalculateResult(CreditInfo& info) {
  info_ = info;

  if (info_.period == "years") {
    info_.months *= 12;
  }

  if (info_.payment == "annually") {
    CalculateAnnually();
    result_.min_pay = 0;
  } else {
    CalculateDifferentiated();
  }
  return result_;
}

// Calculate credit results using the annual payment approach.
void CreditModel::CalculateAnnually() {
  double i = info_.interest / 12 / 100;
  double n = pow((1 + i), info_.months);
  double coefficient = i * n / (n - 1);
  double tmp = coefficient * info_.sum;
  result_.max_pay = round(tmp * 100) / 100;
  result_.overpay = result_.max_pay * info_.months - info_.sum;
  result_.sum_total = info_.sum + result_.overpay;
}

// Calculate credit results using the differentiated payment approach.
void CreditModel::CalculateDifferentiated() {
  double net_int = 0;
  double credit_body = info_.sum;
  double month_pay = info_.sum / info_.months;
  for (int n = 0; n < info_.months; n++) {
    net_int = credit_body * info_.interest / 100 / 12;
    if (n == 0) {
      result_.max_pay = net_int + month_pay;
    }
    credit_body -= month_pay;
    result_.overpay += net_int;
  }
  result_.min_pay = net_int + month_pay;
  result_.sum_total = info_.sum + result_.overpay;
}
}  // namespace s21