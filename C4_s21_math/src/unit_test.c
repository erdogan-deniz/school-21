#include <check.h>
#include <math.h>  // оригинальную библ. можно подключать только здесь в тестах
#include <stdlib.h>

#include "s21_math.h"

START_TEST(abs_test) {
  ck_assert_int_eq(abs(-13), s21_abs(-13));
  ck_assert_int_eq(abs(13), s21_abs(13));
  ck_assert_int_eq(abs(-1000), s21_abs(-1000));
  ck_assert_int_eq(abs(32346234), s21_abs(32346234));
  ck_assert_int_eq(abs(0), s21_abs(0));
}
END_TEST

START_TEST(fabs_test) {
  ck_assert_ldouble_eq(s21_fabs(1.0), fabs(1.0));
  ck_assert_ldouble_eq(s21_fabs(-423423523523523.0), fabs(-423423523523523.0));
  ck_assert_ldouble_eq(s21_fabs(-1555.999), fabs(-1555.999));
  ck_assert_ldouble_eq(s21_fabs(12.0), fabs(12.0));
  ck_assert_ldouble_eq(s21_fabs(0.00000001), fabs(0.00000001));
  ck_assert_ldouble_eq(s21_fabs(S21_INF), fabs(S21_INF));
  ck_assert_ldouble_nan(s21_fabs(S21_NAN));
  ck_assert_ldouble_nan(s21_fabs(S21_NAN));
}
END_TEST

START_TEST(ceil_test) {
  ck_assert_ldouble_eq(s21_ceil(1.0), ceil(1.0));
  ck_assert_ldouble_eq(s21_ceil(-1.0), ceil(-1.0));
  ck_assert_ldouble_eq(s21_ceil(0.0), ceil(0.0));
  ck_assert_ldouble_eq(s21_ceil(21e-11), ceil(21e-11));
  ck_assert_ldouble_eq(s21_ceil(-1000000000000), ceil(-1000000000000));
  ck_assert_ldouble_eq(s21_ceil(20), ceil(20));
  ck_assert_ldouble_eq(s21_ceil(0.4), ceil(0.4));
  ck_assert_ldouble_eq(s21_ceil(-0.4), ceil(-0.4));
  ck_assert_ldouble_eq(s21_ceil(S21__INF), ceil(S21__INF));
  ck_assert_ldouble_eq(s21_ceil(S21_INF), ceil(S21_INF));
  ck_assert_ldouble_nan(ceil(S21_NAN));
  ck_assert_ldouble_nan(s21_ceil(S21_NAN));
}
END_TEST

START_TEST(floor_test) {
  ck_assert_ldouble_eq(s21_floor(0.0), floor(0.0));
  ck_assert_ldouble_eq(s21_floor(1.0), floor(1.0));
  ck_assert_ldouble_eq(s21_floor(-423423523523523.0),
                       floor(-423423523523523.0));
  ck_assert_ldouble_eq(s21_floor(-1555.999), floor(-1555.999));
  ck_assert_ldouble_eq(s21_floor(12.0), floor(12.0));
  ck_assert_ldouble_eq(s21_floor(0.00000001), floor(0.00000001));
  ck_assert_ldouble_eq(s21_floor(-1.0 / 0.0), floor(-1.0 / 0.0));
  ck_assert_ldouble_eq(s21_floor(1.0 / 0.0), floor(1.0 / 0.0));
  ck_assert_ldouble_nan(s21_floor(S21_NAN));
  ck_assert_float_nan(floor(S21_NAN));
}
END_TEST

START_TEST(fmod_test) {
  ck_assert_ldouble_eq(s21_fmod(0.0, 1.0), fmod(0.0, 1.0));
  ck_assert_ldouble_eq(s21_fmod(1.0, 21.0), fmod(1.0, 21.0));
  ck_assert_ldouble_eq(s21_fmod(-1555.999, 44.532), fmod(-1555.999, 44.532));
  ck_assert_ldouble_eq(s21_fmod(12.0, 53), fmod(12.0, 53));
  ck_assert_ldouble_eq(s21_fmod(0.00000001, 5352.6), fmod(0.00000001, 5352.6));
  ck_assert_ldouble_nan(s21_fmod(12.0, 0));
  ck_assert_ldouble_nan(fmod(12.0, 0));
  ck_assert_ldouble_nan(fmod(-S21_INF, 10));
  ck_assert_ldouble_nan(s21_fmod(-S21_INF, 10));
  ck_assert_ldouble_eq(s21_fmod(10, S21_INF), fmod(10, S21_INF));
  ck_assert_ldouble_eq(s21_fmod(10, S21__INF), fmod(10, S21__INF));
  ck_assert_ldouble_nan(fmod(S21__INF, S21__INF));
  ck_assert_ldouble_nan(s21_fmod(S21__INF, S21__INF));
  ck_assert_ldouble_nan(fmod(S21_NAN, S21_NAN));
  ck_assert_ldouble_nan(s21_fmod(S21_NAN, S21_NAN));
  ck_assert_ldouble_nan(fmod(10, S21_NAN));
  ck_assert_ldouble_nan(s21_fmod(10, S21_NAN));
}
END_TEST

START_TEST(sqrt_test) {
  ck_assert_float_eq(sqrt(0.0), s21_sqrt(0.0));
  ck_assert_float_eq(sqrt(1.0), s21_sqrt(1.0));
  ck_assert_float_eq(sqrt(3.14), s21_sqrt(3.14));
  ck_assert_float_eq(sqrt(6.28), s21_sqrt(6.28));
  ck_assert_float_eq(sqrt(2.2343), s21_sqrt(2.2343));
  ck_assert_ldouble_nan(s21_sqrt(-123));
  ck_assert_ldouble_nan(s21_sqrt(-1.0 / 0.0));
  ck_assert_ldouble_nan(s21_sqrt(0.0 / 0.0));
  ck_assert_ldouble_eq(s21_sqrt(S21_INF), sqrt(S21_INF));
}
END_TEST

START_TEST(pow_test) {
  ck_assert_ldouble_eq(pow(0.0, 1.0), s21_pow(0.0, 1.0));
  ck_assert_ldouble_eq(pow(1.0, 21.0), s21_pow(1.0, 21.0));
  ck_assert_ldouble_nan(s21_pow(-423423523523523.0, 33.33));
  ck_assert_ldouble_nan(s21_pow(-1555.999, 44.532));
  ck_assert_float_eq(pow(12.0, 5), s21_pow(12.0, 5));
  ck_assert_ldouble_eq(pow(0, 32), s21_pow(0, 32));
  ck_assert_ldouble_eq(pow(0, -5), s21_pow(0, -5));
  ck_assert_ldouble_eq(s21_pow(0.0 / 0.0, 0.0), pow(0.0 / 0.0, 0.0));
}
END_TEST

START_TEST(log_test) {
  ck_assert_float_eq(s21_log(1.0), log(1.0));
  ck_assert_ldouble_eq(s21_log(0.0), log(0.0));
  ck_assert_ldouble_eq(s21_log(S21_INF), log(S21_INF));
  ck_assert_ldouble_nan(s21_log(-1.0));
  ck_assert_ldouble_nan(log(-1.0));
  ck_assert_float_eq(s21_log(10000.0), log(10000.0));
  ck_assert_ldouble_eq_tol(s21_log(S21_PI / 2), log(S21_PI / 2), 10);
  ck_assert_ldouble_nan(s21_log(-3 * S21_PI / 4));
  ck_assert_ldouble_nan(log(-3 * S21_PI / 4));
  ck_assert_ldouble_nan(s21_log(-10000.0));
  ck_assert_ldouble_nan(log(-10000.0));
  ck_assert_ldouble_nan(s21_log(-1.0 / 0.0));
  ck_assert_ldouble_nan(log(-1.0 / 0.0));
  ck_assert_ldouble_nan(s21_log(S21_NAN));
  ck_assert_ldouble_nan(log(S21_NAN));
}
END_TEST

START_TEST(asin_test) {
  ck_assert_float_eq(s21_asin(1.0), asin(1.0));
  ck_assert_ldouble_eq_tol(s21_asin(0.7), asin(0.7), 6);
  ck_assert_ldouble_eq(s21_asin(0.0), asin(0.0));
  ck_assert_ldouble_eq(s21_asin(-1.0), asin(-1.0));
  ck_assert_ldouble_nan(s21_asin(10000.0));
  ck_assert_ldouble_nan(asin(10000.0));
  ck_assert_ldouble_nan(s21_asin(-3 * S21_PI / 4));
  ck_assert_ldouble_nan(asin(-3 * S21_PI / 4));
  ck_assert_ldouble_nan(s21_asin(-10000.0));
  ck_assert_ldouble_nan(asin(-10000.0));
  ck_assert_ldouble_nan(s21_asin(-1.0 / 0.0));
  ck_assert_ldouble_nan(asin(-1.0 / 0.0));
  ck_assert_ldouble_nan(s21_asin(1.0 / 0.0));
  ck_assert_ldouble_nan(asin(1.0 / 0.0));
  ck_assert_ldouble_nan(s21_asin(0.0 / 0.0));
  ck_assert_ldouble_nan(asin(0.0 / 0.0));
}
END_TEST

START_TEST(acos_test) {
  ck_assert_ldouble_eq(s21_acos(1.0), acos(1.0));
  ck_assert_ldouble_eq(s21_acos(-1.0), acos(-1.0));
  ck_assert_ldouble_eq(s21_acos(0.0), acos(0.0));
  ck_assert_ldouble_eq_tol(s21_acos(0.5), acos(0.5), 1e-6);
  ck_assert_ldouble_eq_tol(s21_acos(-0.5), acos(-0.5), 1e-6);
  ck_assert_ldouble_nan(s21_acos(-4234235223.0));
  ck_assert_ldouble_nan(s21_acos(5));
  ck_assert_ldouble_nan(acos(5));
  ck_assert_ldouble_nan(s21_acos(13.02));
  ck_assert_ldouble_nan(acos(13.02));
  ck_assert_ldouble_nan(s21_acos(S21__INF));
  ck_assert_ldouble_nan(acos(S21__INF));
  ck_assert_ldouble_nan(s21_acos(S21_NAN));
  ck_assert_ldouble_nan(acos(S21_NAN));
}
END_TEST

START_TEST(atan_test) {
  ck_assert_ldouble_eq(s21_atan(0.0), atan(0.0));
  ck_assert_float_eq(s21_atan(1.0), atan(1.0));
  ck_assert_float_eq(s21_atan(-1.0), atan(-1.0));
  ck_assert_float_eq(s21_atan(S21__INF), atan(S21__INF));
  ck_assert_float_eq(s21_atan(S21_INF), atan(S21_INF));
  ck_assert_ldouble_eq_tol(s21_sin(-4234235223.0), sin(-4234235223.0), 10);
  ck_assert_ldouble_eq_tol(s21_sin(-1555.999), sin(-1555.999), 10);
  ck_assert_ldouble_eq_tol(s21_atan(S21_PI / 4), atan(S21_PI / 4), 10);
  ck_assert_ldouble_eq_tol(s21_atan(12.0), atan(12.0), 10);
  ck_assert_ldouble_nan(s21_atan(0.0 / 0.0));
  ck_assert_ldouble_nan(s21_atan(S21_NAN));
  ck_assert_ldouble_nan(atan(S21_NAN));
}
END_TEST

START_TEST(sin_test) {
  ck_assert_float_eq(s21_sin(0.0), sin(0.0));
  ck_assert_float_eq(s21_sin(1.0), sin(1.0));
  ck_assert_ldouble_eq_tol(s21_sin(-4234235223.0), sin(-4234235223.0), 10);
  ck_assert_ldouble_eq_tol(s21_sin(-1555.999), sin(-1555.999), 10);
  ck_assert_ldouble_eq_tol(s21_sin(12.0), sin(12.0), 10);
  ck_assert_float_eq(s21_sin(-1555.999), sin(-1555.999));
  ck_assert_float_eq(s21_sin(12.0), sin(12.0));
  ck_assert_ldouble_nan(s21_sin(-1.0 / 0.0));
  ck_assert_ldouble_nan(sin(-1.0 / 0.0));
  ck_assert_ldouble_nan(s21_sin(0.0 / 0.0));
  ck_assert_ldouble_nan(sin(0.0 / 0.0));
  ck_assert_ldouble_nan(s21_sin(S21_INF));
  ck_assert_ldouble_nan(sin(S21_INF));
}
END_TEST

START_TEST(cos_test) {
  ck_assert_float_eq(s21_cos(1.0), cos(1.0));
  ck_assert_float_eq(s21_cos(-1.0), cos(-1.0));
  ck_assert_ldouble_eq(s21_cos(0.0), cos(0.0));
  ck_assert_float_eq(s21_cos(10000.0), cos(10000.0));
  ck_assert_ldouble_eq_tol(s21_cos(S21_PI / 2), cos(S21_PI / 2), 10);
  ck_assert_ldouble_eq_tol(s21_cos(-3 * S21_PI / 4), cos(-3 * S21_PI / 4), 10);
  ck_assert_float_eq(s21_cos(-10000.0), cos(-10000.0));
  ck_assert_ldouble_nan(s21_acos(-1.0 / 0.0));
  ck_assert_ldouble_nan(cos(-1.0 / 0.0));
  ck_assert_ldouble_nan(s21_cos(S21_NAN));
  ck_assert_ldouble_nan(cos(S21_NAN));
}
END_TEST

START_TEST(tan_test) {
  ck_assert_ldouble_eq(s21_tan(0.0), tan(0.0));
  ck_assert_float_eq(s21_tan(1.0), tan(1.0));
  ck_assert_ldouble_eq_tol(s21_tan(-4234235223.0), tan(-4234235223.0), 10);
  ck_assert_ldouble_eq_tol(s21_tan(-1555.999), tan(-1555.999), 10);
  ck_assert_ldouble_eq_tol(s21_tan(S21_PI / 4), tan(S21_PI / 4), 10);
  ck_assert_ldouble_eq_tol(s21_tan(12.0), tan(12.0), 10);
  ck_assert_ldouble_nan(s21_tan(0.0 / 0.0));
  ck_assert_ldouble_nan(s21_tan(-1.0 / 0.0));
  ck_assert_ldouble_nan(tan(-1.0 / 0.0));
  ck_assert_ldouble_nan(s21_tan(S21_INF));
  ck_assert_ldouble_nan(tan(S21_INF));
  ck_assert_ldouble_nan(s21_tan(S21_NAN));
  ck_assert_ldouble_nan(tan(S21_NAN));
}
END_TEST

START_TEST(exp_test) {
  ck_assert_float_eq(exp(13.54), s21_exp(13.54));
  ck_assert_float_eq(exp(-0.54), s21_exp(-0.54));
  ck_assert_float_eq(exp(1000), s21_exp(1000));
  ck_assert_float_eq(exp(1), s21_exp(1));
  ck_assert_float_eq(exp(S21__INF), s21_exp(S21__INF));
  ck_assert_float_eq(exp(S21_INF), s21_exp(S21_INF));
  ck_assert_float_eq(exp(2), s21_exp(2));
  ck_assert_float_eq(exp(-1), s21_exp(-1));
  ck_assert_float_eq(exp(0), s21_exp(0));
  ck_assert_float_eq(exp(710), s21_exp(710));
  ck_assert_float_eq(exp(1.2345), s21_exp(1.2345));
  ck_assert_float_eq(exp(1.23454656768), s21_exp(1.23454656768));
}
END_TEST

int main(void) {
  Suite *suite =
      suite_create("UNITS");  // test suite - это набор тестовых случаев
  TCase *tcase =
      tcase_create("TESTS");  // test case — это набор тестовых примеров
  SRunner *srunner = srunner_create(
      suite);  // Suite runner - это функция, которая берет набор тестов
               // и запускает все тестовые случаи и их тестовые функции
  int val = 0;

  suite_add_tcase(suite, tcase);
  tcase_add_test(tcase, sqrt_test);
  tcase_add_test(tcase, pow_test);
  tcase_add_test(tcase, log_test);
  tcase_add_test(tcase, fmod_test);
  tcase_add_test(tcase, abs_test);
  tcase_add_test(tcase, fabs_test);
  tcase_add_test(tcase, ceil_test);
  tcase_add_test(tcase, floor_test);
  tcase_add_test(tcase, exp_test);
  tcase_add_test(tcase, sin_test);
  tcase_add_test(tcase, cos_test);
  tcase_add_test(tcase, tan_test);
  tcase_add_test(tcase, asin_test);
  tcase_add_test(tcase, acos_test);
  tcase_add_test(tcase, atan_test);
  // Запуск всех наборов тестов (suite - набор). CK_NORMAL - что бы выводить
  // только неудачные тесты.
  srunner_run_all(srunner, CK_NORMAL);
  // Количество проваленных тестов.
  val = srunner_ntests_failed(srunner);
  // Освобождаем память срунеру, при этом suite и tcase освобождать почему то не
  // нужно
  srunner_free(srunner);

  return val == 0 ? 0 : 1;
}
