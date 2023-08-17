#include "s21_bonus.h"

s21_payments* s21_free_payments(s21_payments* payments) {
  if (payments) {
    while (payments) payments = s21_pop_payment(payments);
  }

  return payments;
}
