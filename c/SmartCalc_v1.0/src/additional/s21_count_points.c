#include "s21_additional.h"

int s21_count_points(char* string) {
  int count = empty;

  if (string)
    for (size_t i = 0; i < strlen(string); ++i)
      if (string[i] == '.') ++count;

  return count;
}