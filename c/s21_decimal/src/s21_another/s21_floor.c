#include "../s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  if (result != NULL) {
    memset(result, 0, sizeof(s21_decimal));
    s21_decimal one = {{1}};
    s21_decimal mod_res = {0};
    int sign = get_sign(value);
    delete_sign(&value);
    s21_mod(value, one, &mod_res);
    s21_truncate(value, &value);
    if (sign && !is_zero(mod_res) && !is_zero(value)) {
      s21_sum(value, one, result);
      set_sign(result);
    } else {
      *result = value;
      if (sign) {
        set_sign(result);
      }
    }
  } else {
    return CONVERT_ERROR;
  }
  return CONVERT_OK;
}
