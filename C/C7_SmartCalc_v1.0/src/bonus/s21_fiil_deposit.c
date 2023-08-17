#include "s21_bonus.h"

s21_payments* s21_fill_deposit(long double sum, int month_number,
                               s21_payments* payment) {
  if (payment) {
    payment->debt = sum;
    payment->percents = empty;
    payment->month_number = month_number;
  }

  return payment;
}