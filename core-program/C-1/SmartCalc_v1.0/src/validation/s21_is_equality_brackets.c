#include "s21_validation.h"

int s21_is_equality_brackets(char *string) {
  int brackets_counter = empty;
  int answer = true;

  if (string)
    for (size_t i = 0; i < strlen(string); ++i) {
      if (string[i] == '(')
        ++brackets_counter;
      else if (string[i] == ')')
        --brackets_counter;

      if (brackets_counter < 0) {
        answer = false;
        break;
      }
    }

  return answer && !brackets_counter ? true : false;
}