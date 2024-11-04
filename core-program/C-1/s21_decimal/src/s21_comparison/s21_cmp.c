#include "../s21_decimal.h"

int comparison_value_bits(s21_decimal value1, s21_decimal value2) {
  int result = FALSE;

  for (int i = 95; i >= 0; i--) {
    int bit1 = get_bit(value1, i);
    int bit2 = get_bit(value2, i);
    if (!bit1 && bit2) {
      result = TRUE;
      break;
    }
    if (bit1 && !bit2) {
      result = FALSE;
      break;
    }
  }
  return result;
}
