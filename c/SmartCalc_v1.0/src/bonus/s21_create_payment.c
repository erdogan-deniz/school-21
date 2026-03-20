#include "s21_bonus.h"

s21_payments* s21_create_payment(s21_payments* payments) {
  if (payments) {
    while (payments->prev) payments = payments->prev;

    s21_payments* prev = payments;

    payments = (s21_payments*)calloc(1, sizeof(s21_payments));
    payments->debt = empty;
    payments->percents = empty;
    payments->month_number = empty;
    payments->next = prev;
    prev->prev = payments;
    payments->prev = NULL;
  }

  return payments;
}