#include "s21_additional.h"

long double s21_string_to_long_double(char* string) {
  return string ? strtold(string, NULL) : 0.0L;
}