#include "s21_math.h"

long double s21_log(double x) {
  long double result = 0;
  double y = 0;
  if (x == 0.0) {
    result = S21__INF;
  } else if (x == S21__INF) {
    result = S21_NAN;
  } else if (x == S21_INF) {
    result = S21_INF;
  } else if (x > 0) {
    for (int i = 0; i < 1000; i++) {
      y = result;
      result = y + 2 * (x - s21_exp(y)) / (x + s21_exp(y));
    }
  } else {
    result = S21_NAN;
  }
  return result;
}