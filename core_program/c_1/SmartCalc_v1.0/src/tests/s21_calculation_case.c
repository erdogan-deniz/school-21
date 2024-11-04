#include "s21_tests.h"

START_TEST(test_1) {
  long double result_originl = -cos(1) + 3;
  long double result = s21_calculator("-cos(1)+3", NULL);

  ck_assert_double_eq(result_originl, result);
}
END_TEST

START_TEST(test_2) {
  long double result_originl = -0.1 + 0.2;
  long double result = s21_calculator("-0.1+0.2", NULL);

  ck_assert_double_eq((int)isnan(result_originl), (int)(result));
}
END_TEST

START_TEST(test_3) {
  long double result_originl = pow(2, 2.1 + 1) - 11 % 2;
  long double result = s21_calculator("2^(2.1+1)-11mod2", NULL);

  ck_assert_double_eq(result_originl, result);
}
END_TEST

START_TEST(test_4) {
  long double result_originl =
      sin(0.5) - cos(1) + tan(0.5) + acos(0.5) - asin(1) - atan(1);
  long double result = s21_calculator(
      "sin(0.5)-cos(1)+tan(0.5)+acos(0.5)-asin(1)-atan(1)", NULL);

  ck_assert_double_eq(result_originl, result);
}
END_TEST

START_TEST(test_5) {
  long double result_originl = sqrt(4.123456789) + 3 - 1.12;
  long double result = s21_calculator("sqrt(4.123456789)+3-1.12", NULL);

  ck_assert_float_eq(result_originl, result);
}
END_TEST

START_TEST(test_6) {
  long double result_originl = log(+10.2) - log10(10.2);
  long double result = s21_calculator("log(+10.2)-ln(10.2)", NULL);

  ck_assert_double_eq(result_originl, result);
}
END_TEST

START_TEST(test_7) {
  long double result_originl = 11 + pow((-2), 5);
  long double result = s21_calculator("11+(-2)^5", NULL);

  ck_assert_double_eq(result_originl, result);
}
END_TEST

START_TEST(test_8) {
  long double result_originl = log(+10.2) + log10(10.2);
  long double result = s21_calculator("log(+10.2)+ln(10.2)", NULL);

  ck_assert_double_eq(result_originl, result);
}
END_TEST

START_TEST(test_9) {
  long double result_originl = sqrt(+4 + 1) + (-3 + 1);
  long double result = s21_calculator("sqrt(+4+1)+(-3+1)", NULL);

  ck_assert_double_eq(result_originl, result);
}
END_TEST

START_TEST(test_10) {
  long double result_originl = sqrt(3 + 1) - (-3 + 1);
  long double result = s21_calculator("sqrt(3+1)-(-3+1)", NULL);

  ck_assert_double_eq(result_originl, result);
}
END_TEST

START_TEST(test_11) {
  long double x = 1.1;
  long double result_originl = sin(x);
  long double result = s21_calculator("sin(x)", &x);

  ck_assert_double_eq(result_originl, result);
}
END_TEST

START_TEST(test_12) {
  long double result = s21_calculator("sqrt(-5.032)", NULL);
  int answer = isnan(result) ? 1 : 0;

  ck_assert_int_eq(answer, 1);
}
END_TEST

START_TEST(test_13) {
  long double result_originl = (+5 * sqrt(4) - (-5 + 6)) / 3;
  long double result = s21_calculator("(+5*sqrt(4)-(-5+6))/3", NULL);

  ck_assert_double_eq(result_originl, result);
}
END_TEST

START_TEST(test_14) {
  long double result_originl = 5 + 5;
  long double result = s21_calculator("5 + 5", NULL);

  ck_assert_double_eq(result_originl, result);
}
END_TEST

START_TEST(test_15) {
  long double result_originl = -2 * 2 / 2;
  long double result = s21_calculator("-2*2/2", NULL);

  ck_assert_double_eq(result_originl, result);
}
END_TEST

START_TEST(test_16) {
  long double result_originl = 4 * 5 * 2 * 2 * 2 + 2;
  long double result = s21_calculator("   4 * 5 * 2 * 2 * 2 + 2", NULL);

  ck_assert_double_eq(result_originl, result);
}
END_TEST

START_TEST(test_17) {
  long double result_originl = 150 / 10 + 5 * 2 / 2;
  long double result = s21_calculator("150 / 10 + 5 * 2 / 2", NULL);

  ck_assert_double_eq(result_originl, result);
}
END_TEST

START_TEST(test_19) {
  long double result_originl = 123 + 0.456;
  long double result = s21_calculator("123+0.456", NULL);

  ck_assert_double_eq(result_originl, result);
}
END_TEST

START_TEST(test_20) {
  long double result = s21_calculator(".+m", NULL);
  int answer = isnan(result) ? 1 : 0;

  ck_assert_int_eq(answer, 1);
}
END_TEST

START_TEST(test_21) {
  long double x = -2;
  long double result = s21_calculator("log(x)", &x);
  int answer = isnan(result) ? 1 : 0;

  ck_assert_int_eq(answer, 1);
}
END_TEST

START_TEST(test_22) {
  long double result_originl = -(-1);
  long double result = s21_calculator("-(-1)", NULL);

  ck_assert_double_eq(result_originl, result);
}
END_TEST

START_TEST(test_23) {
  long double result_originl = cos(10 % 2);
  long double result = s21_calculator("cos(10mod2)", NULL);

  ck_assert_double_eq(result_originl, result);
}
END_TEST

START_TEST(test_24) {
  long double result_originl = sqrt(log10(10));
  long double result = s21_calculator("sqrt(ln(10))", NULL);

  ck_assert_double_eq(result_originl, result);
}
END_TEST

START_TEST(test_25) {
  long double result_originl = atan(10) + sin(10);
  long double result = s21_calculator("atan(10)+sin(10)", NULL);

  ck_assert_double_eq(result_originl, result);
}
END_TEST

START_TEST(test_26) {
  long double result_originl = asin(1);
  long double result = s21_calculator("asin(1)", NULL);

  ck_assert_double_eq(result_originl, result);
}
END_TEST

START_TEST(test_27) {
  long double result_originl = 10 - 20 * (-10);
  long double result = s21_calculator("10-20*(-10)", NULL);

  ck_assert_double_eq(result_originl, result);
}
END_TEST

START_TEST(test_28) {
  long double result = s21_calculator("-(o(i(a(10.01)*n(2))/10m2))^q(5)", NULL);
  int answer = isnan(result) ? 1 : 0;

  ck_assert_int_eq(answer, 1);
}
END_TEST

START_TEST(test_29) {
  long double result = s21_calculator("mod+9(()))", NULL);
  int answer = isnan(result) ? 1 : 0;

  ck_assert_int_eq(answer, 1);
}
END_TEST

START_TEST(test_30) {
  long double result = s21_calculator("md(+9(()))", NULL);
  int answer = isnan(result) ? 1 : 0;

  ck_assert_int_eq(answer, 1);
}
END_TEST

START_TEST(test_31) {
  long double x = 0.0;
  long double result_originl = 4 % 8;
  long double result = s21_calculator("4mod8", &x);

  ck_assert_double_eq(result_originl, result);
}
END_TEST

START_TEST(test_32) {
  long double x = 0.0;
  long double result_originl = sqrt(1);
  long double result = s21_calculator("sqrt(1)", &x);

  ck_assert_double_eq(result_originl, result);
}
END_TEST

START_TEST(test_33) {
  long double result_originl = 2 + (5 * 5 * 5 + 5 + 2 * 2) / (2);
  long double result = s21_calculator("2+(5 * 5 * 5 + 5 + 2 * 2) / (2)", NULL);

  ck_assert_double_eq(result_originl, result);
}
END_TEST

START_TEST(test_34) {
  long double result_originl = 5 + (3 + sin(8 / 2 - 3.5)) * 2;
  long double result = s21_calculator("5 + (3 + sin(8/2 - 3.5)) *2", NULL);

  ck_assert_double_eq(result_originl, result);
}
END_TEST

START_TEST(test_35) {
  long double result_originl = 24 * 4 - 3 * 2;
  long double result = s21_calculator("24*4 -3 * 2", NULL);

  ck_assert_double_eq(result_originl, result);
}
END_TEST

START_TEST(test_36) {
  long double x = 0;
  long double result_originl = -sin(9);
  long double result = s21_calculator("-sin(9)", &x);

  ck_assert_double_eq(result_originl, result);
}
END_TEST

START_TEST(test_37) {
  long double x = 0;
  long double result_originl = sin(9) - (-2);
  long double result = s21_calculator("sin(9)-(-2)", &x);

  ck_assert_double_eq(result_originl, result);
}
END_TEST

START_TEST(test_38) {
  long double result_originl = log(1);
  long double result = s21_calculator("log(1)", NULL);

  ck_assert_double_eq(result_originl, result);
}
END_TEST

Suite *suite_s21_calculation(void) {
  Suite *suite = suite_create("suite_s21_calculation");
  TCase *tcase = tcase_create("s21_calculation");

  tcase_add_test(tcase, test_1);
  tcase_add_test(tcase, test_2);
  tcase_add_test(tcase, test_3);
  tcase_add_test(tcase, test_4);
  tcase_add_test(tcase, test_5);
  tcase_add_test(tcase, test_6);
  tcase_add_test(tcase, test_7);
  tcase_add_test(tcase, test_8);
  tcase_add_test(tcase, test_9);
  tcase_add_test(tcase, test_10);
  tcase_add_test(tcase, test_11);
  tcase_add_test(tcase, test_12);
  tcase_add_test(tcase, test_13);
  tcase_add_test(tcase, test_14);
  tcase_add_test(tcase, test_15);
  tcase_add_test(tcase, test_16);
  tcase_add_test(tcase, test_17);
  tcase_add_test(tcase, test_19);
  tcase_add_test(tcase, test_20);
  tcase_add_test(tcase, test_21);
  tcase_add_test(tcase, test_22);
  tcase_add_test(tcase, test_23);
  tcase_add_test(tcase, test_24);
  tcase_add_test(tcase, test_25);
  tcase_add_test(tcase, test_26);
  tcase_add_test(tcase, test_27);
  tcase_add_test(tcase, test_28);
  tcase_add_test(tcase, test_29);
  tcase_add_test(tcase, test_30);
  tcase_add_test(tcase, test_31);
  tcase_add_test(tcase, test_32);
  tcase_add_test(tcase, test_33);
  tcase_add_test(tcase, test_34);
  tcase_add_test(tcase, test_35);
  tcase_add_test(tcase, test_36);
  tcase_add_test(tcase, test_37);
  tcase_add_test(tcase, test_38);

  suite_add_tcase(suite, tcase);

  return suite;
}