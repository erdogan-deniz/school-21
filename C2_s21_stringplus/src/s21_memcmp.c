#include "s21_string.h"

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  s21_size_t i = 0;
  const unsigned char *cstr1 = (const unsigned char *)str1;
  const unsigned char *cstr2 = (const unsigned char *)str2;
  int result = 0;
  while (i < n) {
    if (*(cstr1 + i) != *(cstr2 + i)) {
      result = *(cstr1 + i) - *(cstr2 + i);
      break;
    }
    i++;
  }
  return result;
}