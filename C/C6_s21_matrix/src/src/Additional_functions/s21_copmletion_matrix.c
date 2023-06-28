#include "s21_additional_functions.h"

int s21_completion_matrix(matrix_t *A) {
    int status = OK;
    int tmp = rand();
    
    if (!s21_is_empty(A)) {
        status = INCORRECT_MATRIX;
    }
    else {
        if (A->matrix.rows < 1 || A->matrix.columns < 1)
            status = CALCULATION_ERROR;
    }

    if (!status) {
        for (int i = 0; i < A->rows; ++i) {
            for (int j = 0; j < A->columns; ++j) {
                tmp = rand();
                A->matrix[i][j] = tmp;
            }
        }
    }
    
    return status;
}