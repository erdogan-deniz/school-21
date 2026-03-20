#include "s21_bonus.h"

s21_payments* s21_pop_payment(s21_payments* payment) {
  if (payment) {
    s21_payments* next = NULL;

    while (payment->prev) payment = payment->prev;

    next = payment->next;

    payment = s21_clear_payment(payment);
    free(payment);

    if (next) next->prev = NULL;

    payment = next;
  }

  return payment;
}