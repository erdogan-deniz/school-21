#include "s21_matrix.h"

int s21_determinant(matrix_t *A, double *result) {
  int exit_code = OK;
  int size = A->rows;

  if (s21_is_matrix_exists(A)) {
    if (A->rows == A->columns && result) {
      if (A->columns == 1) {
        *result = A->matrix[0][0];
      } else {
        *result = s21_found_determinant(*A, size);
      }
    } else {
      exit_code = CALC_ERROR;
    }
  } else {
    exit_code = MATRIX_ERROR;
  }

  return exit_code;
}

double s21_found_determinant(matrix_t A, int size) {
  double determinant = 0.0;

  if (size == 2) {
    determinant =
        (A.matrix[0][0] * A.matrix[1][1]) - (A.matrix[0][1] * A.matrix[1][0]);
  } else {
    for (int i = 0; i < size; i++) {
      for (int j = 0; j < size; j++) {
        matrix_t matrix_temp = {0};
        if (s21_create_matrix(size - 1, size - 1, &matrix_temp) == CALLOC_ERROR)
          return OK;

        s21_fill_determinate_matrix(A.matrix, matrix_temp.matrix, i, j, size);
        determinant += pow(-1, j) * A.matrix[0][j] *
                       s21_found_determinant(matrix_temp, size - 1);

        s21_remove_matrix(&matrix_temp);
      }
    }
  }

  return determinant;
}

void s21_fill_determinate_matrix(double **matrix_input, double **matrix_temp,
                                 int skip_row, int skip_column, int size) {
  int last_elem_in_column = size - 1;
  for (int row = 0, i = 0, j = 0; row < size; row++) {
    for (int column = 0; column < size; column++) {
      if (row == skip_row || column == skip_column) continue;

      matrix_temp[i][j++] = matrix_input[row][column];

      if (j == last_elem_in_column) {
        j = 0;
        i++;
      }
    }
  }
}