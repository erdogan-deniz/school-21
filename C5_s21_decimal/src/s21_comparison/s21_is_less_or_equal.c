#include "../s21_decimal.h"

int s21_is_less_or_equal(s21_decimal value1, s21_decimal value2) {
  return s21_is_less(value1, value2) || s21_is_equal(value1, value2);
}
