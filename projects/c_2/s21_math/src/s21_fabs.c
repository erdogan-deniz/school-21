#include "s21_math.h"

long double s21_fabs(double x) {
  double y = 0;
  if (x == S21_INF) {
    y = S21_INF;
  } else if (x > 0) {
    y = x;
  } else {
    y = x * (-1);
  }
  return y;
}