#include "../s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal* result) {
  s21_decimal ten = {{10}};
  int power = s21_get_power(value);
  int sign = get_sign(value);
  delete_sign(&value);
  s21_set_power(&value, 0);
  if (power) {
    while (power) {
      memset(result, 0, sizeof(s21_decimal));
      result->bits[0] = 1;
      s21_int_div(value, ten, result);
      value = *result;
      power--;
    }
  } else {
    *result = value;
  }
  if (sign) {
    set_sign(result);
  }
  return OK;
}
