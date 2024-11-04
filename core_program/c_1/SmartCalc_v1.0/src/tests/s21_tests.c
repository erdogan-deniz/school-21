#include "s21_tests.h"

void run_tests(void) {
  Suite *list_cases[] = {suite_s21_input(), suite_s21_calculation(), NULL};

  for (Suite **current_test_case = list_cases; *current_test_case;
       ++current_test_case)

    run_test_case(*current_test_case);
}

void run_test_case(Suite *test_case) {
  static int tests_counter = 1;
  SRunner *runner = NULL;

  if (tests_counter > 0) putchar('\n');

  ++tests_counter;
  runner = srunner_create(test_case);
  srunner_set_fork_status(runner, CK_NOFORK);
  srunner_run_all(runner, CK_NORMAL);
  srunner_free(runner);
}

int main(void) {
  run_tests();

  return 0;
}