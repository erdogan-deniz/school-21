#include "../s21_matrix_tests.h"

START_TEST(check_sums) {
    const int rows = rand() % 20 + 1;
    const int columns = rand() % 20 + 1;
    matrix_t matrix1 = {0};
    matrix_t matrix2 = {0};
    matrix_t result = {0};
    matrix_t check = {0};

    s21_create_matrix(rows, columns, &matrix1);
    s21_create_matrix(rows, columns, &matrix2);
    s21_create_matrix(rows, columns, &result);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            matrix1.matrix[i][j] = get_rand(-10000, 10000);
            matrix2.matrix[i][j] = get_rand(-10000, 10000);
            result.matrix[i][j] = matrix1.matrix[i][j] +  matrix2.matrix[i][j];
        }
    }

    ck_assert_int_eq(s21_sum_matrix(&matrix1, &matrix2, &check), OK);
    ck_assert_int_eq(s21_eq_matrix(&result, &check), SUCCESS);
    s21_remove_matrix(&matrix1);
    s21_remove_matrix(&matrix2);
    s21_remove_matrix(&result);
    s21_remove_matrix(&check);
}
END_TEST

START_TEST(empty_matrix_one) {
    const int rows = rand() % 25 + 1;
    const int columns = rand() % 25 + 1;
    matrix_t matrix1 = {0};
    matrix_t matrix2 = {0};
    matrix_t result = {0};

    s21_create_matrix(rows, columns, &matrix2);
    ck_assert_int_eq(s21_sum_matrix(&matrix1, &matrix2, &result), INCORRECT_MATRIX);
    s21_remove_matrix(&matrix2);
}
END_TEST

START_TEST(empty_matrix_two) {
    const int rows = rand() % 25 + 1;
    const int columns = rand() % 25 + 1;
    matrix_t matrix1 = {0};
    matrix_t matrix2 = {0};
    matrix_t result = {0};

    s21_create_matrix(rows, columns, &matrix1);
    ck_assert_int_eq(s21_sum_matrix(&matrix1, &matrix2, &result), INCORRECT_MATRIX);
    s21_remove_matrix(&matrix1);
}
END_TEST

START_TEST(none_empty_result) {
    const int rows = rand() % 25 + 1;
    const int columns = rand() % 25 + 1;
    matrix_t matrix1 = {0};
    matrix_t matrix2 = {0};
    matrix_t result = {0};
    
    result.rows = 5;

    s21_create_matrix(rows, columns, &matrix1);
    s21_create_matrix(rows, columns, &matrix2);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            matrix1.matrix[i][j] = i + j;
            matrix2.matrix[i][j] = i + j;
        }
    }

    ck_assert_int_eq(s21_sum_matrix(&matrix1, &matrix2, &result), INCORRECT_MATRIX);
    s21_remove_matrix(&matrix1);
    s21_remove_matrix(&matrix2);
}
END_TEST

START_TEST(none_equal_rows) {
    const int rows = rand() % 25 + 1;
    const int columns = rand() % 25 + 1;
    matrix_t matrix1 = {0};
    matrix_t matrix2 = {0};
    matrix_t result = {0};

    s21_create_matrix(rows + 2, columns, &matrix1);
    s21_create_matrix(rows, columns, &matrix2);
    ck_assert_int_eq(s21_sum_matrix(&matrix1, &matrix2, &result), CALCULATION_ERROR);
    s21_remove_matrix(&matrix1);
    s21_remove_matrix(&matrix2);
}
END_TEST

START_TEST(none_equal_columns) {
    const int rows = rand() % 25 + 1;
    const int columns = rand() % 25 + 1;
    matrix_t matrix1 = {0};
    matrix_t matrix2 = {0};
    matrix_t result = {0};

    s21_create_matrix(rows, columns + 2, &matrix1);
    s21_create_matrix(rows, columns, &matrix2);
    ck_assert_int_eq(s21_sum_matrix(&matrix1, &matrix2, &result), CALCULATION_ERROR);
    s21_remove_matrix(&matrix1);
    s21_remove_matrix(&matrix2);
}
END_TEST

START_TEST(no_equal_rows_and_columns) {
    const int rows = rand() % 25 + 1;
    const int columns = rand() % 25 + 1;
    matrix_t matrix1 = {0};
    matrix_t matrix2 = {0};
    matrix_t result = {0};

    s21_create_matrix(rows, columns + 2, &matrix1);
    s21_create_matrix(rows + 1, columns, &matrix2);
    ck_assert_int_eq(s21_sum_matrix(&matrix1, &matrix2, &result), CALCULATION_ERROR);
    s21_remove_matrix(&matrix1);
    s21_remove_matrix(&matrix2);
}
END_TEST

Suite *suite_s21_sum_matrix(void) {
    Suite *suite = suite_create("suite_s21_sum_matrix");
    TCase *tcase = tcase_create("s21_sum_matrix");

    tcase_add_loop_test(tcase, check_sums, 0, 25);

    tcase_add_test(tcase, empty_matrix_one);
    tcase_add_test(tcase, empty_matrix_two);
    tcase_add_test(tcase, none_empty_result);
    tcase_add_test(tcase, none_equal_rows);
    tcase_add_test(tcase, none_equal_columns);
    tcase_add_test(tcase, no_equal_rows_and_columns);

    suite_add_tcase(suite, tcase);
    
    return suite;
}