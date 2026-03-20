#ifndef SRC_ADDITIONAL_S21_ADDITIONAL_H_
#define SRC_ADDITIONAL_S21_ADDITIONAL_H_

#include "../list/s21_list.h"

#define empty 0

// Status:
#define OK 1
#define ERROR 0

// Transform types:
int s21_char_to_int(char digit);
char* s21_char_to_string(char symbol);  // free() result
int s21_string_to_int(char* string);
long double s21_string_to_long_double(char* string);

// Functions for stack:
s21_token_priority s21_get_priority_token(char* token);
int s21_is_unary_token(char* token);

// Functions for list:
long double s21_get_value(s21_list* list);
s21_list* s21_set_value(s21_list* list, long double value);  // s21_free_list()

// Validation functions:
int s21_count_points(char* string);
int s21_have_number(char* string);
int s21_have_point(char* string);
int s21_have_x(char* string);
int s21_is_int(char* string);
int s21_is_sign(char symbol);
int s21_is_valid_symbol(char symbol);

#endif  // SRC_ADDITIONAL_S21_ADDITIONAL_H_