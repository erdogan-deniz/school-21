#include "depositmodel.h"

namespace s21 {

// Calculate implementation
DepositResult& DepositModel::Calculate(DepositInfo& info) {
  info_ = info;
  result_.income = 0;

  if (info_.frequency == Frequency::kDaily) {
    CalculateDaily();
  } else if (info_.frequency == Frequency::kMonthly) {
    CalculateMonthly();
  } else if (info_.frequency == Frequency::kQuarterly) {
    CalculateQuarterly();
  } else if (info_.frequency == Frequency::kHalfYearly) {
    CalculateHalfYear();
  } else if (info_.frequency == Frequency::kYearly) {
    CalculateYearly();
  } else {
    CalculateEnd();
  }

  if (!result_.income) {
    result_.income = result_.end_sum - info_.start_sum;
  }

  CalculateTax();
  return result_;
}
// Calculate end sum and income for deposits with "end" frequency.
void DepositModel::CalculateEnd() {
  result_.income =
      static_cast<int>(info_.start_sum * info_.interest * info_.days / 365);
  result_.end_sum = info_.start_sum + result_.income;
}

// Calculate end sum for deposits with "daily" frequency.
void DepositModel::CalculateDaily() {
  result_.end_sum =
      info_.start_sum * std::pow(1 + info_.interest / 365, info_.days);
}

// Calculate end sum for deposits with "monthly" frequency.
void DepositModel::CalculateMonthly() {
  result_.end_sum =
      info_.start_sum * std::pow(1 + info_.interest / 12, info_.months);
}

// Calculate end sum for deposits with "quarterly" frequency.
void DepositModel::CalculateQuarterly() {
  double quarters = static_cast<double>(info_.months) / 3.0;
  result_.end_sum =
      info_.start_sum * std::pow(1 + info_.interest / 4, quarters);
}

// Calculate end sum for deposits with "half-year" frequency.
void DepositModel::CalculateHalfYear() {
  double half_year = static_cast<double>(info_.months) / 6.0;
  result_.end_sum =
      info_.start_sum * std::pow(1 + info_.interest / 2, half_year);
}

// Calculate end sum for deposits with "yearly" frequency.
void DepositModel::CalculateYearly() {
  double years = static_cast<double>(info_.months) / 12.0;
  result_.end_sum = info_.start_sum * std::pow(1 + info_.interest, years);
}

// Calculate tax based on interest rate and income.
void DepositModel::CalculateTax() {
  if (info_.interest > 0.125) {
    info_.interest = 0.125;
    DepositModel clone(*this);
    clone.Calculate(info_);
    double tax_sum = result_.income - clone.result_.income;
    result_.tax = static_cast<int>(std::round(tax_sum * info_.tax));
  } else {
    result_.tax = 0;
  }
  AddTax();
}

// Adjust end sum, income, and end sum based on tax calculation.
void DepositModel::AddTax() {
  result_.end_sum -= result_.income;
  result_.income -= result_.tax;
  result_.end_sum += result_.income;
}

}  // namespace s21