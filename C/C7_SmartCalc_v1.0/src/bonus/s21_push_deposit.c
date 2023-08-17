#include "s21_bonus.h"

s21_payments* s21_push_deposit(long double sum, int month,
                               s21_payments* payments) {
  if (payments) {
    payments = s21_create_payment(payments);
    payments = s21_fill_deposit(sum, month, payments);
  } else {
    payments = s21_create_payments(payments);
    payments = s21_fill_deposit(sum, month, payments);
  }

  return payments;
}