#include "s21_string.h"

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  char *res = s21_NULL;
  s21_size_t src_length, str_length;
  src_length = (src == s21_NULL) ? 0 : s21_strlen(src);
  str_length = (str == s21_NULL) ? 0 : s21_strlen(str);
  s21_size_t fin_length = src_length + str_length;
  if (start_index <= src_length) {
    res = (char *)calloc(src_length + str_length + 1, sizeof(char));
  }
  if (res) {
    for (s21_size_t i = 0; i < fin_length; i++) {
      if (i < start_index) {
        res[i] = src[i];
      } else if (i < str_length + start_index) {
        res[i] = str[i - start_index];
      } else {
        res[i] = src[i - str_length];
      }
    }
  }
  return res;
}