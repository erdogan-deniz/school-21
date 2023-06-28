#include "s21_additional_functions.h"

int s21_downgrade(int n, int m, matrix_t *A, matrix_t *result) {
    
    int status = OK;

    if (!s21_is_correct(A) || !s21_is_empty(result)) {
        status = INCORRECT_MATRIX;
    }
    else {
        if(A->rows != A->columns)
             status = CALCULATION_ERROR;
    }

    if (!status) {
        s21_create_matrix(A->rows - 1, A->columns - 1, result);

        int di = 0, dj = 0;

        for (int i = 0; i < A->rows; ++i) {
            if (i == n) continue;

            di = (i > n)? 1: 0;
        
            for (int j = 0; j < A->columns; ++j) {
                if (j == m) continue;

                dj = j > m? 1: 0;            

                result[i - di][j - dj] = A[i][j];
            }
        }
    }
    
    return status;
}