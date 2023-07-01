#include "../s21_matrix_tests.h"

START_TEST(transpose_matrix) {
  const int rows = rand() % 100 + 1;
  const int cols = rand() % 100 + 1;
  matrix_t m = {0};
  matrix_t check = {0};
  matrix_t res = {0};

  s21_create_matrix(rows, cols, &m);
  s21_create_matrix(cols, rows, &check);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      double rand_val = get_rand(-10e10, 10e10);
      m.matrix[i][j] = rand_val;
      check.matrix[j][i] = rand_val;
    }
  }

  ck_assert_int_eq(s21_transpose(&m, &res), OK);
  ck_assert_int_eq(s21_eq_matrix(&check, &res), SUCCESS);
  s21_remove_matrix(&m);
  s21_remove_matrix(&res);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(transpose_matrix2) {
  int rows = rand() % 100 + 1;
  int cols = rand() % 100 + 1;
  matrix_t res = {0};
  matrix_t m = {0};
  matrix_t check = {0};

  rows = -rows;
  cols = -cols;
  
  s21_create_matrix(rows, cols, &m);
  s21_create_matrix(cols, rows, &check); 
  ck_assert_int_eq(s21_transpose(&m, &res), INCORRECT_MATRIX);
  s21_remove_matrix(&m);
  s21_remove_matrix(&res);
  s21_remove_matrix(&check);
}
END_TEST

Suite *suite_s21_transpose(void) {
  Suite *suite = suite_create("suite_s21_transpose");
  TCase *tcase = tcase_create("s21_transpose");

  tcase_add_loop_test(tcase, transpose_matrix, 0, 100);
  tcase_add_loop_test(tcase, transpose_matrix2, 0, 100);

  suite_add_tcase(suite, tcase);
  return suite;
}