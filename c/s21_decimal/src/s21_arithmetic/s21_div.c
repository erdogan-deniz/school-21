#include "../s21_decimal.h"

static s21_decimal s21_binary_div(s21_decimal value_1, s21_decimal value_2,
                                  s21_decimal *result) {
  static unsigned int pre_digit = 0;
  s21_decimal temp_result = {{1}};
  s21_decimal result_sub = {0};
  s21_decimal one = {{1}};
  s21_decimal temp_value_2 = value_2;
  if (s21_is_less(value_1, value_2)) {
    s21_decimal ten = {{10}};
    if (!is_zero(value_1)) {
      int is_over = 0;
      int power = s21_get_power(*result);
      if (power == 28) {
        is_over = 1;
      } else {
        is_over = s21_multiply(*result, ten, result);
      }
      power += 1;
      s21_multiply(value_1, ten, &value_1);
      if (is_over) {
        s21_int_div(value_1, value_2, &temp_result);
        s21_decimal pre_digit_dec = {{pre_digit}};
        *result = s21_base_bank_round(temp_result, pre_digit_dec, *result);
        return result_sub;
      }
      s21_set_power(result, power);
      pre_digit = 0;
      s21_binary_div(value_1, value_2, result);
    }
    return result_sub;
  } else if (s21_is_equal(value_1, value_2)) {
    s21_sum(*result, one, result);
    return one;
  }
  while (find_first_one_bit(value_1) > find_first_one_bit(temp_value_2)) {
    lshift(&temp_value_2);
    lshift(&temp_result);
  }
  if (s21_is_less(value_1, temp_value_2)) {
    rshift(&temp_value_2);
    rshift(&temp_result);
  }
  s21_sum(*result, temp_result, result);
  s21_sub(value_1, temp_value_2, &result_sub);
  pre_digit += temp_result.bits[0];
  s21_binary_div(result_sub, value_2, result);
  return *result;
}

s21_decimal s21_normalize_after_div(s21_decimal result_dif, int power_1,
                                    int power_2) {
  int difference;
  s21_decimal ten = {{10}};
  if (power_1 > power_2) {
    difference = power_1 - power_2;
    int result_power = s21_get_power(result_dif) + difference;
    if (result_power > 28) {
      result_power = 28;
    }
    s21_set_power(&result_dif, result_power);
  } else if (power_1 < power_2) {
    difference = power_2 - power_1;
    int result_power = s21_get_power(result_dif) - difference;
    result_power = result_power < 0 ? 0 : result_power;
    s21_set_power(&result_dif, 0);
    while (difference) {
      s21_multiply(result_dif, ten, &result_dif);
      difference--;
    }
    s21_set_power(&result_dif, result_power);
  }
  return result_dif;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int result_value = OK;
  memset(result, 0, sizeof(s21_decimal));

  int sign_1 = get_sign(value_1);
  int sign_2 = get_sign(value_2);
  int result_sign = 0;
  s21_decimal one = {{1}};

  delete_sign(&value_1);
  delete_sign(&value_2);
  int pow1 = s21_get_power(value_1);
  int pow2 = s21_get_power(value_2);

  if ((!sign_1 && sign_2) || (sign_1 && !sign_2)) {
    result_sign = 1;
  }

  if (is_zero(value_2)) {
    return s21_NAN;
  } else if (s21_is_equal(value_2, one)) {
    *result = value_1;
    result_sign ? set_sign(result) : 0;
    return result_value;
  }
  int is_over = s21_check_over(value_1, value_2);
  if (is_over) {
    if ((!sign_1 && !sign_2) || (sign_1 && sign_2)) {
      return POZITIVE_INF;
    } else if ((!sign_1 && sign_2) || (sign_1 && !sign_2)) {
      return NEGATIVE_INF;
    }
  }
  s21_set_power(&value_1, 0);
  s21_set_power(&value_2, 0);
  pow1 > pow2 ? s21_set_power(result, pow1) : 0;
  s21_binary_div(value_1, value_2, result);
  *result = s21_normalize_after_div(*result, pow1, pow2);

  if (result_sign) {
    set_sign(result);
  }
  return result_value;
}
