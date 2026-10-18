#ifndef S21_STRING_TEST_H
#define S21_STRING_TEST_H

#include <check.h>
#include <locale.h>
#include <stdio.h>
#include <string.h>

#include "s21_string.h"

#define BUFF_SIZE 512

Suite *suite_part1(void);
Suite *suite_str(void);
Suite *suite_part5(void);
Suite *suite_mem(void);
Suite *suite_sprintf(void);
Suite *suite_sprintf_hex(void);
Suite *suite_sscanf_1(void);
Suite *suite_sscanf_2(void);

#endif  // S21_STRING_TEST_H
