#include "../s21_matrix_tests.h"

START_TEST(sub_matrix) {
  int rows = rand() % 100 + 1;
  int cols = rand() % 100 + 1;
  matrix_t m = {0};
  matrix_t mtx = {0};
  matrix_t check = {0};
  matrix_t res = {0};

  s21_create_matrix(rows, cols, &m);  
  s21_create_matrix(rows, cols, &mtx);
  s21_create_matrix(rows, cols, &check);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      m.matrix[i][j] = get_rand(DBL_MIN, DBL_MAX);
      mtx.matrix[i][j] = get_rand(DBL_MIN, DBL_MAX);
      check.matrix[i][j] = m.matrix[i][j] - mtx.matrix[i][j];
    }
  }
  
  ck_assert_int_eq(s21_sub_matrix(&m, &mtx, &res), OK);
  ck_assert_int_eq(s21_eq_matrix(&check, &res), SUCCESS);
  s21_remove_matrix(&m);
  s21_remove_matrix(&mtx);
  s21_remove_matrix(&res);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(sub_matrix1) {
  matrix_t m = {0};
  matrix_t mtx = {0};
  matrix_t res = {0};
  const int rows = rand() % 100 + 1;
  const int cols = rand() % 100 + 1;
  const int rows1 = rand() % 100 + 1;
  const int cols1 = rand() % 100 + 1;

  s21_create_matrix(rows, cols, &m);
  s21_create_matrix(rows1, cols1, &mtx);

  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++)
      m.matrix[i][j] = get_rand(DBL_MIN, DBL_MAX) + 1;

  for (int i = 0; i < rows1; i++)
    for (int j = 0; j < cols1; j++)
      mtx.matrix[i][j] = get_rand(DBL_MIN, DBL_MAX);
  
  ck_assert_int_eq(s21_sub_matrix(&m, &mtx, &res), CALCULATION_ERROR);
  s21_remove_matrix(&m);
  s21_remove_matrix(&mtx);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(sub_matrix2) {
  int rows = rand() % 100 + 1;
  int cols = rand() % 100 + 1;
  matrix_t m = {0};
  matrix_t mtx = {0};
  matrix_t check = {0};
  matrix_t res = {0};
  
  rows = -rows;
  cols = -cols;

  s21_create_matrix(rows, cols, &m);
  s21_create_matrix(rows, cols, &mtx);
  s21_create_matrix(rows, cols, &check);
  ck_assert_int_eq(s21_sub_matrix(&m, &mtx, &res), INCORRECT_MATRIX);
  s21_remove_matrix(&m);
  s21_remove_matrix(&mtx);
  s21_remove_matrix(&res);
  s21_remove_matrix(&check);
}
END_TEST

Suite *suite_s21_sub_matrix(void) {
  Suite *suite = suite_create("suite_s21_sub_matrix");
  TCase *tcase = tcase_create("s21_sub_matrix");

  tcase_add_loop_test(tcase, sub_matrix, 0, 100);
  tcase_add_loop_test(tcase, sub_matrix1, 0, 100);
  tcase_add_loop_test(tcase, sub_matrix2, 0, 100);

  suite_add_tcase(suite, tcase);
  return suite;
}