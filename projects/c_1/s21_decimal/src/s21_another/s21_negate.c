#include "../s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal* result) {
  result->bits[0] = value.bits[0];
  result->bits[1] = value.bits[1];
  result->bits[2] = value.bits[2];
  result->bits[3] = value.bits[3];
  if (!get_sign(value)) {
    set_sign(result);
  } else {
    delete_sign(result);
  }
  return OK;
}
