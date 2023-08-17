#ifndef SRC_VALIDATION_S21_VALIDATION_H_
#define SRC_VALIDATION_S21_VALIDATION_H_

#define INPUT_MAX_LENGTH 255

#define OK 1
#define ERROR 0

#include "../additional/s21_additional.h"
#include "../s21_calculator.h"

// Main validation function:
int s21_validation(char *string);

// Function validations:
int s21_acos_asin_atan_validation(char *string);
int s21_cos_validation(char *string);
int s21_ln_log_validation(char *string);
int s21_sin_sqrt_validation(char *string);
int s21_tan_validation(char *string);

// Other validations:
int s21_binary_operator_validation(char *string);
int s21_double_number_validation(char *string);
int s21_double_symbol_validation(char *string);
int s21_empty_brackets_validation(char *string);
int s21_glued_values_validation(char *string);
int s21_is_equality_brackets(char *string);
int s21_is_valid_string(char *string);
int s21_mod_validation(char *string);
int s21_number_validation(char *string);
int s21_unary_operator_validation(char *string);

#endif  // SRC_VALIDATION_S21_VALIDATION_H_