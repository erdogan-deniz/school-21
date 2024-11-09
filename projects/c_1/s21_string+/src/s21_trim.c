#include "s21_string.h"

void delete_first_letter(char *str);
void delete_left_part(char *result, const char *src, const char *trim_chars);
void delete_right_part(char *result, const char *src, const char *trim_chars);

void *s21_trim(const char *src, const char *trim_chars) {
  int is_error = 0;
  char *result = s21_NULL;
  if (src) {
    char default_chars[7] = " \t\n\v\r\f\0";
    if (trim_chars == s21_NULL || s21_strlen(trim_chars) == 0)
      trim_chars = default_chars;
    result = (char *)calloc(s21_strlen(src) + 10, sizeof(char));
    if (result == s21_NULL) {
      is_error = 1;
    }
    s21_strcpy(result, (char *)src);
    delete_left_part(result, src, trim_chars);
    delete_right_part(result, src, trim_chars);
  } else {
    is_error = 1;
  }
  return is_error ? s21_NULL : (void *)result;
}

void delete_first_letter(char *str) {
  s21_size_t counter = 0;
  while (str[counter]) {
    str[counter] = str[counter + 1];
    counter++;
  }
}

void delete_left_part(char *result, const char *src, const char *trim_chars) {
  s21_size_t format_length = s21_strlen(trim_chars);
  s21_size_t str_length = s21_strlen(src);
  for (s21_size_t i = 0; i < str_length; i++) {
    int is_break = 0;
    for (s21_size_t j = 0; j < format_length; j++) {
      if (src[i] == trim_chars[j]) {
        delete_first_letter(result);
        break;
      }
      if (j == format_length - 1 && src[i] != trim_chars[format_length]) {
        is_break = 1;
      }
    }
    if (is_break) break;
  }
}

void delete_right_part(char *result, const char *src, const char *trim_chars) {
  s21_size_t format_length = s21_strlen(trim_chars);
  s21_size_t result_length = s21_strlen(result);
  for (int i = (int)result_length - 1; i >= 0; i--) {
    int is_break = 0;
    for (s21_size_t j = 0; j < format_length; j++) {
      if (result[i] == trim_chars[j]) {
        result[i] = '\0';
        break;
      }
      if (j == format_length - 1 && src[i] != trim_chars[format_length]) {
        is_break = 1;
      }
    }
    if (is_break) break;
  }
}