#include "s21_math.h"

long double s21_sin(double x) {
  long long int fa = 1;
  double po = 1.0;
  double result = 0.0;
  double result2 = 10.0;
  int znak = 1;

  if (x == S21_INF || x == S21__INF || x == S21_NAN || x == S21_NAN2) {
    result = S21_NAN;
  } else {
    if (s21_fabs(x) > 2.0 * S21_PI) {
      if (x > 0.0) x = s21_fmod(s21_fabs(x), 2.0 * S21_PI);
      if (x < 0.0) x = -s21_fmod(s21_fabs(x), 2.0 * S21_PI);
    }
    while (s21_fabs(result - result2) > S21_EPS) {
      result2 = result;
      result += znak * (s21_pow(x, po) / s21_factorial(fa));
      po += 2;
      fa += 2;
      znak = -znak;
    }
  }
  return result;
}