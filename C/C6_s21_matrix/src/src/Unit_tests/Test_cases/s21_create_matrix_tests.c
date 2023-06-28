# include "../s21_test.h"

START_TEST(minimum_matrix) {
    const int rows = 1;
    const int columns = 1;
    matrix_t matrix = {0};

    ck_assert_int_eq(s21_create_matrix(rows, columns, &matrix), 0);
    ck_assert_int_eq(matrix.rows, rows);
    ck_assert_int_eq(matrix.columns, columns);
    ck_assert_ptr_ne(matrix->matrix, NULL);

    s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(medium_matrix) {
    const int rows = 20;
    const int columns = 20;
    matrix_t matrix = {0};

    ck_assert_int_eq(s21_create_matrix(rows, columns, &matrix), 0);
    ck_assert_int_eq(matrix.rows, rows);
    ck_assert_int_eq(matrix.columns, columns);

    s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(no_rows) {
    const int rows = 0;
    const int columns = 5;
    matrix_t matrix = {0};

    ck_assert_int_eq(s21_create_matrix(rows, columns, &matrix), INCORRECT_MATRIX);
}
END_TEST

START_TEST(no_columns) {
    const int rows = 5;
    const int columns = 0;
    matrix_t matrix = {0};

    ck_assert_int_eq(s21_create_matrix(rows, columns, &matrix), INCORRECT_MATRIX);
}
END_TEST

START_TEST(no_rows_and_columns) {
    const int rows = 0;
    const int columns = 0;
    matrix_t matrix = {0};

    ck_assert_int_eq(s21_create_matrix(rows, columns, &matrix), INCORRECT_MATRIX);
}
END_TEST

START_TEST(negative_rows) {
    const int rows = -1;
    const int columns = 5;
    matrix_t matrix = {0};

    ck_assert_int_eq(s21_create_matrix(rows, columns, &matrix), INCORRECT_MATRIX);
}
END_TEST

START_TEST(negative_columns) {
    const int rows = 5;
    const int columns = -1;
    matrix_t matrix = {0};

    ck_assert_int_eq(s21_create_matrix(rows, columns, &matrix), INCORRECT_MATRIX);
}
END_TEST

START_TEST(negative_rows_and_columns) {
    const int rows = -1;
    const int columns = -1;
    matrix_t matrix = {0};

    ck_assert_int_eq(s21_create_matrix(rows, columns, &matrix), INCORRECT_MATRIX);
}
END_TEST

START_TEST(check_pointer) {
    const int rows = 5;
    const int columns = 5;
    matrix_t matrix = {0};

    matrix->matrix = (double**)malloc(1 * sizeof(double*));

    ck_assert_int_eq(s21_create_matrix(rows, columns, &matrix), CALCULATION_ERROR);
    
    free(matrix->matrix);
}
END_TEST

START_TEST(check_rows) {
    const int rows = 5;
    const int columns = 5;
    matrix_t matrix = {0};

    matrix->rows = 5;

    ck_assert_int_eq(s21_create_matrix(rows, columns, &matrix), CALCULATION_ERROR);
}
END_TEST

START_TEST(check_columns) {
    const int rows = 5;
    const int columns = 5;
    matrix_t matrix = {0};

    matrix->columns = 5;

    ck_assert_int_eq(s21_create_matrix(rows, columns, &matrix), CALCULATION_ERROR);
}
END_TEST

START_TEST(check_rows_and_columns) {
    const int rows = 5;
    const int columns = 5;
    matrix_t matrix = {0};
    
    matrix->rows = 5;
    matrix->columns = 5;

    ck_assert_int_eq(s21_create_matrix(rows, columns, &matrix), CALCULATION_ERROR);
}
END_TEST

START_TEST(check_matrix) {
    const int rows = 5;
    const int columns = 5;
    matrix_t matrix = {0};

    matrix->rows = 5;
    matrix->columns = 5;
    matrix->matrix = (double**)malloc(1 * sizeof(double*));

    ck_assert_int_eq(s21_create_matrix(rows, columns, &matrix), CALCULATION_ERROR);
    free(matrix->matrix);
}
END_TEST

Suite *suite_s21_create_matrix(void) {
    Suite *suite = suite_create("suite_s21_create_matrix");
    TCase *tcase = tcase_create("s21_create_matrix");

    tcase_add_test(tcase, minimum_matrix);
    tcase_add_test(tcase, medium_matrix);
    tcase_add_test(tcase, no_rows);
    tcase_add_test(tcase, no_columns);
    tcase_add_test(tcase, no_rows_and_columns);
    tcase_add_test(tcase, negative_rows);
    tcase_add_test(tcase, negative_columns);
    tcase_add_test(tcase, negative_rows_and_columns);
    tcase_add_test(tcase, check_pointer);
    tcase_add_test(tcase, check_rows);
    tcase_add_test(tcase, check_columns);
    tcase_add_test(tcase, check_rows_and_columns);
    tcase_add_test(tcase, check_matrix);

    suite_add_tcase(suite, tcase);
    
    return suite;
}