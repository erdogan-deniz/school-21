#include "s21_bonus.h"

s21_payments* s21_clear_payment(s21_payments* payment) {
  if (payment) {
    payment->debt = empty;
    payment->percents = empty;
    payment->month_number = empty;
    payment->prev = NULL;
    payment->next = NULL;
  }

  return payment;
}
