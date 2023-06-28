#include "s21_matrix.h"

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {

    int status = OK;
    
    if (!s21_is_correct(A) || !s21_is_correct(B) || !s21_is_empty(result)) {
        status = INCORRECT_MATRIX;
    } 
    else {
        if (A->columns != B->rows)
            status = CALCULATION_ERROR;
    }
    
    if (!status) {
        s21_create_matrix(A->rows, B->columns, result);

        for (int i = 0; i < A->rows; ++i) {
            for (int j = 0; j < B->columns; ++j) {
                result->matrix[i][j] = 0;

                for (int k = 0; k < A->columns; ++k)
                    result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
            }
        }    
    }

    return status;
}