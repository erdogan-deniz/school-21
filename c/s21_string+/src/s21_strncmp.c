#include "s21_string.h"

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int lenght = 0;
  if (n == 0) lenght = 0;
  if (n != 0) {
    s21_size_t i = 0;
    while (*(str1 + i) && *(str2 + i) && i < n - 1 &&
           *(str1 + i) == *(str2 + i))
      i++;
    if (*(str1 + i) != *(str2 + i)) lenght = *(str1 + i) - *(str2 + i);
  }
  return lenght;
}