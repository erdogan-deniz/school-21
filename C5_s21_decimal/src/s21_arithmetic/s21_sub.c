#include "../s21_decimal.h"

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal* result) {
  int return_value = OK;
  memset(result, 0, sizeof(s21_decimal));

  int sign_1 = get_sign(value_1);
  int sign_2 = get_sign(value_2);

  sign_1 ? delete_sign(&value_1) : 0;
  sign_2 ? delete_sign(&value_2) : 0;
  int pow_1 = s21_get_power(value_1);
  int pow_2 = s21_get_power(value_2);

  s21_normalization(&value_1, &value_2);
  s21_decimal add_code_1;
  s21_decimal add_code_2;

  if (!sign_1 && !sign_2) {
    if (s21_comparison(value_1, value_2) == VAIUE2_GREATER) {
      add_code_1 = s21_add_code(value_1);
      s21_sum(value_2, add_code_1, result);
      set_sign(result);
    } else {
      add_code_2 = s21_add_code(value_2);
      s21_sum(value_1, add_code_2, result);
    }
  } else if (sign_1 && sign_2) {
    if (s21_comparison(value_1, value_2) == VAIUE1_GREATER) {
      add_code_2 = s21_add_code(value_2);
      s21_sum(add_code_2, value_1, result);
      set_sign(result);
    } else {
      add_code_1 = s21_add_code(value_1);
      s21_sum(add_code_1, value_2, result);
    }
  } else if (!sign_1 && sign_2) {
    s21_sum(value_1, value_2, result);

  } else if (sign_1 && !sign_2) {
    int is_over = s21_sum(value_1, value_2, result);
    if (is_over) {
      return NEGATIVE_INF;
    }
    set_sign(result);
  }
  int max_pow = pow_1 > pow_2 ? pow_1 : pow_2;
  s21_set_power(result, max_pow);

  return return_value;
}
