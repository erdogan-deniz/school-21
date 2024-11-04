#include "s21_string.h"

char *s21_strcpy(char *dest, const char *src) {
  char *cpindest = dest;
  if (src != s21_NULL && dest != s21_NULL) {
    while (*src != '\0') {
      *dest = *src;
      dest++;
      src++;
    }
    *dest = '\0';
  }
  return cpindest;
}