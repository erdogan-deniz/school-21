#include "../s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  if (dst == NULL) {
    return CONVERT_ERROR;
  }
  int sign = get_sign(src);
  int power = s21_get_power(src);
  long double result = 0;
  for (int i = 0; i < 96; i++) {  //  переводим в десятичную систему, умножая
                                  //  биты на степень двойки
    result += pow(2, i) * get_bit(src, i);
  }

  while (power) {
    result /= 10.0;  //  отделяем дробную часть
    power--;
  }
  if (sign) {
    result *= -1.0;
  }

  *dst = result;
  return OK;
}
