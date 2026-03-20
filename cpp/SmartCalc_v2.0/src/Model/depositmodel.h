#ifndef SRC_MODEL_DEPOSIT_H
#define SRC_MODEL_DEPOSIT_H

#include <cmath>
#include <iostream>

namespace s21 {

// Enum representing different frequency options for deposit calculation.
enum Frequency { kDaily, kMonthly, kQuarterly, kHalfYearly, kYearly, kEnd };

// Structure to hold the information about deposit
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

// Structure to hold the calculated result including income, tax, and end sum.
struct DepositResult {
  int income{};
  int tax{};
  int end_sum{};

  DepositResult() {}
  ~DepositResult() {}
};

class DepositModel {
 public:
  // Constructor
  DepositModel(){};
  // Copy Contructor
  DepositModel(const DepositModel& other)
      : info_(other.info_), result_(other.result_) {}
  // Destructor
  ~DepositModel(){};
  // Initiates the deposit calculation based on the selected frequency.
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
