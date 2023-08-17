#include "s21_additional.h"

int s21_have_x(char* string) {
  int answer = false;

  if (string)
    for (size_t i = 0; i < strlen(string); ++i)
      if (string[i] == 'x') answer = true;

  return answer;
}