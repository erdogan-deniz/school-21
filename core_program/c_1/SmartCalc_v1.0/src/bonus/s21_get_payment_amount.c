#include "s21_bonus.h"

long double s21_get_payment_amount(s21_payments* payment) {
  long double payment_amount = empty;

  if (payment) {
    payment_amount += payment->debt + payment->percents;
  }

  return payment_amount;
}