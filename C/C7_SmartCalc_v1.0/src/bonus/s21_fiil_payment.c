#include "s21_bonus.h"

s21_payments* s21_fill_payment(long double sum, int months, int month_number,
                               long double interest_rate,
                               s21_payments* payment) {
  if (payment) {
    payment->debt = sum / months;
    payment->percents = (sum * interest_rate / 100) / 12;
    payment->month_number = month_number;
  }

  return payment;
}