#include "s21_validation.h"

int s21_is_valid_string(char *string) {
  int answer = true;

  if (string)
    for (size_t i = 0; i < strlen(string); ++i)
      if (!s21_is_valid_symbol(string[i])) {
        answer = false;
        break;
      }

  return answer;
}