#include "../s21_decimal.h"

s21_decimal s21_int_div(s21_decimal value_1, s21_decimal value_2,
                        s21_decimal* result) {
  s21_decimal result_sub = {0};
  s21_decimal one = {{1}};
  s21_decimal temp_value_2 = value_2;
  if (s21_is_less(value_1, value_2)) {
    *result = result_sub;
    return result_sub;
  } else if (s21_is_equal(value_1, value_2)) {
    return one;
  }
  while (find_first_one_bit(value_1) > find_first_one_bit(temp_value_2)) {
    lshift(&temp_value_2);
    lshift(result);
  }
  if (s21_is_less(value_1, temp_value_2)) {
    rshift(&temp_value_2);
    rshift(result);
  }
  s21_sub(value_1, temp_value_2, &result_sub);
  one = s21_int_div(result_sub, value_2, &one);
  s21_sum(*result, one, result);
  return *result;
}

s21_decimal s21_get_pre_digit(s21_decimal value) {
  s21_decimal ten = {{10}};
  s21_decimal div_result = {{1}};
  s21_decimal pre_digit = {0};
  s21_int_div(value, ten, &div_result);
  s21_mod(div_result, ten, &pre_digit);
  return pre_digit;
}

s21_decimal s21_base_bank_round(s21_decimal last_decimal, s21_decimal pre_digit,
                                s21_decimal result) {
  s21_decimal two = {{2}};
  s21_decimal five = {{5}};
  s21_decimal is_even = {0};
  if (s21_is_equal(last_decimal, five)) {
    s21_mod(pre_digit, two, &is_even);
    if (!is_zero(is_even)) {
      s21_plus_one(result, &result);
    }
  } else if (s21_is_less(five, last_decimal)) {
    s21_plus_one(result, &result);
  }
  return result;
}

s21_decimal s21_bank_rounding(s21_decimal value) {
  s21_decimal ten = {{10}};
  s21_decimal last_decimal = {0};
  s21_decimal result = {{1}};

  s21_mod(value, ten, &last_decimal);
  s21_decimal pre_digit = s21_get_pre_digit(value);
  s21_int_div(value, ten, &result);

  return s21_base_bank_round(last_decimal, pre_digit, result);
}

int s21_normalization(s21_decimal* value_1, s21_decimal* value_2) {
  int check_over = OK;
  int power_1 = s21_get_power(*value_1);
  int power_2 = s21_get_power(*value_2);
  s21_set_power(value_1, 0);
  s21_set_power(value_2, 0);

  int biggest_power = power_1 > power_2 ? power_1 : power_2;
  int min_power = power_1 < power_2 ? power_1 : power_2;
  s21_decimal num_normalize = power_1 < power_2 ? *value_1 : *value_2;
  s21_decimal small = power_1 < power_2 ? *value_2 : *value_1;
  s21_decimal result = {0};
  s21_decimal ten = {{10}};

  while (min_power != biggest_power) {
    check_over = s21_multiply(num_normalize, ten, &result);
    if (check_over) {
      break;
    }
    min_power++;
    num_normalize = result;
    memset(&result, 0, sizeof(s21_decimal));
  }
  if (check_over) {
    while (min_power < biggest_power) {
      small = s21_bank_rounding(small);
      min_power++;
    }
  }
  if (power_1 < power_2) {
    *value_1 = num_normalize;
    *value_2 = small;
  } else {
    *value_2 = num_normalize;
    *value_1 = small;
  }
  s21_set_power(value_1, biggest_power);
  s21_set_power(value_2, biggest_power);
  return check_over;
}
