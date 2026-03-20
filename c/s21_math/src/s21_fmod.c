#include "s21_math.h"

long double s21_fmod(double x, double y) {
  long double res = 0;
  if (x == S21_INF || x == S21__INF || x == S21_NAN || y == S21_NAN) {
    res = S21_NAN;
  } else if (x != 0.0 && y == S21_INF) {
    res = (long double)x;
  } else if (x != 0.0 && y == S21__INF) {
    res = (long double)x;
  } else if (y == 0) {
    res = S21_NAN;
  } else {
    long long int mod = 0;
    mod = x / y;
    res = (long double)x - mod * (long double)y;
  }
  return res;
}