#include "s21_string.h"

char *s21_strcat(char *dest, const char *src) {
  s21_memcpy(dest + s21_strlen(dest), src, s21_strlen(src) + 1);
  return dest;
}