#include "s21_math.h"

long double s21_floor(double x) {
  long double y = 0;
  if (s21_fmod(x, 1.0) != 0) {
    y = x;
    if (x == S21_INF) {
      y = S21_INF;
    } else if (x == S21__INF) {
      y = S21__INF;
    } else if (x > 0.0) {
      y = (long long int)x;
    } else if (x < 0.0) {
      y = (long long int)x - 1;
    }
  } else {
    y = x;
  }
  return y;
}