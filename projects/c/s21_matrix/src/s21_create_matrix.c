#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int exit_code = OK;

  if (rows > 0 && columns > 0 && result) {
    result->rows = rows;
    result->columns = columns;
    result->matrix = calloc(rows, sizeof(double));

    if (result->matrix) {
      for (int i = 0; i < rows; i++) {
        result->matrix[i] = calloc(columns, sizeof(double));
        if (!result->matrix[i]) exit_code = CALLOC_ERROR;
      }
    } else {
      exit_code = CALLOC_ERROR;
    }
  } else {
    exit_code = MATRIX_ERROR;
  }

  return exit_code;
}