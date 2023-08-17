#include "s21_bonus.h"

s21_payments* s21_push_payment(long double sum, int months, int month,
                               long double interest_rate,
                               s21_payments* payments) {
  if (payments) {
    payments = s21_create_payment(payments);
    payments = s21_fill_payment(sum, months, month, interest_rate, payments);
  } else {
    payments = s21_create_payments(payments);
    payments = s21_fill_payment(sum, months, month, interest_rate, payments);
  }

  return payments;
}