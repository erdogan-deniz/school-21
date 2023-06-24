#include "s21_math.h"

long double s21_exp(double x) {
  long double add_vavial = 1.0;
  long double i = 1.0;
  long double serias = 1.0;
  int flag = 0;
  if (x == S21_INF) {
    serias = S21_INF;
  } else if (x == S21__INF) {
    serias = 0;
  } else {
    if (x < 0) {
      x *= -1;
      flag = 1;
    }
    while (S21_EPS < s21_fabs(add_vavial)) {
      add_vavial *= x / i;
      serias += add_vavial;
      i++;
      if (serias > DBL_MAX) {
        serias = S21_INF;
        break;
      }
    }
    if (flag) {
      serias = 1 / serias;
    }
  }
  return serias;
}