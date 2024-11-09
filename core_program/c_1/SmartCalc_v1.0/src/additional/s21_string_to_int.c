#include "s21_additional.h"

int s21_string_to_int(char* string) {
  long double integer = empty;

  if (string) {
    int degree = strlen(string) - 1;

    for (size_t i = 0; i < strlen(string); ++i) {
      integer += s21_char_to_int(string[i]) * pow(10, degree);
      --degree;
    }
  }

  return integer;
}
