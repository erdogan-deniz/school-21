#include "s21_string.h"

char *s21_strerror(int errnum) {
  static char *s_err;
  static char buffer[4096];

  s21_sprintf(buffer, "%s%d", UERROR, (int)errnum);
  if (s_err == s21_NULL || errnum > N || errnum < 0) {
    s_err = buffer;
  } else {
    static const char *array[] = error;
    s_err = (char *)array[errnum];
  }
  return s_err;
}