#include "s21_matrix.h"

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int exit_code = OK;
  int size = A->rows;

  if (s21_is_matrix_exists(A)) {
    if (A->rows == A->columns && result) {
      exit_code = s21_create_matrix(size, size, result);

      if (!exit_code && size == 1) {
        result->matrix[0][0] = A->matrix[0][0];
      } else if (!exit_code) {
        matrix_t matrix_temp = {0};
        if (s21_create_matrix(size - 1, size - 1, &matrix_temp)) return OK;

        for (int i = 0; i < size; i++) {
          for (int j = 0; j < size; j++) {
            s21_fill_determinate_matrix(A->matrix, matrix_temp.matrix, i, j,
                                        size);
            double determinant = 0.0;
            s21_determinant(&matrix_temp, &determinant);
            result->matrix[i][j] = pow(-1, i + j) * determinant;
          }
        }

        s21_remove_matrix(&matrix_temp);
      }
    } else {
      exit_code = CALC_ERROR;
    }
  } else {
    exit_code = MATRIX_ERROR;
  }

  return exit_code;
}