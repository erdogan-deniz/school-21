# include "../s21_matrix_tests.h"

START_TEST(check_mults) {
    const int rows = rand() % 25 + 1;
    const int columns = rand() % 25 + 1;
    double mult_number = get_rand(-10e2, 10e2);
    matrix_t matrix1 = {0};
    matrix_t result = {0};
    matrix_t check = {0};
        
    s21_create_matrix(rows, columns, &matrix1);
    s21_create_matrix(rows, columns, &result);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            matrix1.matrix[i][j] = get_rand(-10000, 10000);
            result.matrix[i][j] = matrix1.matrix[i][j] * mult_number;
        }
    }
    
    ck_assert_int_eq(s21_mult_number(&matrix1, mult_number, &check), OK);
    ck_assert_int_eq(s21_eq_matrix(&check, &result), SUCCESS);
    s21_remove_matrix(&matrix1);
    s21_remove_matrix(&result);
    s21_remove_matrix(&check);
}
END_TEST

START_TEST(incorrect_matrix) {
    double mult_number = get_rand(-10e5, 10e5);
    matrix_t matrix = {0};
    matrix_t result = {0};

    matrix.rows = 0;
    matrix.columns = -2;
    
    ck_assert_int_eq(s21_mult_number(&matrix, mult_number, &result), INCORRECT_MATRIX);
}
END_TEST

START_TEST(none_empty_result) {
    double mult_number = get_rand(-10e5, 10e5);
    matrix_t matrix = {0};
    matrix_t result = {0};

    result.rows = 5;
    result.columns = 5;
    
    ck_assert_int_eq(s21_mult_number(&matrix, mult_number, &result), INCORRECT_MATRIX);
}
END_TEST

Suite *suite_s21_mult_number(void) {
    Suite *suite = suite_create("suite_s21_mult_number");
    TCase *tcase = tcase_create("s21_mult_number");

    tcase_add_loop_test(tcase, check_mults, 0, 25);

    tcase_add_test(tcase, incorrect_matrix);
    tcase_add_test(tcase, none_empty_result);
    
    suite_add_tcase(suite, tcase);
    
    return suite;
}