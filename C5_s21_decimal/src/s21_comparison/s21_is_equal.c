#include "../s21_decimal.h"

int s21_is_equal(s21_decimal a, s21_decimal b) {
  int equal_sign = get_sign(a) == get_sign(b);

  int pow1 = s21_get_power(a);
  int pow2 = s21_get_power(b);
  int equal = a.bits[0] == b.bits[0] && a.bits[1] == b.bits[1] &&
              a.bits[2] == b.bits[2];

  return pow1 == pow2 && equal_sign && equal;
}
