#include "s21_string.h"

int in(char ch, const char *str) {
  int flag = 0;
  for (int i = 0; str[i] != '\0'; i++)
    if (str[i] == ch) flag = 1;
  return flag;
}

void skipSeps(char **str, const char *sep) {
  while (in(**str, sep) && **str != '\0') (*str)++;
}

void skipNonSeps(char **str, const char *sep) {
  while (in(**str, sep) == 0 && **str != '\0') (*str)++;
}

char *s21_strtok(char *str, const char *delim) {
  static char *prev_ptr;
  const char *result;
  if (str) prev_ptr = str;
  if (prev_ptr == s21_NULL || *prev_ptr == '\0') {
    result = s21_NULL;
  } else {
    skipSeps(&prev_ptr, delim);
    char *begin = prev_ptr;
    skipNonSeps(&prev_ptr, delim);
    if (*prev_ptr == '\0' && !(prev_ptr - begin)) {
      prev_ptr = s21_NULL;
      result = s21_NULL;
    } else {
      if (*prev_ptr != '\0') {
        *prev_ptr = '\0';
        prev_ptr++;
      }
      result = begin;
    }
  }
  return (char *)result;
}