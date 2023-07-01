#include "s21_matrix.h"

int s21_transpose(matrix_t *A, matrix_t *result) {

    int status = OK;
    
    if (!s21_is_correct(A) || !s21_is_empty(result))
        status = INCORRECT_MATRIX;

    if (!status) {
        s21_create_matrix(A->columns, A->rows, result);

        for (int i = 0; i < A->rows; ++i)
            for (int j = 0; j < A->columns; ++j) 
                result->matrix[j][i] = A->matrix[i][j];
    }
    
    return status;
}