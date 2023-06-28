#include "s21_matrix.h"

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
    
    int eq_flag = SUCCESS;

    if (!s21_is_correct(A) || !s21_is_correct(B) || (A->rows != B->rows) || (A->columns != B->columns))
        eq_flag = FAILURE;

    if (eq_flag) {
        for (int i = 0; i < A->rows; ++i) {
            for (int j = 0; j < A->columns; ++j) {
                if (!s21_is_equal(A->matrix[i][j], B->matrix[i][j])) {
                    eq_flag = FAILURE;
                    break;
                }
            }

        if (!eq_flag) break;  
        }
    }

    return eq_flag;
}