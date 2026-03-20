#include "../s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  if (dst == NULL) {
    return CONVERT_ERROR;
  } else {
    memset(dst, 0, sizeof(s21_decimal));
    int sign = 0;
    if (src < 0) {
      sign = 1;
      src *= -1;
    }
    dst->bits[0] = src;
    sign ? set_sign(dst) : 0;
  }
  return CONVERT_OK;
}
