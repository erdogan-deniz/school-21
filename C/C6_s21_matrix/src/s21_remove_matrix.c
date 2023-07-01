#include "s21_matrix.h"

void s21_remove_matrix(matrix_t *A) {
    
    if (A) {
        if (A->matrix) {
            for (int i = 0; i < A->rows; i++) 
                if (A->matrix[i]) {
                    free(A->matrix[i]);

                    A->matrix[i] = 0;
                }
        
            free(A->matrix);

            A->matrix = 0;
        }
        
        A->columns = 0;
        A->rows = 0;
    }
}