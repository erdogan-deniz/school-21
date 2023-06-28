#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
    
    int status = OK;

    if (!s21_is_empty(result)) {
        status = CALCULATION_ERROR;
    }
    else {
        if (rows < 1 || columns < 1) {
            status = INCORRECT_MATRIX;
        }
        else {
            result->rows = rows;
            result->columns = columns;
            result->matrix = (double**)malloc(rows * sizeof(double*));
        }

        if (result->matrix != NULL) {
            for (int i = 0; i < rows; ++i) {
                result->matrix[i] = (double*)calloc(columns, sizeof(double));

                if (!result->matrix[i]) {
                    for (int j = 0; j < i; ++j)
                        free(result->matrix[j]);
                
                    free(result->matrix);
                    result->rows = 0;
                    result->columns = 0;
                    break;
                }
            }
        }
    }

    return status;
}