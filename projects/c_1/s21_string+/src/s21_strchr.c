#include "s21_string.h"

char *s21_strchr(const char *str, int c) {
  int i = 0;
  int flag = 0;
  char *result = s21_NULL;
  while (*(str + i)) {
    if (*(str + i) == (char)c) {
      flag = 1;
      result = (char *)(str + i);
      break;
    }
    i++;
  }
  if (!flag && *(str + i) == c) result = (char *)(str + i);
  return result;
}