#include "s21_math.h"

long double s21_tan(double x) {
  long double result = s21_sin(x) / s21_cos(x);
  return result;
}