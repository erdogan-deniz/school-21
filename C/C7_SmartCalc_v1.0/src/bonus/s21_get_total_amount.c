#include "s21_bonus.h"

long double s21_get_total_amount(s21_payments* payments) {
  long double total_amount = empty;

  if (payments) {
    while (payments->next) payments = payments->next;

    while (payments) {
      total_amount += s21_get_payment_amount(payments);
      payments = payments->prev;
    }
  }

  return total_amount;
}