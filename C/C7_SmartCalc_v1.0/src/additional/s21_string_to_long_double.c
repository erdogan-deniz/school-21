#include "s21_additional.h"

long double s21_string_to_long_double(char* string) {
  long double number = empty;

  if (string) {
    int integer = 0;
    int degree = strlen(string) - 1;

    for (size_t i = 0; i < strlen(string); ++i) {
      if (string[i] == '.') continue;

      number += s21_char_to_int(string[i]) * pow(10, degree);
      --degree;
    }

    if (s21_have_point(string)) {
      degree = 0;

      while (string[degree] != '.') {
        ++integer;
        ++degree;
      }

      number /= pow(10, strlen(string) - integer);
    }
  }

  return number;
}