#include "s21_string.h"

void *s21_to_upper(const char *str) {
  char *result = s21_NULL;
  if (str != s21_NULL) {
    int y = 0;
    result = (char *)malloc((s21_strlen(str) + 1) * sizeof(char));
    if (!result) exit(0);
    for (int i = 0; str[i] != '\0'; i++) {
      if (str[i] >= 97 && str[i] <= 122) {
        result[i] = str[i] - 32;
      } else {
        result[i] = str[i];
      }
      ++y;
    }
    result[y] = '\0';
  }
  return result;
}