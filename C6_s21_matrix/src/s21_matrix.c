#define SUCCESS 1
#define FAILURE 0

// Необходимые библиотеки
# include "s21_matrix.h"

// Функции
int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);
int s21_eq_matrix(matrix_t *A, matrix_t *B);
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_transpose(matrix_t *A, matrix_t *result);
int s21_calc_complements(matrix_t *A, matrix_t *result);
int s21_determinant(matrix_t *A, double *result);
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

int s21_create_matrix(int rows, int columns, matrix_t *result) {
    
    int key = 0;

    if (result->rows != 0 || result->columns != 0) {
        key = 1;
    }
    else {
        if (rows == 0 && columns == 0) {
            key = 2;
        } else {
            result->rows = rows;
            result->columns = columns;
        }

        result->matrix = (double**)malloc(rows * sizeof(double*));
        for (int i = 0; i < columns; ++i) {
            result->matrix[i] = (double*)malloc(rows * sizeof(double));
        }
    }

    return key;
}

int main(void) {

matrix_t tmp = {0};
s21_create_matrix(4, 4, &tmp);

for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
        tmp.matrix[i][j] = 1;
}}

for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
        printf("[%d %d] = %lf", i, j, tmp.matrix[i][j]);
}
printf("\n");
}

return 0;
}