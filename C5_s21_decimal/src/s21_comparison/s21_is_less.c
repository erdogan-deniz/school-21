#include "../s21_decimal.h"

int s21_is_less(s21_decimal value1, s21_decimal value2) {
  int result = FALSE;

  int sign1 = get_sign(value1);
  int sign2 = get_sign(value2);

  if (is_zero(value1) && is_zero(value2)) {
    result = FALSE;
  } else if (sign1 && !sign2) {
    result = TRUE;
  } else if (!sign1 && sign2) {
    result = FALSE;
  } else if (sign1 && sign2) {
    delete_sign(&value1);
    delete_sign(&value2);
    result = s21_is_greater(value1, value2);
  } else {
    s21_normalization(&value1, &value2);
    result = comparison_value_bits(value1, value2);
  }
  return result;
}
