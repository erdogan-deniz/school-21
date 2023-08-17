#include "s21_additional.h"

int s21_is_int(char* string) {
  int answer = true;

  if (string) {
    for (size_t i = 0; i < strlen(string); ++i)
      if (!isdigit(string[i])) answer = false;

    if (string[0] == '0' || string[0] == '-' || strlen(string) == 0)
      answer = false;
  }

  return answer;
}