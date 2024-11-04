#include "s21_string.h"

s21_size_t s21_strspn(const char *str1, const char *str2) {
  s21_size_t lenght = 0;
  const char *sym;
  for (; *str1; str1++, lenght++) {
    for (sym = str2; *sym && *sym != *str1; sym++)
      ;
    if (!*sym) break;
  }
  return lenght;
}