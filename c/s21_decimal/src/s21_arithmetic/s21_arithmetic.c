#include <stdio.h>

#include "../s21_decimal.h"
/*
00101 5
00011 3
01000 8
*/

int s21_check_over(s21_decimal value_1, s21_decimal value_2) {
  int check_over = OK;
  int power_1 = s21_get_power(value_1);
  int power_2 = s21_get_power(value_2);
  s21_set_power(&value_1, 0);
  s21_set_power(&value_2, 0);

  int biggest_power = power_1 > power_2 ? power_1 : power_2;
  int min_power = power_1 < power_2 ? power_1 : power_2;
  s21_decimal num_normalize = power_1 < power_2 ? value_1 : value_2;
  s21_decimal small = power_1 < power_2 ? value_2 : value_1;
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
    if (is_zero(small)) {
      return check_over;
    }
  }
  return OK;
}
