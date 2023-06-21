#ifndef S21_MATH
#define S21_MATH

#include <float.h>
#include <stdio.h>

#define S21_EPS 1e-9
#define S21_NAN 0.0 / 0.0
#define S21_NAN2 -0.0 / 0.0
#define S21_INF 1.0 / 0.0
#define S21__INF -1.0 / 0.0
#define S21_PI 3.14159265358979323846

int s21_abs(int);
long double s21_pow(double, double);
long double s21_log(double);
long double s21_fabs(double);
long double s21_fmod(double, double);
long double s21_exp(double);
long double s21_sqrt(double);
long double s21_ceil(double);
long double s21_floor(double);
long double s21_acos(double);
long double s21_asin(double);
long double s21_atan(double);
long double s21_cos(double);
long double s21_sin(double);
long double s21_tan(double);
long double s21_factorial(int);
#endif