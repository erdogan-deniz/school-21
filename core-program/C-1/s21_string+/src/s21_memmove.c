#include "s21_string.h"

void *s21_memmove(void *dest, const void *src, s21_size_t n) {
  char *l1 = (char *)dest;
  char *l2 = (char *)src;
  if (dest != s21_NULL && src != s21_NULL) {
    s21_size_t i;
    if (l1 > l2) {
      i = n;
      while (i--) *(l1 + i) = *(l2 + i);
    } else {
      i = 0;
      while (i++ < n) *(l1 + (i - 1)) = *(l2 + (i - 1));
    }
  }
  return l1;
}