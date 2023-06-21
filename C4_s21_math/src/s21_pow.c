#include "s21_math.h"

long double s21_pow(double base, double exp) {
  long double result = 0;
  int flag = 0;
  if (exp == 0) {
    result = 1;
  } else {
    if (base < 0 && (int)exp < exp) {
      result = S21_NAN;
    } else {
      if (base < 0) {
        base = -base;
        flag = 1;
      }
      if (base != 0) {
        result = s21_exp(exp * s21_log(base));
      } else {
        result = 0;
      }
      if (flag && (int)exp % 2 != 0) {
        result = -result;
      }
    }
    if (base == 0 && exp < 0) {
      result = S21_INF;
    }
  }
  return result;
}