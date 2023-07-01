#include "s21_matrix_tests.h"

void run_tests(void) {
    Suite *list_cases[] = {
        suite_s21_create_matrix(), 
        suite_s21_eq_matrix(), 
        suite_s21_sub_matrix(), 
        suite_s21_sum_matrix(), 
        suite_s21_mult_matrix(), 
        suite_s21_mult_number(),
        suite_s21_transpose(), 
        suite_s21_calc_complements(),
        suite_s21_determinant(), 
        suite_s21_inverse_matrix(),
        suite_s21_remove_matrix(), NULL
    };
  
    for (Suite **current_testcase = list_cases; *current_testcase != NULL; ++current_testcase) {
        run_testcase(*current_testcase);
    }
}

void run_testcase(Suite *testcase) {
    static int counter_testcase = 1;

    if (counter_testcase > 0)
        putchar('\n');
  
    ++counter_testcase;
    SRunner *sr = srunner_create(testcase);

    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_run_all(sr, CK_NORMAL);
    srunner_free(sr);
}

double get_rand(double min, double max) {
    double val = (double)rand() / RAND_MAX;
    return min + val * (max - min);
}

int main(void) {
    
    run_tests();
    return 0;
}