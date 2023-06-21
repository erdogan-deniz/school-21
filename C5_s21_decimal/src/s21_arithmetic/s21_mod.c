#include "../s21_decimal.h"

static s21_decimal s21_binary_mod(s21_decimal value_1, s21_decimal value_2) {
  s21_decimal result_sub = {0};
  s21_decimal result = {0};
  s21_decimal temp_value_2 = value_2;
  if (s21_is_less(value_1, value_2)) {
    return value_1;
  } else if (s21_is_equal(value_1, value_2)) {
    return result_sub;
  }
  while (find_first_one_bit(value_1) > find_first_one_bit(temp_value_2)) {
    lshift(&temp_value_2);
  }
  if (s21_is_less(value_1, temp_value_2)) {
    rshift(&temp_value_2);
  }
  s21_sub(value_1, temp_value_2, &result_sub);
  result = s21_binary_mod(result_sub, value_2);
  return result;
}

int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  memset(result, 0, sizeof(s21_decimal));
  if (is_zero(value_2)) {
    return s21_NAN;
  }
  int sign = get_sign(value_1);
  delete_sign(&value_1);
  delete_sign(&value_2);
  int pow_1 = s21_get_power(value_1);
  int pow_2 = s21_get_power(value_2);
  int is_over = s21_normalization(&value_1, &value_2);
  if (is_over && is_zero(value_2)) {
    return OK;
  }
  s21_set_power(&value_1, 0);
  s21_set_power(&value_2, 0);
  *result = s21_binary_mod(value_1, value_2);
  if (sign) {
    set_sign(result);
  }
  int max = pow_1 > pow_2 ? pow_1 : pow_2;
  s21_set_power(result, max);
  if (is_over) {
    s21_truncate(*result, result);
  }
  return OK;
}
