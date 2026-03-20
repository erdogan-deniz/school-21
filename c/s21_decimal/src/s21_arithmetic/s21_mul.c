#include "../s21_decimal.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal* result) {
  int result_value = OK;
  memset(result, 0, sizeof(s21_decimal));

  int sign_1 = get_sign(value_1);
  int sign_2 = get_sign(value_2);

  int need_sign = (!sign_1 && sign_2) || (sign_1 && !sign_2);
  delete_sign(&value_1);
  delete_sign(&value_2);
  int pow1 = s21_get_power(value_1);
  int pow2 = s21_get_power(value_2);
  s21_set_power(&value_1, 0);
  s21_set_power(&value_2, 0);
  s21_decimal temp_result = {0};

  int is_over = s21_multiply(value_1, value_2, &temp_result);
  int count = 0;

  if (is_over && (pow1 + pow2) > 0) {
    s21_decimal ten = {{10}};
    while (is_over && count < (pow1 + pow2)) {
      s21_decimal div_res = {{1}};
      s21_decimal delim = count % 2 ? value_2 : value_1;
      s21_int_div(delim, ten, &div_res);
      if (count % 2) {
        value_2 = div_res;
      } else {
        value_1 = div_res;
      }
      is_over = s21_multiply(value_1, value_2, &temp_result);
      count++;
    }
  }
  if (is_over && need_sign) {
    return NEGATIVE_INF;
  } else if (is_over && !need_sign) {
    return POZITIVE_INF;
  }
  *result = temp_result;
  s21_set_power(result, pow1 + pow2 - count);
  if (need_sign) {
    set_sign(result);
  }
  return result_value;
}
