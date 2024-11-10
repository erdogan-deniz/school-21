#include "s21_tests.h"

START_TEST(input_test_1) { ck_assert_int_eq(s21_validation("2+2*2"), CORRECT); }
END_TEST

START_TEST(input_test_2) { ck_assert_int_eq(s21_validation("2^2^3"), CORRECT); }
END_TEST

START_TEST(input_test_3) {
  ck_assert_int_eq(s21_validation("cos(4)*sin(3)"), CORRECT);
}
END_TEST

START_TEST(input_test_4) {
  ck_assert_int_eq(s21_validation("3.1415-21/42+12*tan(5)"), CORRECT);
}
END_TEST

START_TEST(input_test_5) {
  ck_assert_int_eq(s21_validation("Hello, world!"), INCORRECT);
}
END_TEST

START_TEST(input_test_6) {
  ck_assert_int_eq(s21_validation("3..15"), INCORRECT);
}
END_TEST

START_TEST(input_test_7) {
  ck_assert_int_eq(s21_validation("1--16"), INCORRECT);
}
END_TEST

START_TEST(input_test_8) {
  ck_assert_int_eq(s21_validation("atan(5)+ln(3)+mod(4)+sqrb()"), INCORRECT);
}
END_TEST

START_TEST(input_test_9) {
  ck_assert_int_eq(s21_validation("+x-(-21)"), CORRECT);
}
END_TEST

START_TEST(input_test_10) {
  ck_assert_int_eq(s21_validation("3.14+56((x)22)"), INCORRECT);
}
END_TEST

START_TEST(input_test_11) {
  ck_assert_int_eq(s21_validation("xxxxxxxxx(x)"), INCORRECT);
}
END_TEST

START_TEST(input_test_12) {
  ck_assert_int_eq(s21_validation("log(log(log(sin(3))))"), CORRECT);
}
END_TEST

START_TEST(input_test_13) {
  ck_assert_int_eq(s21_validation("+3247862-(-1)"), CORRECT);
}
END_TEST

START_TEST(input_test_14) {
  ck_assert_int_eq(s21_validation("12/03/1997"), CORRECT);
}
END_TEST

START_TEST(input_test_15) {
  ck_assert_int_eq(s21_validation("log(x)"), CORRECT);
}
END_TEST

START_TEST(input_test_16) {
  ck_assert_int_eq(s21_validation(".123123123+12398172387126387123613412"),
                   INCORRECT);
}
END_TEST

START_TEST(input_test_17) {
  ck_assert_int_eq(s21_validation("^3^2^10*(24124-16)cos(5)/0log(x)"),
                   INCORRECT);
}
END_TEST

START_TEST(input_test_18) {
  ck_assert_int_eq(s21_validation("1+2+3-log(6)*sqrt(10)+ln(10)"), CORRECT);
}
END_TEST

START_TEST(input_test_19) {
  ck_assert_int_eq(s21_validation("1.123123+2mod4+(3*7)+sqrt(7)"), CORRECT);
}
END_TEST

START_TEST(input_test_20) {
  ck_assert_int_eq(s21_validation("1+2mod4+3*(7+1)+acos(1/2)+5^2"), CORRECT);
}
END_TEST

START_TEST(input_test_21) {
  ck_assert_int_eq(s21_validation("1+2mod4+3*(7+1)+asin(1/2)"), CORRECT);
}
END_TEST

START_TEST(input_test_22) {
  ck_assert_int_eq(s21_validation("^1+2mod4+3*(7+1)+atan(1/2)"), INCORRECT);
}
END_TEST

START_TEST(input_test_23) {
  ck_assert_int_eq(s21_validation("cos(1/2)+2mod4+3*(7+1)+sin(0)"), CORRECT);
}
END_TEST

START_TEST(input_test_24) {
  ck_assert_int_eq(s21_validation("tan(1/2)+2mod4+3*(7+1)+asin(0)+atan(0)"),
                   CORRECT);
}
END_TEST

START_TEST(input_test_25) {
  ck_assert_int_eq(s21_validation("123456789+"), INCORRECT);
}
END_TEST

START_TEST(input_test_26) {
  ck_assert_int_eq(
      s21_validation("1/2+aco(3)-lo(6)+l(8)-asi(5)+at(3)+tcos(213)^"),
      INCORRECT);
}
END_TEST

START_TEST(input_test_27) { ck_assert_int_eq(s21_validation(" "), INCORRECT); }
END_TEST

START_TEST(input_test_28) {
  ck_assert_int_eq(s21_validation("!1+4-f+d/"), INCORRECT);
}
END_TEST

START_TEST(input_test_29) {
  ck_assert_int_eq(s21_validation("1+4/"), INCORRECT);
}
END_TEST

START_TEST(input_test_30) {
  ck_assert_int_eq(s21_validation("1+4*"), INCORRECT);
}
END_TEST

START_TEST(input_test_31) {
  ck_assert_int_eq(s21_validation("1+5-4*"), INCORRECT);
}
END_TEST

START_TEST(input_test_32) {
  ck_assert_int_eq(s21_validation("1+((5-4)/410"), INCORRECT);
}
END_TEST

START_TEST(input_test_33) {
  ck_assert_int_eq(s21_validation("4mid2+(5-4)"), INCORRECT);
}
END_TEST

START_TEST(input_test_34) { ck_assert_int_eq(s21_validation("1+"), INCORRECT); }
END_TEST

START_TEST(input_test_35) {
  ck_assert_int_eq(s21_validation("2^(2.1+)-+11mod2"), INCORRECT);
}
END_TEST

START_TEST(input_test_36) {
  ck_assert_int_eq(s21_validation("2^(2.1+1)-11mid2"), INCORRECT);
}
END_TEST

START_TEST(input_test_37) { ck_assert_int_eq(s21_validation("+"), INCORRECT); }
END_TEST

START_TEST(input_test_38) { ck_assert_int_eq(s21_validation("*"), INCORRECT); }
END_TEST

START_TEST(input_test_39) { ck_assert_int_eq(s21_validation("^"), INCORRECT); }
END_TEST

START_TEST(input_test_40) { ck_assert_int_eq(s21_validation("/"), INCORRECT); }
END_TEST

START_TEST(input_test_41) { ck_assert_int_eq(s21_validation("-"), INCORRECT); }
END_TEST

START_TEST(input_test_42) {
  ck_assert_int_eq(s21_validation("mod"), INCORRECT);
}
END_TEST

START_TEST(input_test_43) {
  ck_assert_int_eq(s21_validation("cos"), INCORRECT);
}
END_TEST

START_TEST(input_test_44) {
  ck_assert_int_eq(s21_validation("sin"), INCORRECT);
}
END_TEST

START_TEST(input_test_45) {
  ck_assert_int_eq(s21_validation("tan"), INCORRECT);
}
END_TEST

START_TEST(input_test_46) {
  ck_assert_int_eq(s21_validation("acos"), INCORRECT);
}
END_TEST

START_TEST(input_test_47) {
  ck_assert_int_eq(s21_validation("asin"), INCORRECT);
}
END_TEST

START_TEST(input_test_48) {
  ck_assert_int_eq(s21_validation("atan"), INCORRECT);
}
END_TEST

START_TEST(input_test_49) {
  ck_assert_int_eq(s21_validation("sqrt"), INCORRECT);
}
END_TEST

START_TEST(input_test_50) { ck_assert_int_eq(s21_validation("ln"), INCORRECT); }
END_TEST

START_TEST(input_test_51) {
  ck_assert_int_eq(s21_validation("log"), INCORRECT);
}
END_TEST

Suite *suite_s21_input(void) {
  Suite *suite = suite_create("suite_s21_input");
  TCase *tcase = tcase_create("s21_input");

  tcase_add_test(tcase, input_test_1);
  tcase_add_test(tcase, input_test_2);
  tcase_add_test(tcase, input_test_3);
  tcase_add_test(tcase, input_test_4);
  tcase_add_test(tcase, input_test_5);
  tcase_add_test(tcase, input_test_6);
  tcase_add_test(tcase, input_test_7);
  tcase_add_test(tcase, input_test_8);
  tcase_add_test(tcase, input_test_9);
  tcase_add_test(tcase, input_test_10);
  tcase_add_test(tcase, input_test_11);
  tcase_add_test(tcase, input_test_12);
  tcase_add_test(tcase, input_test_13);
  tcase_add_test(tcase, input_test_14);
  tcase_add_test(tcase, input_test_15);
  tcase_add_test(tcase, input_test_16);
  tcase_add_test(tcase, input_test_17);
  tcase_add_test(tcase, input_test_18);
  tcase_add_test(tcase, input_test_19);
  tcase_add_test(tcase, input_test_20);
  tcase_add_test(tcase, input_test_21);
  tcase_add_test(tcase, input_test_22);
  tcase_add_test(tcase, input_test_23);
  tcase_add_test(tcase, input_test_24);
  tcase_add_test(tcase, input_test_25);
  tcase_add_test(tcase, input_test_26);
  tcase_add_test(tcase, input_test_27);
  tcase_add_test(tcase, input_test_28);
  tcase_add_test(tcase, input_test_29);
  tcase_add_test(tcase, input_test_30);
  tcase_add_test(tcase, input_test_31);
  tcase_add_test(tcase, input_test_32);
  tcase_add_test(tcase, input_test_33);
  tcase_add_test(tcase, input_test_34);
  tcase_add_test(tcase, input_test_35);
  tcase_add_test(tcase, input_test_36);
  tcase_add_test(tcase, input_test_37);
  tcase_add_test(tcase, input_test_38);
  tcase_add_test(tcase, input_test_39);
  tcase_add_test(tcase, input_test_40);
  tcase_add_test(tcase, input_test_41);
  tcase_add_test(tcase, input_test_42);
  tcase_add_test(tcase, input_test_43);
  tcase_add_test(tcase, input_test_44);
  tcase_add_test(tcase, input_test_45);
  tcase_add_test(tcase, input_test_46);
  tcase_add_test(tcase, input_test_47);
  tcase_add_test(tcase, input_test_48);
  tcase_add_test(tcase, input_test_49);
  tcase_add_test(tcase, input_test_50);
  tcase_add_test(tcase, input_test_51);

  suite_add_tcase(suite, tcase);

  return suite;
}