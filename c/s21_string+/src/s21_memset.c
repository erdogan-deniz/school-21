#include "s21_string.h"

void *s21_memset(void *str, int c, s21_size_t n) {
  s21_size_t i = 0;
  while (i++ < n) *(((unsigned char *)str) + (i - 1)) = (unsigned char)c;
  return str;
}