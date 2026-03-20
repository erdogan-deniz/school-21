#include "s21_math.h"

long double s21_factorial(int n) {
  double res = 0;
  if (n == 0 || n == 1)
    res = 1;
  else
    res = n * s21_factorial(n - 1);
  return res;
}