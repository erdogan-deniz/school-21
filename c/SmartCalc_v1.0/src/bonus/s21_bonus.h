#ifndef SRC_BONUS_S21_BONUS_H_
#define SRC_BONUS_S21_BONUS_H_

typedef struct s21_payments {
  long double debt;
  long double percents;
  int month_number;
  struct s21_payments* next;
  struct s21_payments* prev;
} s21_payments;

#define empty 0

#include "../stack/s21_stack.h"

s21_payments* s21_clear_payment(s21_payments* payment);
s21_payments* s21_create_payment(s21_payments* payments);
s21_payments* s21_create_payments(s21_payments* payments);
s21_payments* s21_fill_deposit(long double sum, int month_number,
                               s21_payments* payment);
s21_payments* s21_fill_payment(long double sum, int months, int month_number,
                               long double interest_rate,
                               s21_payments* payment);
s21_payments* s21_free_payments(s21_payments* payments);
long double s21_get_action_amount(int from, int to, s21_payments* payments);
long double s21_get_payment_amount(s21_payments* payment);
long double s21_get_total_amount(s21_payments* payments);
long double s21_get_total_debt(s21_payments* payments);
long double s21_interest_rate_to_month_ratio(long double interest_rate);
s21_payments* s21_pop_payment(s21_payments* payment);
s21_payments* s21_push_deposit(long double sum, int month,
                               s21_payments* payments);
s21_payments* s21_push_payment(long double sum, int months, int month,
                               long double interest_rate,
                               s21_payments* payments);

#endif  // SRC_BONUS_S21_BONUS_H_