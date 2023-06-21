#include "s21_string.h"

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  s21_memcpy(dest + s21_strlen(dest), src, n);
  return dest;
}
