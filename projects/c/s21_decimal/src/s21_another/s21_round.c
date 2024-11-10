#include "../s21_decimal.h"

int s21_round(s21_decimal value, s21_decimal *result) {
  if (result == NULL) {
    return CONVERT_ERROR;
  }
  memset(result, 0, sizeof(s21_decimal));
  s21_decimal five = {{5}};
  s21_decimal one = {{1}};
  s21_decimal mod_result = {0};
  int sign = get_sign(value);
  delete_sign(&value);
  s21_set_power(&five, 1);
  s21_truncate(value, result);
  s21_mod(value, one, &mod_result);
  if (!s21_is_less(mod_result, five)) {
    s21_sum(*result, one, result);
  }
  if (sign) {
    set_sign(result);
  }
  return OK;
}
