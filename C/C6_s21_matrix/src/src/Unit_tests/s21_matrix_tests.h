#ifndef SRC_UNIT_TESTS_S21_MATRIX_H_
#define SRC_UNIT_TESTS_S21_MATRIX_H_

#include "../s21_matrix.h"
#include <check.h>
#include <stdlib.h>
#include <time.h>

Suite *suite_s21_eq_matrix(void);
Suite *suite_s21_create_matrix(void);
Suite *suite_s21_sum_matrix(void);
Suite *suite_s21_sub_matrix(void);
Suite *suite_s21_mult_number_matrix(void);
Suite *suite_s21_mult_matrix(void);
Suite *suite_s21_transpose_matrix(void);
Suite *suite_s21_calc_complements(void);
Suite *suite_s21_determinant(void);
Suite *suite_s21_inverse_matrix(void);

void run_tests(void);
void run_testcase(Suite *testcase);
double get_rand(double min, double max);
#endif  //  SRC_UNIT_TESTS_S21_MATRIX_H_