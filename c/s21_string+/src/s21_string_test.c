// Test runner: every suite of s21_string+ in one CK_NOFORK run.
#include "s21_string_test.h"

int main(void) {
  setlocale(LC_ALL, "");
  SRunner *sr = srunner_create(suite_part1());
  srunner_add_suite(sr, suite_str());
  srunner_add_suite(sr, suite_part5());
  srunner_add_suite(sr, suite_mem());
  srunner_add_suite(sr, suite_sprintf());
  srunner_add_suite(sr, suite_sprintf_hex());
  srunner_add_suite(sr, suite_sscanf_1());
  srunner_add_suite(sr, suite_sscanf_2());

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_VERBOSE);

  int nf = srunner_ntests_failed(sr);
  srunner_free(sr);
  return nf == 0 ? 0 : 1;
}
