#include "../s21_decimal.h"

#define MAX 79228162514264337593543950335.0F
#define MIN -79228162514264337593543950335.0F

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int wrong_arg = src == S21_POSITIVE_INF || src == S21_NEGATIVE_INF ||
                  src != src || dst == NULL;
  if (wrong_arg || (src < MIN || src > MAX)) {
    return CONVERT_ERROR;
  }
  memset(dst, 0, sizeof(s21_decimal));
  int is_negative = 0;
  if (src < 0) {
    is_negative = 1;
  }
  long double src_work = fabsf(src);
  long double exp_src = src_work;
  int exp = 0;
  while (exp_src >= 1) {  //  получаем количество знаков до точки
    exp_src /= 10.0;
    exp++;
  }
  if (exp == 0) {
    exp = 1;
  }
  src_work *= powl(
      (long double)10.0,
      (long double)(28.0 - exp));  //  получаем src домноженный до 28 знаков
  char bit[128] = {'\0'};
  for (int i = 0; src_work > 1e-6; i++) {
    src_work = floorl(src_work) / 2;
    if (src_work - floorl(src_work) > 1e-6) {
      bit[i] = '1';
    } else {
      bit[i] = '0';
    }
  }

  for (size_t i = strlen(bit) - 1; i < strlen(bit); i--) {
    if (bit[i] - 48) {
      set_bit(dst, i);
    }
  }
  s21_set_power(dst, 28 - exp);
  if (is_negative) {
    set_sign(dst);
  }
  return OK;
}
