#include "../s21_matrix.h"

int s21_downgrade(int n, int m, matrix_t *A, matrix_t *result) {

    int status = OK;

    if (!s21_is_correct(A))
        status = INCORRECT_MATRIX;

    if (!status)
        if(A->rows != A->columns)
             status = CALCULATION_ERROR;

    if (!status) {
        int di = 0;
        int dj = 0;

        for (int i = 0; i < A->rows; ++i) {
            if (i == n) continue;

            di = (i > n) ? 1 : 0;
        
            for (int j = 0; j < A->columns; ++j) {
                if (j == m) continue;

                dj = (j > m) ? 1 : 0;

                result->matrix[i - di][j - dj] = A->matrix[i][j];
            }
        }
    }
    
    return status;
}