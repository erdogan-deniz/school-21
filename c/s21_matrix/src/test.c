#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "s21_matrix.h"

double get_rand(double min, double max) {
  double val = (double)rand() / RAND_MAX;
  return min + val * (max - min);
}

START_TEST(create_matrix_1) {
  matrix_t matrix = {0};
  int rows = rand() % 100 + 1;
  int columns = rand() % 100 + 1;
  int code = s21_create_matrix(rows, columns, &matrix);
  ck_assert_int_eq(code, OK);
  ck_assert_int_eq(matrix.rows, rows);
  ck_assert_int_eq(matrix.columns, columns);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      ck_assert_double_eq(matrix.matrix[i][j], 0.0);
    }
  }
  s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(create_matrix_2) {
  matrix_t matrix = {0};
  int rows = 0;
  int columns = 10;
  int code = s21_create_matrix(rows, columns, &matrix);
  ck_assert_int_eq(code, MATRIX_ERROR);
  ck_assert_int_eq(matrix.rows, 0);
  ck_assert_int_eq(matrix.columns, 0);
  ck_assert_ptr_null(matrix.matrix);
}
END_TEST

START_TEST(create_matrix_3) {
  matrix_t matrix = {0};
  int rows = 10;
  int columns = 0;
  int code = s21_create_matrix(rows, columns, &matrix);
  ck_assert_int_eq(code, MATRIX_ERROR);
  ck_assert_int_eq(matrix.rows, 0);
  ck_assert_int_eq(matrix.columns, 0);
  ck_assert_ptr_null(matrix.matrix);
}
END_TEST

START_TEST(create_matrix_4) {
  matrix_t matrix = {0};
  int rows = 0;
  int columns = 0;
  int code = s21_create_matrix(rows, columns, &matrix);
  ck_assert_int_eq(code, MATRIX_ERROR);
  ck_assert_int_eq(matrix.rows, 0);
  ck_assert_int_eq(matrix.columns, 0);
  ck_assert_ptr_null(matrix.matrix);
}
END_TEST

START_TEST(remove_matrix_1) {
  matrix_t matrix = {0};
  int rows = rand() % 100 + 1;
  int columns = rand() % 100 + 1;
  s21_create_matrix(rows, columns, &matrix);

  s21_remove_matrix(&matrix);
  ck_assert_int_eq(matrix.rows, 0);
  ck_assert_int_eq(matrix.columns, 0);
  ck_assert_ptr_null(matrix.matrix);
}
END_TEST

START_TEST(remove_matrix_2) {
  matrix_t matrix = {0};
  int rows = 0;
  int columns = 10;
  s21_create_matrix(rows, columns, &matrix);

  s21_remove_matrix(&matrix);
  ck_assert_int_eq(matrix.rows, 0);
  ck_assert_int_eq(matrix.columns, 0);
  ck_assert_ptr_null(matrix.matrix);
}
END_TEST

START_TEST(remove_matrix_3) {
  matrix_t matrix = {0};
  int rows = 10;
  int columns = 0;
  s21_create_matrix(rows, columns, &matrix);

  s21_remove_matrix(&matrix);
  ck_assert_int_eq(matrix.rows, 0);
  ck_assert_int_eq(matrix.columns, 0);
  ck_assert_ptr_null(matrix.matrix);
}
END_TEST

START_TEST(remove_matrix_4) {
  matrix_t matrix = {0};
  int rows = 0;
  int columns = 0;
  s21_create_matrix(rows, columns, &matrix);

  s21_remove_matrix(&matrix);
  ck_assert_int_eq(matrix.rows, 0);
  ck_assert_int_eq(matrix.columns, 0);
  ck_assert_ptr_null(matrix.matrix);
}
END_TEST

START_TEST(eq_matrix_1) {
  matrix_t matrix_1 = {0};
  matrix_t matrix_2 = {0};
  int rows = rand() % 100 + 1;
  int columns = rand() % 100 + 1;
  double counter = rand() % 100 + 1;
  s21_create_matrix(rows, columns, &matrix_1);
  s21_create_matrix(rows, columns, &matrix_2);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      matrix_1.matrix[i][j] = counter;
      matrix_2.matrix[i][j] = counter;
      counter++;
    }
  }

  ck_assert_int_eq(s21_eq_matrix(&matrix_1, &matrix_2), SUCCESS);

  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
}
END_TEST

START_TEST(eq_matrix_2) {
  matrix_t matrix_1 = {0};
  matrix_t matrix_2 = {0};
  int rows = rand() % 100 + 1;
  int columns = rand() % 100 + 1;
  s21_create_matrix(rows + 1, columns, &matrix_1);
  s21_create_matrix(rows, columns, &matrix_2);

  ck_assert_int_eq(s21_eq_matrix(&matrix_1, &matrix_2), FAILURE);

  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
}
END_TEST

START_TEST(eq_matrix_3) {
  matrix_t matrix_1 = {0};
  matrix_t matrix_2 = {0};
  int rows = rand() % 100 + 1;
  int columns = rand() % 100 + 1;
  s21_create_matrix(rows, columns + 1, &matrix_1);
  s21_create_matrix(rows, columns, &matrix_2);

  ck_assert_int_eq(s21_eq_matrix(&matrix_1, &matrix_2), FAILURE);

  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
}
END_TEST

START_TEST(eq_matrix_4) {
  matrix_t matrix_1 = {0};
  matrix_t matrix_2 = {0};
  int rows = rand() % 100 + 1;
  int columns = rand() % 100 + 1;
  s21_create_matrix(rows, columns, &matrix_1);
  s21_create_matrix(rows - 1, columns, &matrix_2);

  ck_assert_int_eq(s21_eq_matrix(&matrix_1, &matrix_2), FAILURE);

  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
}
END_TEST

START_TEST(eq_matrix_5) {
  matrix_t matrix_1 = {0};
  matrix_t matrix_2 = {0};
  int rows = rand() % 100 + 1;
  int columns = rand() % 100 + 1;
  s21_create_matrix(rows, columns, &matrix_1);
  s21_create_matrix(rows, columns - 1, &matrix_2);

  ck_assert_int_eq(s21_eq_matrix(&matrix_1, &matrix_2), FAILURE);

  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
}
END_TEST

START_TEST(eq_matrix_6) {
  matrix_t matrix_1 = {0};
  matrix_t matrix_2 = {0};
  int rows = rand() % 100 + 1;
  int columns = rand() % 100 + 1;
  s21_create_matrix(rows, columns, &matrix_2);

  ck_assert_int_eq(s21_eq_matrix(&matrix_1, &matrix_2), FAILURE);

  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
}
END_TEST

START_TEST(eq_matrix_7) {
  matrix_t matrix_1 = {0};
  matrix_t matrix_2 = {0};
  int rows = rand() % 100 + 1;
  int columns = rand() % 100 + 1;
  s21_create_matrix(rows, columns, &matrix_1);

  ck_assert_int_eq(s21_eq_matrix(&matrix_1, &matrix_2), FAILURE);

  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
}
END_TEST

START_TEST(eq_matrix_8) {
  matrix_t matrix_1 = {0};
  matrix_t matrix_2 = {0};
  int rows = rand() % 100 + 1;
  int columns = rand() % 100 + 1;
  s21_create_matrix(rows, columns, &matrix_1);
  s21_create_matrix(rows, columns, &matrix_2);

  ck_assert_int_eq(s21_eq_matrix(&matrix_1, &matrix_2), SUCCESS);

  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
}
END_TEST

START_TEST(eq_matrix_9) {
  matrix_t matrix_1 = {0};
  matrix_t matrix_2 = {0};
  int rows = rand() % 100 + 1;
  int columns = rand() % 100 + 1;
  double counter = rand() % 100 + 1;
  s21_create_matrix(rows, columns, &matrix_1);
  s21_create_matrix(rows, columns, &matrix_2);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      matrix_1.matrix[i][j] = counter;
      matrix_2.matrix[i][j] = counter;
      counter++;
    }
  }
  matrix_1.matrix[0][0] = 2e-6;

  ck_assert_int_eq(s21_eq_matrix(&matrix_1, &matrix_2), FAILURE);

  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
}
END_TEST

START_TEST(sum_matrix_1) {
  matrix_t matrix_1 = {0};
  matrix_t matrix_2 = {0};
  matrix_t matrix_3 = {0};
  int rows = rand() % 100 + 1;
  int columns = rand() % 100 + 1;
  double rand_num = rand() % 100 + 1;
  double counter = rand_num;
  s21_create_matrix(rows, columns, &matrix_1);
  s21_create_matrix(rows, columns, &matrix_2);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      matrix_1.matrix[i][j] = counter;
      matrix_2.matrix[i][j] = counter;
      counter--;
    }
  }

  int code = s21_sum_matrix(&matrix_1, &matrix_2, &matrix_3);
  counter = rand_num;

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      bool answer = fabs((counter + counter) - matrix_3.matrix[i][j]) > EPS;
      counter--;
      ck_assert_int_eq(0, answer);
    }
  }

  ck_assert_int_eq(code, OK);
  ck_assert_int_eq(matrix_3.rows, rows);
  ck_assert_int_eq(matrix_3.columns, columns);

  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
  s21_remove_matrix(&matrix_3);
}
END_TEST

START_TEST(sum_matrix_2) {
  matrix_t matrix_1 = {0};
  matrix_t matrix_2 = {0};
  matrix_t matrix_3 = {0};
  int rows = rand() % 100 + 1;
  int columns = rand() % 100 + 1;
  double rand_num = rand() % 100 + 1;
  double counter = rand_num;
  s21_create_matrix(rows, columns, &matrix_1);
  s21_create_matrix(rows, columns, &matrix_2);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      matrix_1.matrix[i][j] = counter;
      matrix_2.matrix[i][j] = counter;
      counter--;
    }
  }
  matrix_1.columns++;

  int code = s21_sum_matrix(&matrix_1, &matrix_2, &matrix_3);

  ck_assert_int_eq(code, CALC_ERROR);

  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
  s21_remove_matrix(&matrix_3);
}
END_TEST

START_TEST(sum_matrix_3) {
  matrix_t matrix_1 = {0};
  matrix_t matrix_2 = {0};
  matrix_t matrix_3 = {0};
  int rows = rand() % 100 + 1;
  int columns = rand() % 100 + 1;
  double counter = 5.0;
  s21_create_matrix(rows, columns, &matrix_1);
  s21_create_matrix(rows, columns, &matrix_2);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      matrix_1.matrix[i][j] = counter;
      matrix_2.matrix[i][j] = counter;
      counter--;
    }
  }
  matrix_2.columns++;

  int code = s21_sum_matrix(&matrix_1, &matrix_2, &matrix_3);

  ck_assert_int_eq(code, CALC_ERROR);

  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
  s21_remove_matrix(&matrix_3);
}
END_TEST

START_TEST(sum_matrix_4) {
  matrix_t matrix_1 = {0};
  matrix_t matrix_2 = {0};
  matrix_t matrix_3 = {0};
  int rows = rand() % 100 + 1;
  int columns = rand() % 100 + 1;
  double counter = 5.0;
  s21_create_matrix(rows, columns, &matrix_1);
  s21_create_matrix(rows, columns, &matrix_2);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      matrix_1.matrix[i][j] = counter;
      matrix_2.matrix[i][j] = counter;
      counter--;
    }
  }
  matrix_1.rows++;

  int code = s21_sum_matrix(&matrix_1, &matrix_2, &matrix_3);

  ck_assert_int_eq(code, CALC_ERROR);

  matrix_1.rows--;
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
  s21_remove_matrix(&matrix_3);
}
END_TEST

START_TEST(sum_matrix_5) {
  matrix_t matrix_1 = {0};
  matrix_t matrix_2 = {0};
  matrix_t matrix_3 = {0};
  int rows = rand() % 100 + 1;
  int columns = rand() % 100 + 1;
  double counter = 5.0;
  s21_create_matrix(rows, columns, &matrix_1);
  s21_create_matrix(rows, columns, &matrix_2);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      matrix_1.matrix[i][j] = counter;
      matrix_2.matrix[i][j] = counter;
      counter--;
    }
  }
  matrix_2.columns++;

  int code = s21_sum_matrix(&matrix_1, &matrix_2, &matrix_3);

  ck_assert_int_eq(code, CALC_ERROR);

  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
  s21_remove_matrix(&matrix_3);
}
END_TEST

START_TEST(sum_matrix_6) {
  matrix_t matrix_1 = {0};
  matrix_t matrix_2 = {0};
  matrix_t matrix_3 = {0};
  int rows = rand() % 100 + 1;
  int columns = rand() % 100 + 1;

  s21_create_matrix(rows, columns, &matrix_1);

  int code = s21_sum_matrix(&matrix_1, &matrix_2, &matrix_3);

  ck_assert_int_eq(code, MATRIX_ERROR);

  s21_remove_matrix(&matrix_1);
}
END_TEST

START_TEST(sum_matrix_7) {
  matrix_t matrix_1 = {0};
  matrix_t matrix_2 = {0};
  matrix_t matrix_3 = {0};
  int rows = rand() % 100 + 1;
  int columns = rand() % 100 + 1;

  s21_create_matrix(rows, columns, &matrix_2);

  int code = s21_sum_matrix(&matrix_1, &matrix_2, &matrix_3);

  ck_assert_int_eq(code, MATRIX_ERROR);

  s21_remove_matrix(&matrix_2);
}
END_TEST

START_TEST(sub_matrix_1) {
  matrix_t matrix_1 = {0};
  matrix_t matrix_2 = {0};
  matrix_t matrix_3 = {0};
  int rows = rand() % 100 + 1;
  int columns = rand() % 100 + 1;
  double rand_num = rand() % 100 + 1;
  double counter = rand_num;
  s21_create_matrix(rows, columns, &matrix_1);
  s21_create_matrix(rows, columns, &matrix_2);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      matrix_1.matrix[i][j] = counter;
      matrix_2.matrix[i][j] = counter;
      counter--;
    }
  }

  int code = s21_sub_matrix(&matrix_1, &matrix_2, &matrix_3);
  counter = rand_num;

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      bool answer = fabs(matrix_3.matrix[i][j]) > EPS;
      counter--;
      ck_assert_int_eq(0, answer);
    }
  }

  ck_assert_int_eq(code, OK);
  ck_assert_int_eq(matrix_3.rows, rows);
  ck_assert_int_eq(matrix_3.columns, columns);

  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
  s21_remove_matrix(&matrix_3);
}
END_TEST

START_TEST(sub_matrix_2) {
  matrix_t matrix_1 = {0};
  matrix_t matrix_2 = {0};
  matrix_t matrix_3 = {0};
  int rows = rand() % 100 + 1;
  int columns = rand() % 100 + 1;
  double rand_num = rand() % 100 + 1;
  double counter = rand_num;
  s21_create_matrix(rows, columns, &matrix_1);
  s21_create_matrix(rows, columns, &matrix_2);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      matrix_1.matrix[i][j] = counter;
      matrix_2.matrix[i][j] = counter;
      counter--;
    }
  }
  matrix_1.columns++;

  int code = s21_sub_matrix(&matrix_1, &matrix_2, &matrix_3);

  ck_assert_int_eq(code, CALC_ERROR);

  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
  s21_remove_matrix(&matrix_3);
}
END_TEST

START_TEST(sub_matrix_3) {
  matrix_t matrix_1 = {0};
  matrix_t matrix_2 = {0};
  matrix_t matrix_3 = {0};
  int rows = rand() % 100 + 1;
  int columns = rand() % 100 + 1;
  double counter = 5.0;
  s21_create_matrix(rows, columns, &matrix_1);
  s21_create_matrix(rows, columns, &matrix_2);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      matrix_1.matrix[i][j] = counter;
      matrix_2.matrix[i][j] = counter;
      counter--;
    }
  }
  matrix_2.columns++;

  int code = s21_sub_matrix(&matrix_1, &matrix_2, &matrix_3);

  ck_assert_int_eq(code, CALC_ERROR);

  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
  s21_remove_matrix(&matrix_3);
}
END_TEST

START_TEST(sub_matrix_4) {
  matrix_t matrix_1 = {0};
  matrix_t matrix_2 = {0};
  matrix_t matrix_3 = {0};
  int rows = rand() % 100 + 1;
  int columns = rand() % 100 + 1;
  double counter = 5.0;
  s21_create_matrix(rows, columns, &matrix_1);
  s21_create_matrix(rows, columns, &matrix_2);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      matrix_1.matrix[i][j] = counter;
      matrix_2.matrix[i][j] = counter;
      counter--;
    }
  }
  matrix_1.rows++;

  int code = s21_sub_matrix(&matrix_1, &matrix_2, &matrix_3);

  ck_assert_int_eq(code, CALC_ERROR);

  matrix_1.rows--;
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
  s21_remove_matrix(&matrix_3);
}
END_TEST

START_TEST(sub_matrix_5) {
  matrix_t matrix_1 = {0};
  matrix_t matrix_2 = {0};
  matrix_t matrix_3 = {0};
  int rows = rand() % 100 + 1;
  int columns = rand() % 100 + 1;
  double counter = 5.0;
  s21_create_matrix(rows, columns, &matrix_1);
  s21_create_matrix(rows, columns, &matrix_2);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      matrix_1.matrix[i][j] = counter;
      matrix_2.matrix[i][j] = counter;
      counter--;
    }
  }
  matrix_2.columns++;

  int code = s21_sub_matrix(&matrix_1, &matrix_2, &matrix_3);

  ck_assert_int_eq(code, CALC_ERROR);

  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
  s21_remove_matrix(&matrix_3);
}
END_TEST

START_TEST(sub_matrix_6) {
  matrix_t matrix_1 = {0};
  matrix_t matrix_2 = {0};
  matrix_t matrix_3 = {0};
  int rows = rand() % 100 + 1;
  int columns = rand() % 100 + 1;

  s21_create_matrix(rows, columns, &matrix_1);

  int code = s21_sub_matrix(&matrix_1, &matrix_2, &matrix_3);

  ck_assert_int_eq(code, MATRIX_ERROR);

  s21_remove_matrix(&matrix_1);
}
END_TEST

START_TEST(sub_matrix_7) {
  matrix_t matrix_1 = {0};
  matrix_t matrix_2 = {0};
  matrix_t matrix_3 = {0};
  int rows = rand() % 100 + 1;
  int columns = rand() % 100 + 1;

  s21_create_matrix(rows, columns, &matrix_2);

  int code = s21_sub_matrix(&matrix_1, &matrix_2, &matrix_3);

  ck_assert_int_eq(code, MATRIX_ERROR);

  s21_remove_matrix(&matrix_2);
}
END_TEST

START_TEST(mult_number_1) {
  matrix_t matrix_1 = {0};
  matrix_t matrix_2 = {0};
  int rows = rand() % 100 + 1;
  int columns = rand() % 100 + 1;
  double number = 3.0;
  double counter = 0.0;
  s21_create_matrix(rows, columns, &matrix_1);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      matrix_1.matrix[i][j] = counter;
      counter++;
    }
  }

  int code = s21_mult_number(&matrix_1, number, &matrix_2);
  counter = 0.0;

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      bool answer = fabs(counter * number - matrix_2.matrix[i][j]) > EPS;
      counter++;
      ck_assert_int_eq(0, answer);
    }
  }

  ck_assert_int_eq(code, OK);
  ck_assert_int_eq(matrix_2.rows, rows);
  ck_assert_int_eq(matrix_2.columns, columns);

  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
}
END_TEST

START_TEST(mult_number_2) {
  matrix_t matrix_1 = {0};
  matrix_t matrix_2 = {0};
  int rows = 0;
  int columns = 10;
  double number = 3.0;

  int code = s21_create_matrix(rows, columns, &matrix_1);

  code = s21_mult_number(&matrix_1, number, &matrix_2);

  ck_assert_int_eq(code, MATRIX_ERROR);

  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
}
END_TEST

START_TEST(mult_matrix_1) {
  const int rows = rand() % 100 + 1;
  const int cols = rand() % 100 + 1;
  matrix_t matrix_1 = {0};
  matrix_t matrix_2 = {0};
  s21_create_matrix(rows, cols, &matrix_1);
  s21_create_matrix(cols, rows, &matrix_2);

  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++)
      matrix_1.matrix[i][j] = get_rand(-10e10, 10e10);

  for (int i = 0; i < cols; i++)
    for (int j = 0; j < rows; j++)
      matrix_2.matrix[i][j] = get_rand(-10e10, 10e10);
  matrix_t check = {0};
  s21_create_matrix(matrix_1.rows, matrix_2.columns, &check);

  for (int i = 0; i < matrix_1.rows; i++) {
    for (int j = 0; j < matrix_2.columns; j++) {
      check.matrix[i][j] = 0;
      for (int k = 0; k < matrix_1.columns; k++)
        check.matrix[i][j] += matrix_1.matrix[i][k] * matrix_2.matrix[k][j];
    }
  }

  matrix_t res = {0};
  ck_assert_int_eq(s21_mult_matrix(&matrix_1, &matrix_2, &res), OK);
  ck_assert_int_eq(s21_eq_matrix(&check, &res), SUCCESS);

  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
  s21_remove_matrix(&res);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(mult_matrix_2) {
  const int rows = rand() % 100 + 1;
  const int cols = rand() % 100 + 1;
  matrix_t matrix_1 = {0};
  matrix_t matrix_2 = {0};
  s21_create_matrix(rows, cols, &matrix_1);
  s21_create_matrix(cols, rows, &matrix_2);

  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++)
      matrix_1.matrix[i][j] = get_rand(-10e10, 10e10);

  for (int i = 0; i < cols; i++)
    for (int j = 0; j < rows; j++)
      matrix_2.matrix[i][j] = get_rand(-10e10, 10e10);
  matrix_t check = {0};
  s21_create_matrix(matrix_1.rows, matrix_2.columns, &check);

  for (int i = 0; i < matrix_1.rows; i++) {
    for (int j = 0; j < matrix_2.columns; j++) {
      check.matrix[i][j] = 0;
      for (int k = 0; k < matrix_1.columns; k++)
        check.matrix[i][j] += matrix_1.matrix[i][k] * matrix_2.matrix[k][j];
    }
  }

  matrix_t res = {0};
  matrix_1.columns = 0;
  ck_assert_int_eq(s21_mult_matrix(&matrix_1, &matrix_2, &res), MATRIX_ERROR);

  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
  s21_remove_matrix(&res);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(mult_matrix_3) {
  const int rows = rand() % 100 + 1;
  const int cols = rand() % 100 + 1;
  matrix_t matrix_1 = {0};
  matrix_t matrix_2 = {0};
  s21_create_matrix(rows, cols, &matrix_1);
  s21_create_matrix(cols, rows, &matrix_2);

  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++)
      matrix_1.matrix[i][j] = get_rand(-10e10, 10e10);

  for (int i = 0; i < cols; i++)
    for (int j = 0; j < rows; j++)
      matrix_2.matrix[i][j] = get_rand(-10e10, 10e10);
  matrix_t check = {0};
  s21_create_matrix(matrix_1.rows, matrix_2.columns, &check);

  for (int i = 0; i < matrix_1.rows; i++) {
    for (int j = 0; j < matrix_2.columns; j++) {
      check.matrix[i][j] = 0;
      for (int k = 0; k < matrix_1.columns; k++)
        check.matrix[i][j] += matrix_1.matrix[i][k] * matrix_2.matrix[k][j];
    }
  }

  matrix_t res = {0};
  matrix_1.columns++;
  ck_assert_int_eq(s21_mult_matrix(&matrix_1, &matrix_2, &res), CALC_ERROR);

  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(transpose_1) {
  const int rows = rand() % 100 + 1;
  const int cols = rand() % 100 + 1;
  matrix_t matrix_1 = {0};
  matrix_t check = {0};
  s21_create_matrix(rows, cols, &matrix_1);
  s21_create_matrix(cols, rows, &check);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      double rand_val = get_rand(-10e10, 10e10);
      matrix_1.matrix[i][j] = rand_val;
      check.matrix[j][i] = rand_val;
    }
  }

  matrix_t res = {0};
  ck_assert_int_eq(s21_transpose(&matrix_1, &res), OK);
  ck_assert_int_eq(s21_eq_matrix(&check, &res), SUCCESS);

  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&res);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(transpose_2) {
  const int rows = rand() % 100 + 1;
  const int cols = rand() % 100 + 1;
  matrix_t matrix_1 = {0};
  matrix_t check = {0};
  s21_create_matrix(rows, cols, &matrix_1);
  s21_create_matrix(cols, rows, &check);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      double rand_val = get_rand(-10e10, 10e10);
      matrix_1.matrix[i][j] = rand_val;
      check.matrix[j][i] = rand_val;
    }
  }

  matrix_t res = {0};
  matrix_1.columns = 0;
  ck_assert_int_eq(s21_transpose(&matrix_1, &res), MATRIX_ERROR);

  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(calc_complements_1) {
  const int size = 3;

  matrix_t matrix = {0};
  s21_create_matrix(size, size, &matrix);
  matrix.matrix[0][0] = 1;
  matrix.matrix[0][1] = 2;
  matrix.matrix[0][2] = 3;
  matrix.matrix[1][0] = 0;
  matrix.matrix[1][1] = 4;
  matrix.matrix[1][2] = 2;
  matrix.matrix[2][0] = 5;
  matrix.matrix[2][1] = 2;
  matrix.matrix[2][2] = 1;

  matrix_t expected = {0};
  s21_create_matrix(size, size, &expected);
  expected.matrix[0][0] = 0;
  expected.matrix[0][1] = 10;
  expected.matrix[0][2] = -20;
  expected.matrix[1][0] = 4;
  expected.matrix[1][1] = -14;
  expected.matrix[1][2] = 8;
  expected.matrix[2][0] = -8;
  expected.matrix[2][1] = -2;
  expected.matrix[2][2] = 4;

  matrix_t res = {0};
  int code = s21_calc_complements(&matrix, &res);

  ck_assert_int_eq(s21_eq_matrix(&expected, &res), SUCCESS);
  ck_assert_int_eq(code, OK);

  s21_remove_matrix(&matrix);
  s21_remove_matrix(&res);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(calc_complements_2) {
  const int size = 1;

  matrix_t matrix = {0};
  s21_create_matrix(size, size, &matrix);
  matrix.matrix[0][0] = 123.123;

  matrix_t expected = {0};
  s21_create_matrix(size, size, &expected);
  expected.matrix[0][0] = 123.123;

  matrix_t res = {0};
  int code = s21_calc_complements(&matrix, &res);

  ck_assert_int_eq(s21_eq_matrix(&expected, &res), SUCCESS);
  ck_assert_int_eq(code, OK);

  s21_remove_matrix(&matrix);
  s21_remove_matrix(&res);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(calc_complements_3) {
  const int size = 3;

  matrix_t matrix = {0};
  s21_create_matrix(size, size, &matrix);
  matrix.matrix[0][0] = 1;
  matrix.matrix[0][1] = 2;
  matrix.matrix[0][2] = 3;
  matrix.matrix[1][0] = 0;
  matrix.matrix[1][1] = 4;
  matrix.matrix[1][2] = 2;
  matrix.matrix[2][0] = 5;
  matrix.matrix[2][1] = 2;
  matrix.matrix[2][2] = 1;

  matrix_t expected = {0};
  s21_create_matrix(size, size, &expected);
  expected.matrix[0][0] = 0;
  expected.matrix[0][1] = 10;
  expected.matrix[0][2] = -20;
  expected.matrix[1][0] = 4;
  expected.matrix[1][1] = -14;
  expected.matrix[1][2] = 8;
  expected.matrix[2][0] = -8;
  expected.matrix[2][1] = -2;
  expected.matrix[2][2] = 4;

  matrix_t res = {0};
  matrix.columns++;
  int code = s21_calc_complements(&matrix, &res);

  ck_assert_int_eq(code, CALC_ERROR);

  s21_remove_matrix(&matrix);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(calc_complements_4) {
  const int size = 3;

  matrix_t matrix = {0};
  s21_create_matrix(size, size, &matrix);
  matrix.matrix[0][0] = 1;
  matrix.matrix[0][1] = 2;
  matrix.matrix[0][2] = 3;
  matrix.matrix[1][0] = 0;
  matrix.matrix[1][1] = 4;
  matrix.matrix[1][2] = 2;
  matrix.matrix[2][0] = 5;
  matrix.matrix[2][1] = 2;
  matrix.matrix[2][2] = 1;

  matrix_t expected = {0};
  s21_create_matrix(size, size, &expected);
  expected.matrix[0][0] = 0;
  expected.matrix[0][1] = 10;
  expected.matrix[0][2] = -20;
  expected.matrix[1][0] = 4;
  expected.matrix[1][1] = -14;
  expected.matrix[1][2] = 8;
  expected.matrix[2][0] = -8;
  expected.matrix[2][1] = -2;
  expected.matrix[2][2] = 4;

  matrix_t res = {0};
  matrix.columns = 0;
  int code = s21_calc_complements(&matrix, &res);
  matrix.columns = size;

  ck_assert_int_eq(code, MATRIX_ERROR);

  s21_remove_matrix(&matrix);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(calc_complements_5) {
  matrix_t A, B, R;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);

  A.matrix[0][0] = 5;
  A.matrix[0][1] = -1;
  A.matrix[0][2] = 1;
  A.matrix[1][0] = 2;
  A.matrix[1][1] = 3;
  A.matrix[1][2] = 4;
  A.matrix[2][0] = 1;
  A.matrix[2][1] = 0;
  A.matrix[2][2] = 3;

  s21_calc_complements(&A, &R);

  B.matrix[0][0] = 9;
  B.matrix[0][1] = -2;
  B.matrix[0][2] = -3;
  B.matrix[1][0] = 3;
  B.matrix[1][1] = 14;
  B.matrix[1][2] = -1;
  B.matrix[2][0] = -7;
  B.matrix[2][1] = -18;
  B.matrix[2][2] = 17;

  ck_assert_int_eq(s21_eq_matrix(&R, &B), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&R);
}
END_TEST

START_TEST(calc_complements_6) {
  matrix_t A, B, R;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 3;
  A.matrix[0][2] = 6;
  A.matrix[1][0] = 1;
  A.matrix[1][1] = -10;
  A.matrix[1][2] = 8;
  A.matrix[2][0] = -3;
  A.matrix[2][1] = 4;
  A.matrix[2][2] = 5;

  s21_calc_complements(&A, &R);

  B.matrix[0][0] = -82;
  B.matrix[0][1] = -29;
  B.matrix[0][2] = -26;
  B.matrix[1][0] = 9;
  B.matrix[1][1] = 23;
  B.matrix[1][2] = -13;
  B.matrix[2][0] = 84;
  B.matrix[2][1] = -2;
  B.matrix[2][2] = -13;

  ck_assert_int_eq(s21_eq_matrix(&R, &B), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&R);
}
END_TEST

START_TEST(calc_complements_7) {
  matrix_t A, B, R;
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &B);

  A.matrix[0][0] = 123;

  s21_calc_complements(&A, &R);

  B.matrix[0][0] = 123;

  ck_assert_int_eq(s21_eq_matrix(&R, &B), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&R);
}
END_TEST

START_TEST(calc_complements_8) {
  matrix_t A, B, R;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 4;

  s21_calc_complements(&A, &R);

  B.matrix[0][0] = 4;
  B.matrix[0][1] = -3;
  B.matrix[1][0] = -2;
  B.matrix[1][1] = 1;

  ck_assert_int_eq(s21_eq_matrix(&R, &B), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&R);
}
END_TEST

START_TEST(determinant_1) {
  const int size = 3;
  matrix_t A = {0};
  s21_create_matrix(size, size, &A);

  int counter = 0;
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      A.matrix[i][j] = counter++;
    }
  }

  double result = 0.0;
  int code = s21_determinant(&A, &result);

  ck_assert_double_eq(result, 0.0);
  ck_assert_int_eq(code, OK);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_2) {
  const int size = 3;
  matrix_t A = {0};
  s21_create_matrix(size, size, &A);

  int counter = 0;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      A.matrix[i][j] = counter++;
    }
  }

  double result = 0.0;

  A.columns++;
  int code = s21_determinant(&A, &result);

  ck_assert_int_eq(code, CALC_ERROR);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_3) {
  const int size = 3;
  matrix_t A = {0};
  s21_create_matrix(size, size, &A);

  int counter = 0;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      A.matrix[i][j] = counter++;
    }
  }

  double result = 0.0;

  A.columns = 0;
  int code = s21_determinant(&A, &result);

  ck_assert_int_eq(code, MATRIX_ERROR);

  A.columns = 3;
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_4) {
  const int size = 3;
  matrix_t A = {0};
  s21_create_matrix(size, size, &A);

  int counter = 1;
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      A.matrix[i][j] = counter++;
    }
  }
  A.matrix[2][2] = 10.0;

  double result = 0.0;
  int code = s21_determinant(&A, &result);

  ck_assert_double_eq(result, -3.0);
  ck_assert_int_eq(code, OK);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_5) {
  const int size = 4;
  matrix_t A = {0};
  s21_create_matrix(size, size, &A);

  int counter = 1;
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      A.matrix[i][j] = counter++;
    }
  }

  double result = 0.0;
  int code = s21_determinant(&A, &result);

  ck_assert_double_eq(result, 0.0);
  ck_assert_int_eq(code, OK);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_6) {
  const int size = 4;
  matrix_t A = {0};
  s21_create_matrix(size, size, &A);

  A.matrix[0][0] = 9;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 2;
  A.matrix[0][3] = 4;

  A.matrix[1][0] = 3;
  A.matrix[1][1] = 4;
  A.matrix[1][2] = 4;
  A.matrix[1][3] = 4;

  A.matrix[2][0] = 4;
  A.matrix[2][1] = 4;
  A.matrix[2][2] = 9;
  A.matrix[2][3] = 9;

  A.matrix[3][0] = 1;
  A.matrix[3][1] = 1;
  A.matrix[3][2] = 5;
  A.matrix[3][3] = 1;

  double result = 0.0;
  int code = s21_determinant(&A, &result);

  ck_assert_double_eq(result, -578);
  ck_assert_int_eq(code, OK);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_7) {
  const int size = 1;
  matrix_t A = {0};
  s21_create_matrix(size, size, &A);

  A.matrix[0][0] = 9;

  double result = 0.0;
  int code = s21_determinant(&A, &result);

  ck_assert_double_eq(result, 9);
  ck_assert_int_eq(code, OK);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(inverse_matrix_1) {
  const int size = 3;

  matrix_t matrix = {0};
  s21_create_matrix(size, size, &matrix);
  matrix.matrix[0][0] = 2;
  matrix.matrix[0][1] = 5;
  matrix.matrix[0][2] = 7;
  matrix.matrix[1][0] = 6;
  matrix.matrix[1][1] = 3;
  matrix.matrix[1][2] = 4;
  matrix.matrix[2][0] = 5;
  matrix.matrix[2][1] = -2;
  matrix.matrix[2][2] = -3;

  matrix_t expected = {0};
  s21_create_matrix(size, size, &expected);
  expected.matrix[0][0] = 1;
  expected.matrix[0][1] = -1;
  expected.matrix[0][2] = 1;
  expected.matrix[1][0] = -38;
  expected.matrix[1][1] = 41;
  expected.matrix[1][2] = -34;
  expected.matrix[2][0] = 27;
  expected.matrix[2][1] = -29;
  expected.matrix[2][2] = 24;

  matrix_t res = {0};
  int code = s21_inverse_matrix(&matrix, &res);

  ck_assert_int_eq(s21_eq_matrix(&res, &expected), SUCCESS);
  ck_assert_int_eq(code, OK);

  s21_remove_matrix(&matrix);
  s21_remove_matrix(&expected);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(inverse_matrix_2) {
  const int size = 3;

  matrix_t matrix = {0};
  s21_create_matrix(size, size, &matrix);
  matrix.matrix[0][0] = 2;
  matrix.matrix[0][1] = 5;
  matrix.matrix[0][2] = 7;
  matrix.matrix[1][0] = 6;
  matrix.matrix[1][1] = 3;
  matrix.matrix[1][2] = 4;
  matrix.matrix[2][0] = 5;
  matrix.matrix[2][1] = -2;
  matrix.matrix[2][2] = -3;

  matrix_t expected = {0};
  s21_create_matrix(size, size, &expected);
  expected.matrix[0][0] = 1;
  expected.matrix[0][1] = -1;
  expected.matrix[0][2] = 1;
  expected.matrix[1][0] = -38;
  expected.matrix[1][1] = 41;
  expected.matrix[1][2] = -34;
  expected.matrix[2][0] = 27;
  expected.matrix[2][1] = -29;
  expected.matrix[2][2] = 24;

  matrix_t res = {0};
  matrix.columns++;
  int code = s21_inverse_matrix(&matrix, &res);

  ck_assert_int_eq(code, CALC_ERROR);

  s21_remove_matrix(&matrix);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(inverse_matrix_3) {
  const int size = 3;

  matrix_t matrix = {0};
  s21_create_matrix(size, size, &matrix);
  matrix.matrix[0][0] = 2;
  matrix.matrix[0][1] = 5;
  matrix.matrix[0][2] = 7;
  matrix.matrix[1][0] = 6;
  matrix.matrix[1][1] = 3;
  matrix.matrix[1][2] = 4;
  matrix.matrix[2][0] = 5;
  matrix.matrix[2][1] = -2;
  matrix.matrix[2][2] = -3;

  matrix_t expected = {0};
  s21_create_matrix(size, size, &expected);
  expected.matrix[0][0] = 1;
  expected.matrix[0][1] = -1;
  expected.matrix[0][2] = 1;
  expected.matrix[1][0] = -38;
  expected.matrix[1][1] = 41;
  expected.matrix[1][2] = -34;
  expected.matrix[2][0] = 27;
  expected.matrix[2][1] = -29;
  expected.matrix[2][2] = 24;

  matrix_t res = {0};
  matrix.columns = 0;
  int code = s21_inverse_matrix(&matrix, &res);
  matrix.columns = size;

  ck_assert_int_eq(code, MATRIX_ERROR);

  s21_remove_matrix(&matrix);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(inverse_matrix_4) {
  matrix_t A, B, R;
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &B);

  A.matrix[0][0] = 1.25;
  B.matrix[0][0] = 0.8;

  s21_inverse_matrix(&A, &R);
  ck_assert_int_eq(s21_eq_matrix(&R, &B), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&R);
}
END_TEST

START_TEST(inverse_matrix_5) {
  matrix_t A, B, R;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);

  A.matrix[0][0] = -1;
  A.matrix[0][1] = -10;
  A.matrix[0][2] = 1;
  A.matrix[1][0] = 1;
  A.matrix[1][1] = 10;
  A.matrix[1][2] = 1;
  A.matrix[2][0] = 1;
  A.matrix[2][1] = 1;
  A.matrix[2][2] = 1;

  s21_inverse_matrix(&A, &R);

  B.matrix[0][0] = -0.5;
  B.matrix[0][1] = -11.0 / 18.0;
  B.matrix[0][2] = 10.0 / 9.0;
  B.matrix[1][0] = 0;
  B.matrix[1][1] = 1.0 / 9.0;
  B.matrix[1][2] = -1.0 / 9.0;
  B.matrix[2][0] = 0.5;
  B.matrix[2][1] = 0.5;
  B.matrix[2][2] = 0;

  ck_assert_int_eq(s21_eq_matrix(&R, &B), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&R);
}
END_TEST

Suite *s21_matrix_tests_create() {
  Suite *s21_matrix = suite_create("s21_matrix");
  TCase *s21_matrix_tests = tcase_create("S21_MATRIX");

  tcase_add_test(s21_matrix_tests, create_matrix_1);
  tcase_add_test(s21_matrix_tests, create_matrix_2);
  tcase_add_test(s21_matrix_tests, create_matrix_3);
  tcase_add_test(s21_matrix_tests, create_matrix_4);

  tcase_add_test(s21_matrix_tests, remove_matrix_1);
  tcase_add_test(s21_matrix_tests, remove_matrix_2);
  tcase_add_test(s21_matrix_tests, remove_matrix_3);
  tcase_add_test(s21_matrix_tests, remove_matrix_4);

  tcase_add_test(s21_matrix_tests, eq_matrix_1);
  tcase_add_test(s21_matrix_tests, eq_matrix_2);
  tcase_add_test(s21_matrix_tests, eq_matrix_3);
  tcase_add_test(s21_matrix_tests, eq_matrix_4);
  tcase_add_test(s21_matrix_tests, eq_matrix_5);
  tcase_add_test(s21_matrix_tests, eq_matrix_6);
  tcase_add_test(s21_matrix_tests, eq_matrix_7);
  tcase_add_test(s21_matrix_tests, eq_matrix_8);
  tcase_add_test(s21_matrix_tests, eq_matrix_9);

  tcase_add_test(s21_matrix_tests, sum_matrix_1);
  tcase_add_test(s21_matrix_tests, sum_matrix_2);
  tcase_add_test(s21_matrix_tests, sum_matrix_3);
  tcase_add_test(s21_matrix_tests, sum_matrix_4);
  tcase_add_test(s21_matrix_tests, sum_matrix_5);
  tcase_add_test(s21_matrix_tests, sum_matrix_6);
  tcase_add_test(s21_matrix_tests, sum_matrix_7);

  tcase_add_test(s21_matrix_tests, sub_matrix_1);
  tcase_add_test(s21_matrix_tests, sub_matrix_2);
  tcase_add_test(s21_matrix_tests, sub_matrix_3);
  tcase_add_test(s21_matrix_tests, sub_matrix_4);
  tcase_add_test(s21_matrix_tests, sub_matrix_5);
  tcase_add_test(s21_matrix_tests, sub_matrix_6);
  tcase_add_test(s21_matrix_tests, sub_matrix_7);

  tcase_add_test(s21_matrix_tests, mult_number_1);
  tcase_add_test(s21_matrix_tests, mult_number_2);

  tcase_add_test(s21_matrix_tests, mult_matrix_1);
  tcase_add_test(s21_matrix_tests, mult_matrix_2);
  tcase_add_test(s21_matrix_tests, mult_matrix_3);

  tcase_add_test(s21_matrix_tests, transpose_1);
  tcase_add_test(s21_matrix_tests, transpose_2);

  tcase_add_test(s21_matrix_tests, calc_complements_1);
  tcase_add_test(s21_matrix_tests, calc_complements_2);
  tcase_add_test(s21_matrix_tests, calc_complements_3);
  tcase_add_test(s21_matrix_tests, calc_complements_4);
  tcase_add_test(s21_matrix_tests, calc_complements_5);
  tcase_add_test(s21_matrix_tests, calc_complements_6);
  tcase_add_test(s21_matrix_tests, calc_complements_7);
  tcase_add_test(s21_matrix_tests, calc_complements_8);

  tcase_add_test(s21_matrix_tests, determinant_1);
  tcase_add_test(s21_matrix_tests, determinant_2);
  tcase_add_test(s21_matrix_tests, determinant_3);
  tcase_add_test(s21_matrix_tests, determinant_4);
  tcase_add_test(s21_matrix_tests, determinant_5);
  tcase_add_test(s21_matrix_tests, determinant_6);
  tcase_add_test(s21_matrix_tests, determinant_7);

  tcase_add_test(s21_matrix_tests, inverse_matrix_1);
  tcase_add_test(s21_matrix_tests, inverse_matrix_2);
  tcase_add_test(s21_matrix_tests, inverse_matrix_3);
  tcase_add_test(s21_matrix_tests, inverse_matrix_4);
  tcase_add_test(s21_matrix_tests, inverse_matrix_5);

  suite_add_tcase(s21_matrix, s21_matrix_tests);
  return s21_matrix;
}

int main() {
  srand(time(NULL));

  Suite *s21_matrix = s21_matrix_tests_create();
  SRunner *s21_matrix_runner = srunner_create(s21_matrix);
  int number_failed;
  srunner_run_all(s21_matrix_runner, CK_NORMAL);
  number_failed = srunner_ntests_failed(s21_matrix_runner);
  srunner_free(s21_matrix_runner);

  return number_failed == 0 ? 0 : 1;
}
