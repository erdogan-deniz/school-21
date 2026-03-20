#include "../s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int result = CONVERT_OK;

  int scale = s21_get_power(src);
  if (scale) {
    s21_truncate(src, &src);
  }
  int pos = find_first_one_bit(src);
  if (pos > 30) {
    return CONVERT_ERROR;
  }
  if (dst == NULL) {
    return CONVERT_ERROR;
  } else {
    *dst = 0;
    for (int i = 0; i < 31; i++) {
      int temp = get_bit(src, i);
      int power = (1U << i) * temp;
      *dst += power;
    }
    int sign = get_sign(src);

    if (sign) {
      *dst *= -1;
    }
  }
  return result;
}
