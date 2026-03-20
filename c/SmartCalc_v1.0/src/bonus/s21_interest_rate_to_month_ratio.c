#include "s21_bonus.h"

long double s21_interest_rate_to_month_ratio(long double interest_rate) {
  long double month_ratio = empty;

  if (interest_rate) month_ratio = interest_rate / 12 / 100;

  return month_ratio;
}