#ifndef SRC_TESTS_S21_TESTS_H_
#define SRC_TESTS_S21_TESTS_H_

// Test result:
#define CORRECT 1
#define INCORRECT 0

// Libraries for tests:
#include <check.h>
#include <time.h>
#include <unistd.h>

// Main library:
#include "../s21_calculator.h"
#include "../validation/s21_validation.h"

// Function suites:
Suite *suite_s21_input(void);
Suite *suite_s21_calculation(void);

// Start tests functions:
void run_tests(void);  // Create cases list and run all cases one after one
void run_test_case(Suite *test_case);  // Create tests counter and run test case

#endif  // SRC_TESTS_S21_TESTS_H_