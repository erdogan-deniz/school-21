#include "s21_additional.h"

int s21_have_point(char* string) {
  int answer = false;

  if (string)
    for (size_t i = 0; i < strlen(string); ++i)
      if (string[i] == '.') answer = true;

  return answer;
}