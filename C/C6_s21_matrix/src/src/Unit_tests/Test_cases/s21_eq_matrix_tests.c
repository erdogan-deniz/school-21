# include "../s21_test.h"

START_TEST(check_equal) {
    const int rows = rand() % 25 + 1;
    const int columns = rand() % 25 + 1;
    matrix_t matrix1 = {0};
    matrix_t matrix2 = {0};
    
    s21_create_matrix(rows, columns, &matrix1);
    s21_create_matrix(rows, columns, &matrix2);
    
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            double random_value = get_rand(DBL_MIN, DBL_MAX);
            matrix1.matrix[i][j] = random_value;
            matrix2.matrix[i][j] = random_value;
        }
    }

  ck_assert_int_eq(s21_eq_matrix(&matrix1, &matrix2), SUCCESS);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
}
END_TEST

START_TEST(check_none_equal) {
    const int rows = rand() % 25 + 1;
    const int columns = rand() % 25 + 1;
    matrix_t matrix1 = {0};
    matrix_t matrix2 = {0};
    
    s21_create_matrix(rows, columns, &matrix1);
    s21_create_matrix(rows, columns, &matrix2);
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            double random_value = get_rand(DBL_MIN, DBL_MAX);
            matrix1.matrix[i][j] = random_value;
            matrix2.matrix[i][j] = random_value + 1;
        }
    }

  ck_assert_int_eq(s21_eq_matrix(&matrix1, &matrix2), FAILURE);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
}
END_TEST

START_TEST(equal_minimum_matrix) {
    const int rows = 1;
    const int columns = 1;
    matrix_t matrix1 = {0};
    matrix_t matrix2 = {0};

    s21_create_matrix(rows, columns, &matrix1);
    s21_create_matrix(rows, columns, *matrix2);
    
    double random_value = get_rand(DBL_MIN, DBL_MAX);
    matrix1.matrix[0][0] = random_value;
    matrix2.matrix[0][0] = random_value;

    ck_assert_int_eq(s21_eq_matrix(&matrix1, &matrix2), SUCCESS);
    s21_remove_matrix(&matrix1);
    s21_remove_matrix(&matrix2);
}
END_TEST

START_TEST(equal_medium_matrix) {
    const int rows = 20;
    const int columns = 20;
    matrix_t matrix1 = {0};
    matrix_t matrix2 = {0};

    s21_create_matrix(rows, columns, &matrix1);
    s21_create_matrix(rows, columns, *matrix2);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            double random_value = get_rand(DBL_MIN, DBL_MAX);
            matrix1.matrix[i][j] = random_value;
            matrix2.matrix[i][j] = random_value;
        }
    }

    ck_assert_int_eq(s21_eq_matrix(&matrix1, &matrix2), SUCCESS);
    s21_remove_matrix(&matrix1);
    s21_remove_matrix(&matrix2);
}
END_TEST

START_TEST(none_equal_minimum_matrix) {
    const int rows = 1;
    const int columns = 1;
    matrix_t matrix1 = {0};
    matrix_t matrix2 = {0};

    s21_create_matrix(rows, columns, &matrix1);
    s21_create_matrix(rows, columns, *matrix2);

    double random_value = get_rand(DBL_MIN, DBL_MAX);
    matrix1.matrix[0][0] = random_value;
    matrix2.matrix[0][0] = random_value + 1;

    ck_assert_int_eq(s21_eq_matrix(&matrix1, &matrix2), FAILURE);
    s21_remove_matrix(&matrix1);
    s21_remove_matrix(&matrix2);
}
END_TEST

START_TEST(none_equal_medium_matrix) {
    const int rows = 20;
    const int columns = 20;
    matrix_t matrix1 = {0};
    matrix_t matrix2 = {0};

    s21_create_matrix(rows, columns, &matrix1);
    s21_create_matrix(rows, columns, *matrix2);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            double random_value = get_rand(DBL_MIN, DBL_MAX);

            matrix1.matrix[i][j] = random_value;
            matrix2.matrix[i][j] = random_value  + 1;
        }
    }

    ck_assert_int_eq(s21_eq_matrix(&matrix1, &matrix2), FAILURE);
    s21_remove_matrix(&matrix1);
    s21_remove_matrix(&matrix2);
}
END_TEST

START_TEST(none_equal_rows_first) {
    const int rows = 10;
    const int columns = 10;
    matrix_t matrix1 = {0};
    matrix_t matrix2 = {0};

    s21_create_matrix(rows * 2, columns, &matrix1);
    s21_create_matrix(rows, columns, *matrix2);
    ck_assert_int_eq(s21_eq_matrix(&matrix1, &matrix2), FAILURE);
    s21_remove_matrix(&matrix1);
    s21_remove_matrix(&matrix2);
}
END_TEST

START_TEST(none_equal_rows_second) {
    const int rows = 10;
    const int columns = 10;
    matrix_t matrix1 = {0};
    matrix_t matrix2 = {0};

    s21_create_matrix(rows, columns, &matrix1);
    s21_create_matrix(rows * 2, columns, *matrix2);
    ck_assert_int_eq(s21_eq_matrix(&matrix1, &matrix2), FAILURE);
    s21_remove_matrix(&matrix1);
    s21_remove_matrix(&matrix2);
}
END_TEST

START_TEST(none_equal_columns_first) {
    const int rows = 10;
    const int columns = 10;
    matrix_t matrix1 = {0};
    matrix_t matrix2 = {0};

    s21_create_matrix(rows, columns * 2, &matrix1);
    s21_create_matrix(rows, columns, *matrix2);
    ck_assert_int_eq(s21_eq_matrix(&matrix1, &matrix2), FAILURE);
    s21_remove_matrix(&matrix1);
    s21_remove_matrix(&matrix2);
}
END_TEST

START_TEST(none_equal_columns_second) {
    const int rows = 10;
    const int columns = 10;
    matrix_t matrix1 = {0};
    matrix_t matrix2 = {0};

    s21_create_matrix(rows, columns, &matrix1);
    s21_create_matrix(rows, columns * 2, *matrix2);
    ck_assert_int_eq(s21_eq_matrix(&matrix1, &matrix2), FAILURE);
    s21_remove_matrix(&matrix1);
    s21_remove_matrix(&matrix2);
}
END_TEST

START_TEST(none_equal_rows_and_columns) {
    const int rows = 10;
    const int columns = 10;
    matrix_t matrix1 = {0};
    matrix_t matrix2 = {0};

    s21_create_matrix(rows, columns, &matrix1);
    s21_create_matrix(rows * 2, columns * 2, *matrix2);
    ck_assert_int_eq(s21_eq_matrix(&matrix1, &matrix2), FAILURE);
    s21_remove_matrix(&matrix1);
    s21_remove_matrix(&matrix2);
}
END_TEST

START_TEST(incorrect_matrix_one) {
    const int rows = 10;
    const int columns = 10;
    matrix_t matrix1 = {0};
    matrix_t matrix2 = {0};

    matrix1->rows = rows;
    matrix1->columns = columns;

    s21_create_matrix(rows, columns, *matrix2);
    ck_assert_int_eq(s21_eq_matrix(&matrix1, &matrix2), FAILURE);
    s21_remove_matrix(&matrix1);
    s21_remove_matrix(&matrix2);
}
END_TEST

START_TEST(incorrect_matrix_two) {
    const int rows = 10;
    const int columns = 10;
    matrix_t matrix1 = {0};
    matrix_t matrix2 = {0};

    matrix2->rows = rows;
    matrix2->columns = columns;

    s21_create_matrix(rows, columns, *matrix1);
    ck_assert_int_eq(s21_eq_matrix(&matrix1, &matrix2), FAILURE);
    s21_remove_matrix(&matrix1);
    s21_remove_matrix(&matrix2);
}
END_TEST

START_TEST(empty_matrix_one) {
    const int rows = 10;
    const int columns = 10;
    matrix_t matrix1 = {0};
    matrix_t matrix2 = {0};

    s21_create_matrix(rows, columns, *matrix2);
    ck_assert_int_eq(s21_eq_matrix(&matrix1, &matrix2), FAILURE);
    s21_remove_matrix(&matrix1);
    s21_remove_matrix(&matrix2);
}
END_TEST

START_TEST(empty_matrix_two) {
    const int rows = 10;
    const int columns = 10;
    matrix_t matrix1 = {0};
    matrix_t matrix2 = {0};

    s21_create_matrix(rows, columns, *matrix1);
    ck_assert_int_eq(s21_eq_matrix(&matrix1, &matrix2), FAILURE);
    s21_remove_matrix(&matrix1);
    s21_remove_matrix(&matrix2);
}
END_TEST

Suite *suite_s21_eq_matrix(void) {
    Suite *suite = suite_create("suite_s21_eq_matrix");
    TCase *tcase = tcase_create("s21_eq_matrix");

    tcase_add_loop_test(tcase, check_equal, 0, 25);
    tcase_add_loop_test(tcase, check_none_equal, 0, 25);
    
    tcase_add_test(tcase, equal_minimum_matrix);
    tcase_add_test(tcase, equal_medium_matrix);
    tcase_add_test(tcase, none_equal_minimum_matrix);
    tcase_add_test(tcase, none_equal_medium_matrix);
    tcase_add_test(tcase, none_equal_rows_first);
    tcase_add_test(tcase, none_equal_rows_second);
    tcase_add_test(tcase, none_equal_columns_first);
    tcase_add_test(tcase, none_equal_columns_second);
    tcase_add_test(tcase, none_equal_rows_and_columns);
    tcase_add_test(tcase, incorrect_matrix_one);
    tcase_add_test(tcase, incorrect_matrix_two);
    tcase_add_test(tcase, empty_matrix_one);
    tcase_add_test(tcase, empty_matrix_two);

    suite_add_tcase(suite, tcase);
    
    return suite;
}