#include "s21_bonus.h"

s21_payments* s21_create_payments(s21_payments* payments) {
  if (!payments) {
    payments = (s21_payments*)malloc(sizeof(s21_payments));
    payments->next = NULL;
    payments->prev = NULL;
    payments->debt = empty;
    payments->percents = empty;
    payments->month_number = empty;
  }

  return payments;
}