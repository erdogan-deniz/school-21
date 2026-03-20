#include "s21_string.h"

char *s21_strncpy(dst, src, n)
char *dst;
const char *src;
register s21_size_t n;
{
  if (n != 0) {
    register char *d = dst;
    register const char *s = src;

    do {
      if ((*d++ = *s++) == 0) {
        while (--n != 0) *d++ = 0;
        break;
      }
    } while (--n != 0);
  }
  return (dst);
}