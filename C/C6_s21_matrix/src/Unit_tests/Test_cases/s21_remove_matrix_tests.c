#include "../s21_matrix_tests.h"

START_TEST(minimum_matrix) {
    const int rows = 1;
    const int columns = 1;
    matrix_t matrix = {0};

    s21_create_matrix(rows, columns, &matrix);

    matrix.matrix[0][0] = 1;

    s21_remove_matrix(&matrix);
    ck_assert_ptr_eq(matrix.matrix, NULL);
    ck_assert_int_eq(matrix.rows, 0);
    ck_assert_int_eq(matrix.columns, 0);
}
END_TEST

START_TEST(medium_matrix) {
    const int rows = 20;
    const int columns = 20;
    matrix_t matrix = {0};

    s21_create_matrix(rows, columns, &matrix);
    
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < columns; ++j)
        matrix.matrix[i][j] = i + j;

    s21_remove_matrix(&matrix);
    ck_assert_ptr_eq(matrix.matrix, NULL);
    ck_assert_int_eq(matrix.rows, 0);
    ck_assert_int_eq(matrix.columns, 0);
}
END_TEST

START_TEST(empty_matrix) {
    matrix_t matrix = {0};

    s21_remove_matrix(&matrix);
    ck_assert_ptr_eq(matrix.matrix, NULL);
    ck_assert_int_eq(matrix.rows, 0);
    ck_assert_int_eq(matrix.columns, 0);
}
END_TEST

Suite *suite_s21_remove_matrix(void) {
    Suite *suite = suite_create("suite_s21_remove_matrix");
    TCase *tcase = tcase_create("s21_remove_matrix");

    tcase_add_test(tcase, minimum_matrix);
    tcase_add_test(tcase, medium_matrix);
    tcase_add_test(tcase, empty_matrix);

    suite_add_tcase(suite, tcase);
    
    return suite;
}