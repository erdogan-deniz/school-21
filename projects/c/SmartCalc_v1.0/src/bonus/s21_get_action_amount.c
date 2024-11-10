#include "s21_bonus.h"

long double s21_get_action_amount(int from, int to, s21_payments* payments) {
  long double result = empty;

  if (payments && to) {
    while (payments->next) payments = payments->next;

    while (payments) {
      if (payments->month_number > from && payments->month_number <= to)
        result += payments->debt;

      payments = payments->prev;
    }
  }

  return result;
}
