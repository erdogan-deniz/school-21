#include <stdio.h>

#include "s21_util.h"

/*                                          79228162514264337593543950335
   [11111111 11111111 11111111 11111111] [11111111 11111111 11111111 11111111]
   [11111111 11111111 11111111 11111111]
*/
int get_bit(s21_decimal number, int position) {
  return (number.bits[position / 32] >> (position % 32)) & 1U;
}

void set_bit(s21_decimal* number, int position) {
  int mask = 1U << (position % 32);
  number->bits[position / 32] |= mask;
}

int get_sign(s21_decimal number) { return (number.bits[3] >> SIGN) & 1U; }

void set_sign(s21_decimal* number) {
  int mask = 1U << SIGN;
  number->bits[3] |= mask;
}

void delete_sign(s21_decimal* number) {
  int mask = ~(1U << SIGN);
  number->bits[3] &= mask;
}

int lshift(s21_decimal* value) {
  int is_over = get_bit(*value, 95);
  value->bits[2] <<= 1U;
  if (get_bit(*value, 63)) {
    set_bit(value, 64);
  }
  value->bits[1] <<= 1U;
  if (get_bit(*value, 31)) {
    set_bit(value, 32);
  }
  value->bits[0] <<= 1U;
  return is_over;
}

void rshift(s21_decimal* value) {
  value->bits[0] >>= 1U;
  if (get_bit(*value, 32)) {
    set_bit(value, 31);
  }
  value->bits[1] >>= 1U;
  if (get_bit(*value, 64)) {
    set_bit(value, 63);
  }
  value->bits[2] >>= 1U;
}

s21_decimal s21_inversion(s21_decimal number) {
  s21_decimal result;
  result.bits[0] = ~number.bits[0];
  result.bits[1] = ~number.bits[1];
  result.bits[2] = ~number.bits[2];
  return result;
}

void s21_plus_one(s21_decimal value, s21_decimal* result) {
  s21_decimal one = {0};
  one.bits[0] = 1;
  s21_sum(value, one, result);
}

s21_decimal s21_add_code(s21_decimal value) {
  s21_decimal result = {0};
  s21_decimal add_code = s21_inversion(value);
  s21_plus_one(add_code, &result);
  return result;
}

int s21_sum(s21_decimal value_1, s21_decimal value_2, s21_decimal* result) {
  int result_value = OK;
  int temp = 0;
  s21_decimal temp_res = {0};
  for (int i = 0; i < 96; i++) {
    int value1_bit = get_bit(value_1, i);
    int value2_bit = get_bit(value_2, i);
    int compare = value1_bit || value2_bit;
    if (value1_bit && value2_bit) {
      if (temp) {
        set_bit(&temp_res, i);
      }
      temp = 1;
    }
    if (!temp && compare) {
      set_bit(&temp_res, i);
    } else if (temp && !compare) {
      set_bit(&temp_res, i);
      temp = 0;
    }
    if (i == 95 && temp == 1) {
      result_value = 1;
    }
  }
  s21_set_power(&temp_res, s21_get_power(*result));
  *result = temp_res;
  return result_value;
}

int s21_comparison(s21_decimal value_1, s21_decimal value_2) {
  int result = EQUAL;
  for (int i = 95; i >= 0; i--) {
    if (get_bit(value_1, i) > get_bit(value_2, i)) {
      result = VAIUE1_GREATER;
      break;
    } else if (get_bit(value_1, i) < get_bit(value_2, i)) {
      result = VAIUE2_GREATER;
      break;
    }
  }
  return result;
}

int s21_get_power(s21_decimal value) {
  int power = 0;
  int result = 0;
  for (int i = 0; i < END_POWER - BEGIN_POWER; i++) {
    int temp = get_bit(value, 96 + i + BEGIN_POWER);
    power = (1U << i) * temp;
    result += power;
  }
  return result;
}

static void s21_delete_power(s21_decimal* value) {
  int sign = get_sign(*value);
  value->bits[3] = 0;
  if (sign) {
    set_sign(value);
  }
}

void s21_set_power(s21_decimal* value, int pow) {
  s21_delete_power(value);
  for (int i = BEGIN_POWER; i <= END_POWER && pow; i++) {
    if (pow % 2 == 1) {
      set_bit(value, 96 + i);
    }
    pow /= 2;
  }
}

int is_zero(s21_decimal number) {
  int result =
      number.bits[0] == 0 && number.bits[1] == 0 && number.bits[2] == 0;
  return result;
}

int count_shift(s21_decimal* value, int count) {
  int is_over = 0;
  for (int i = 0; i < count; i++) {
    is_over = lshift(value);
    if (is_over) {
      break;
    }
  }
  return is_over;
}

int s21_multiply(s21_decimal value_1, s21_decimal value_2,
                 s21_decimal* result) {
  int is_over = OK;
  int sum_over = OK;
  s21_decimal temp = {0};
  s21_decimal result_tmp = {0};
  int count = 0;
  while (!is_zero(value_2)) {
    memset(&temp, 0, sizeof(s21_decimal));
    int bit_2 = get_bit(value_2, 0);
    for (int i = 0; i < 96; i++) {
      int bit_1 = get_bit(value_1, i);
      if (bit_1 && bit_2) {
        set_bit(&temp, i);
      }
    }
    is_over = count_shift(&temp, count);
    sum_over = s21_sum(result_tmp, temp, &result_tmp);
    rshift(&value_2);
    if (is_over || sum_over) {
      break;
    }
    count++;
  }
  if (!is_over && !sum_over) {
    *result = result_tmp;
  }
  return is_over || sum_over;
}

int find_first_one_bit(s21_decimal src) {
  int position = -1;
  for (int i = 95; i >= 0; i--) {
    if (get_bit(src, i)) {
      position = i;
      break;
    }
  }
  return position;
}
