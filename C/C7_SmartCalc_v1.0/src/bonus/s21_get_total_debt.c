#include "s21_bonus.h"

long double s21_get_total_debt(s21_payments* payments) {
  long double total_debt = empty;

  if (payments) {
    while (payments->next) payments = payments->next;

    while (payments) {
      total_debt += payments->debt;
      payments = payments->prev;
    }
  }

  return total_debt;
}