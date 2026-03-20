#include "s21_math.h"

long double s21_asin(double x) {
  long double result = 0.0;

  if (x == 1.0) {
    result = S21_PI / 2.0;
  } else if (x == -1) {
    result = S21_PI / -2.0;
  } else if (x > -1.0 && x < 1.0) {
    result = s21_atan(x / s21_sqrt(1.0 - x * x));
  } else {
    result = S21_NAN;
  }

  return result;
}