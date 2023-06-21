#include <check.h>
#include <stdlib.h>

#include "s21_decimal.h"

//  harmonic

START_TEST(s21_is_less_null) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  value_1.bits[0] = 0;
  value_2.bits[0] = 0;
  ck_assert_int_eq(s21_is_less(value_1, value_2), FALSE);
  set_sign(&value_2);
  ck_assert_int_eq(s21_is_less(value_1, value_2), FALSE);
}
END_TEST

START_TEST(s21_is_less_normal) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  for (int i = 1, j = 2; i < 50 || j < 51; i++, j++) {
    value_1.bits[0] = i;
    value_2.bits[0] = j;
    ck_assert_int_eq(s21_is_less(value_1, value_2), TRUE);
    ck_assert_int_eq(s21_is_less(value_2, value_1), FALSE);
  }
}
END_TEST

START_TEST(s21_is_less_negative) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  value_1.bits[0] = 20;
  value_2.bits[0] = 5;
  set_sign(&value_1);
  ck_assert_int_eq(s21_is_less(value_1, value_2), TRUE);
  delete_sign(&value_1);
  set_sign(&value_2);
  ck_assert_int_eq(s21_is_less(value_1, value_2), FALSE);
}
END_TEST

START_TEST(s21_is_less_pow) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  value_1.bits[0] = 50;
  value_2.bits[0] = 30;
  s21_set_power(&value_1, 8);
  s21_set_power(&value_2, 8);
  ck_assert_int_eq(s21_is_less(value_1, value_2), FALSE);
  s21_set_power(&value_2, 0);
  ck_assert_int_eq(s21_is_less(value_1, value_2), TRUE);
}
END_TEST

START_TEST(s21_is_less_or_equal_normal) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  for (int i = 0, j = 1; i < 51 || j < 52; i++, j++) {
    value_1.bits[0] = i;
    value_2.bits[0] = j;
    ck_assert_int_eq(s21_is_less_or_equal(value_1, value_2), TRUE);
  }
  for (int i = 0, j = 0; i < 52 || j < 52; i++, j++) {
    value_1.bits[0] = i;
    value_2.bits[0] = j;
    ck_assert_int_eq(s21_is_less_or_equal(value_1, value_2), TRUE);
  }
}
END_TEST

START_TEST(s21_is_less_or_equal_with_sign) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  value_1.bits[0] = 123450;
  value_2.bits[0] = 123450;
  set_sign(&value_2);
  ck_assert_int_eq(s21_is_less_or_equal(value_1, value_2), FALSE);
  set_sign(&value_1);
  ck_assert_int_eq(s21_is_less_or_equal(value_1, value_2), TRUE);
  delete_sign(&value_1);
  ck_assert_int_eq(s21_is_less_or_equal(value_1, value_2), FALSE);
}
END_TEST

START_TEST(s21_is_greater_null) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  value_1.bits[0] = 0;
  value_2.bits[0] = 0;
  ck_assert_int_eq(s21_is_greater(value_1, value_2), FALSE);
  set_sign(&value_2);
  ck_assert_int_eq(s21_is_greater(value_1, value_2), FALSE);
}
END_TEST

START_TEST(s21_is_greater_normal) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  for (int i = 1, j = 2; i < 50 || j < 51; i++, j++) {
    value_1.bits[0] = i;
    value_2.bits[0] = j;
    ck_assert_int_eq(s21_is_greater(value_1, value_2), FALSE);
    ck_assert_int_eq(s21_is_greater(value_2, value_1), TRUE);
  }
}
END_TEST

START_TEST(s21_is_greater_negative) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  value_1.bits[0] = 20;
  value_2.bits[0] = 5;
  set_sign(&value_1);
  ck_assert_int_eq(s21_is_greater(value_1, value_2), FALSE);
  delete_sign(&value_1);
  set_sign(&value_2);
  ck_assert_int_eq(s21_is_greater(value_1, value_2), TRUE);
}
END_TEST

START_TEST(s21_is_greater_two_negative) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  value_1.bits[0] = 20;
  value_2.bits[0] = 5;
  set_sign(&value_1);
  set_sign(&value_2);
  ck_assert_int_eq(s21_is_greater(value_1, value_2), FALSE);
}
END_TEST

START_TEST(s21_is_greater_pow) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  value_1.bits[0] = 50;
  value_2.bits[0] = 30;
  s21_set_power(&value_1, 8);
  s21_set_power(&value_2, 8);
  ck_assert_int_eq(s21_is_greater(value_1, value_2), TRUE);
  s21_set_power(&value_2, 0);
  ck_assert_int_eq(s21_is_greater(value_1, value_2), FALSE);
}
END_TEST

START_TEST(s21_is_greater_or_equal_normal) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  for (int i = 0, j = 1; i < 51 || j < 52; i++, j++) {
    value_1.bits[0] = i;
    value_2.bits[0] = j;
    ck_assert_int_eq(s21_is_greater_or_equal(value_1, value_2), FALSE);
  }
  for (int i = 0, j = 0; i < 52 || j < 52; i++, j++) {
    value_1.bits[0] = i;
    value_2.bits[0] = j;
    ck_assert_int_eq(s21_is_greater_or_equal(value_1, value_2), TRUE);
  }
}
END_TEST

START_TEST(s21_is_greater_or_equal_with_sign) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  value_1.bits[0] = 123450;
  value_2.bits[0] = 123450;
  set_sign(&value_2);
  ck_assert_int_eq(s21_is_greater_or_equal(value_1, value_2), TRUE);
  set_sign(&value_1);
  ck_assert_int_eq(s21_is_greater_or_equal(value_1, value_2), TRUE);
  delete_sign(&value_2);
  ck_assert_int_eq(s21_is_greater_or_equal(value_1, value_2), FALSE);
}
END_TEST

START_TEST(s21_int_and_decimal_max) {
  s21_decimal value_1 = {0};

  value_1.bits[0] = 4294967295;
  int a = 0;
  int res = s21_from_decimal_to_int(value_1, &a);
  ck_assert_int_eq(res, CONVERT_ERROR);
}
END_TEST

START_TEST(s21_int_and_decimal_big_pow) {
  s21_decimal value_1 = {0};
  int result = 184467440;

  value_1.bits[0] = 344;
  value_1.bits[1] = 4294967295;
  int a = 0;
  s21_set_power(&value_1, 11);
  s21_from_decimal_to_int(value_1, &a);
  ck_assert_int_eq(a, result);
}
END_TEST

START_TEST(s21_int_and_decimal_error) {
  s21_decimal value_1 = {0};

  value_1.bits[0] = 2147483648;
  int a = 0;
  set_sign(&value_1);
  int res = s21_from_decimal_to_int(value_1, &a);
  ck_assert_int_eq(res, CONVERT_ERROR);
  s21_decimal value_2 = {0};
  int* b = NULL;
  res = s21_from_decimal_to_int(value_2, b);
  ck_assert_int_eq(res, CONVERT_ERROR);
  s21_decimal* dst = NULL;
  int c = 0;
  res = s21_from_int_to_decimal(c, dst);
  ck_assert_int_eq(res, CONVERT_ERROR);
}
END_TEST

START_TEST(s21_int_and_decimal_sign) {
  s21_decimal value_1 = {0};
  int a = -5;
  s21_decimal test = {{5}};
  s21_from_int_to_decimal(a, &value_1);
  ck_assert_int_eq(value_1.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(value_1), 1);
}
END_TEST

START_TEST(s21_int_and_decimal_whith_pow) {
  s21_decimal value_1 = {0};
  int a = 0;
  value_1.bits[0] = 5;
  s21_set_power(&value_1, 20);
  s21_from_decimal_to_int(value_1, &a);
  ck_assert_int_eq(a, 0);
}
END_TEST

START_TEST(s21_int_and_decimal_nul) {
  s21_decimal value_1 = {0};
  s21_decimal test = {0};
  int a = 0;
  s21_from_int_to_decimal(a, &value_1);
  ck_assert_int_eq(value_1.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(value_1), 0);
  a = 123456;
  test.bits[0] = 123456;
  s21_from_int_to_decimal(a, &value_1);
  ck_assert_int_eq(value_1.bits[0], test.bits[0]);
  set_sign(&value_1);
  int b = 0;
  s21_from_decimal_to_int(value_1, &b);
  ck_assert_int_eq(value_1.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(value_1), 1);
}
END_TEST

START_TEST(s21_sub_normal) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  value_1.bits[0] = 155;
  value_2.bits[0] = 55;
  s21_sub(value_1, value_2, &result);
  s21_decimal test = {0};
  test.bits[0] = 100;
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  memset(&result, 0, sizeof(s21_decimal));
  value_1.bits[0] = 50;
  value_2.bits[0] = 150;
  s21_sub(value_1, value_2, &result);
  int sign = get_sign(result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(sign, 1);
  memset(&result, 0, sizeof(s21_decimal));
  s21_set_power(&value_2, 2);
  test.bits[0] = 4850;
  s21_sub(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_uint_eq(s21_get_power(result), 2);
  ck_assert_uint_eq(get_sign(result), 0);
}
END_TEST

START_TEST(s21_sub_inf) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  value_1.bits[0] = 4294967295;
  value_1.bits[1] = 4294967295;
  value_1.bits[2] = 4294967295;
  value_2.bits[0] = 55;
  set_sign(&value_1);
  int res = s21_sub(value_1, value_2, &result);
  ck_assert_uint_eq(res, NEGATIVE_INF);
}
END_TEST

START_TEST(s21_sub_one_sign) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  value_1.bits[0] = 150;
  value_2.bits[0] = 50;
  set_sign(&value_1);
  s21_sub(value_1, value_2, &result);
  s21_decimal test = {0};
  test.bits[0] = 200;
  ck_assert_int_eq(result.bits[0], test.bits[0]);
  int sign = get_sign(result);
  ck_assert_int_eq(sign, 1);
  memset(&result, 0, sizeof(s21_decimal));
  delete_sign(&value_1);
  set_sign(&value_2);
  s21_sub(value_1, value_2, &result);
  ck_assert_int_eq(result.bits[0], test.bits[0]);
  int sign1 = get_sign(result);
  ck_assert_int_eq(sign1, 0);
}
END_TEST

START_TEST(s21_sub_two_sign) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  value_1.bits[0] = 150;
  value_2.bits[0] = 50;
  set_sign(&value_1);
  set_sign(&value_2);

  s21_sub(value_1, value_2, &result);
  s21_decimal test = {0};
  test.bits[0] = 100;
  ck_assert_int_eq(result.bits[0], test.bits[0]);
  int sign = get_sign(result);
  ck_assert_int_eq(sign, 1);
  memset(&result, 0, sizeof(s21_decimal));
  s21_sub(value_1, value_2, &result);
  ck_assert_int_eq(result.bits[0], test.bits[0]);
  int sign1 = get_sign(result);
  ck_assert_int_eq(sign1, 1);
  value_1.bits[0] = 50;
  value_2.bits[0] = 150;
  memset(&result, 0, sizeof(s21_decimal));
  s21_sub(value_1, value_2, &result);
  ck_assert_int_eq(result.bits[0], test.bits[0]);
  sign1 = get_sign(result);
  ck_assert_int_eq(sign1, 0);
}
END_TEST

START_TEST(s21_div_normal) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  value_1.bits[0] = 150;
  value_2.bits[0] = 10;
  s21_div(value_1, value_2, &result);
  ck_assert_int_eq(result.bits[0], 15);
  value_1.bits[0] = 4294967295;
  value_2.bits[0] = 123478698;
  s21_set_power(&value_2, 5);
  memset(&result, 0, sizeof(s21_decimal));
  s21_div(value_1, value_2, &result);
  ck_assert_uint_eq(s21_get_power(result), 22);
  memset(&result, 0, sizeof(s21_decimal));
  memset(&value_1, 0, sizeof(s21_decimal));
  memset(&value_2, 0, sizeof(s21_decimal));
  value_1.bits[0] = 4294967294;
  value_1.bits[1] = 1;
  value_2.bits[0] = 2;
  s21_div(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], 4294967295);
}
END_TEST

START_TEST(s21_div_scale) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  value_1.bits[0] = 150;
  value_2.bits[0] = 2;
  s21_set_power(&value_2, 1);
  s21_div(value_1, value_2, &result);
  ck_assert_int_eq(result.bits[0], 750);
}
END_TEST

START_TEST(s21_div_zero) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  value_1.bits[0] = 150;
  value_2.bits[0] = 0;

  int result1 = s21_div(value_1, value_2, &result);
  ck_assert_uint_eq(result1, s21_NAN);
  set_sign(&value_2);
  ck_assert_uint_eq(result1, s21_NAN);
}
END_TEST

START_TEST(s21_div_negative) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  s21_decimal test = {0};
  value_1.bits[0] = 547;
  value_2.bits[0] = 5;
  test.bits[0] = 1094;
  set_sign(&value_2);
  s21_div(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  int pow = s21_get_power(result);
  ck_assert_uint_eq(pow, 1);
  ck_assert_uint_eq(get_sign(result), 1);
  s21_decimal value_3 = {{20}};
  s21_decimal value_4 = {{5}};
  set_sign(&value_4);
  test.bits[0] = 4;
  memset(&result, 0, sizeof(s21_decimal));
  s21_div(value_3, value_4, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_uint_eq(get_sign(result), 1);
}
END_TEST

START_TEST(s21_div_pi) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  s21_decimal test = {0};
  value_1.bits[0] = 22;
  value_2.bits[0] = 7;
  test.bits[0] = 3297921316;
  test.bits[1] = 208949406;
  test.bits[2] = 1703746271;
  s21_div(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_uint_eq(result.bits[1], test.bits[1]);
  ck_assert_uint_eq(result.bits[2], test.bits[2]);
  int pow = s21_get_power(result);
  ck_assert_uint_eq(pow, 28);
}
END_TEST

START_TEST(s21_div_normalize) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  s21_decimal test = {0};
  value_1.bits[0] = 4294967295;
  value_2.bits[0] = 2;
  test.bits[0] = 4294967291;
  test.bits[1] = 4;
  s21_div(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_uint_eq(result.bits[1], test.bits[1]);
  ck_assert_uint_eq(s21_get_power(result), 1);
}
END_TEST

START_TEST(s21_div_min_pow) {
  s21_decimal value_1 = {{3333388888}};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  s21_decimal test = {0};
  value_2.bits[0] = 4294967295;
  value_2.bits[1] = 4294967295;
  test.bits[0] = 1409956271;
  test.bits[1] = 4207;
  test.bits[2] = 0;
  s21_set_power(&value_1, 5);
  s21_div(value_1, value_2, &result);
  ck_assert_uint_eq(s21_get_power(result), 28);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_uint_eq(result.bits[1], test.bits[1]);
}
END_TEST

START_TEST(s21_div_min_pow_second_dec) {
  s21_decimal value_1 = {{3333388888}};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  s21_decimal test = {0};
  value_2.bits[0] = 22647;
  test.bits[0] = 3777176791;
  test.bits[1] = 1197098455;
  test.bits[2] = 797913073;
  s21_set_power(&value_1, 5);
  s21_set_power(&value_2, 3);
  s21_div(value_1, value_2, &result);
  ck_assert_uint_eq(s21_get_power(result), 28);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_uint_eq(result.bits[1], test.bits[1]);
}
END_TEST

START_TEST(s21_div_pow_small) {
  s21_decimal value_1 = {{291}};
  s21_decimal value_2 = {{123}};
  s21_decimal result = {0};
  s21_decimal test = {0};
  test.bits[0] = 425568406;
  test.bits[1] = 790584587;
  test.bits[2] = 1282531838;
  s21_set_power(&value_2, 28);
  s21_div(value_1, value_2, &result);
  ck_assert_uint_eq(s21_get_power(result), 0);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_uint_eq(result.bits[1], test.bits[1]);
  ck_assert_uint_eq(result.bits[2], test.bits[2]);
}
END_TEST

START_TEST(s21_div_max) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  s21_decimal test = {0};
  value_1.bits[0] = 4294967295;
  value_1.bits[1] = 4294967295;
  value_1.bits[2] = 4294967295;
  value_2.bits[0] = 4294967295;
  value_2.bits[1] = 4294967295;
  value_2.bits[2] = 4294967295;
  test.bits[0] = 1;
  s21_div(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_uint_eq(s21_get_power(result), 0);
}
END_TEST

START_TEST(s21_div_pos_over) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  value_1.bits[0] = 4294967295;
  value_1.bits[1] = 4294967295;
  value_1.bits[2] = 4294967295;
  value_2.bits[0] = 2;
  s21_set_power(&value_2, 5);
  int over = s21_div(value_1, value_2, &result);
  ck_assert_uint_eq(over, POZITIVE_INF);
  set_sign(&value_1);
  set_sign(&value_2);
  ck_assert_uint_eq(over, POZITIVE_INF);
}
END_TEST

START_TEST(s21_div_neg_over) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  value_1.bits[0] = 4294967295;
  value_1.bits[1] = 4294967295;
  value_1.bits[2] = 4294967295;
  value_2.bits[0] = 2;
  s21_set_power(&value_2, 5);
  set_sign(&value_1);
  int over = s21_div(value_1, value_2, &result);
  ck_assert_uint_eq(over, NEGATIVE_INF);
  delete_sign(&value_1);
  set_sign(&value_2);
  ck_assert_uint_eq(over, NEGATIVE_INF);
}
END_TEST

START_TEST(s21_div_one) {
  s21_decimal value_1 = {{745}};
  s21_decimal value_2 = {{1}};
  s21_decimal result = {0};
  s21_div(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], value_1.bits[0]);
  ck_assert_uint_eq(get_sign(result), 0);
  memset(&result, 0, sizeof(s21_decimal));
  set_sign(&value_2);
  s21_div(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], value_1.bits[0]);
  ck_assert_uint_eq(get_sign(result), 1);
}
END_TEST

START_TEST(s21_div_pow_norm) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  s21_decimal test = {0};
  value_1.bits[0] = 4294967295;
  value_1.bits[1] = 4294967295;
  value_1.bits[2] = 4294967295;
  value_2.bits[0] = 112;
  test.bits[0] = 1227133512;
  test.bits[1] = 2454267026;
  test.bits[2] = 3834792228;
  s21_div(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_uint_eq(result.bits[1], test.bits[1]);
  ck_assert_uint_eq(result.bits[2], test.bits[2]);
  ck_assert_uint_eq(s21_get_power(result), 2);
}
END_TEST

START_TEST(s21_mod_max_dec) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  s21_decimal test = {0};
  value_1.bits[0] = 4294967295;
  value_1.bits[1] = 4294967295;
  value_1.bits[2] = 4294967295;
  value_2.bits[0] = 4294967295;
  value_2.bits[1] = 4294967295;
  value_2.bits[2] = 4294967295;
  s21_mod(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_uint_eq(s21_get_power(result), 0);
}
END_TEST

START_TEST(s21_mod_max_dec_and_two) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  s21_decimal test = {0};
  value_1.bits[0] = 4294967295;
  value_1.bits[1] = 4294967295;
  value_1.bits[2] = 4294967295;
  value_2.bits[0] = 2;
  test.bits[0] = 1;
  s21_mod(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_uint_eq(s21_get_power(result), 0);
}
END_TEST

START_TEST(s21_mod_max_dec_and_biguint) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  s21_decimal test = {0};
  value_1.bits[0] = 4294967295;
  value_1.bits[1] = 4294967295;
  value_1.bits[2] = 4294967295;
  value_2.bits[0] = 429496729;
  test.bits[0] = 215;
  s21_mod(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_uint_eq(s21_get_power(result), 0);
}
END_TEST

START_TEST(s21_mod_dec_with_pow) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  s21_decimal test = {0};
  value_1.bits[0] = 4294967295;
  value_2.bits[0] = 523467;
  test.bits[0] = 222906;
  s21_set_power(&value_2, 4);
  s21_mod(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_uint_eq(s21_get_power(result), 4);
}
END_TEST

START_TEST(s21_mod_dec_revers) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  s21_decimal test = {0};
  value_1.bits[0] = 523467;
  value_2.bits[0] = 4294967295;
  test.bits[0] = 523467;
  s21_set_power(&value_1, 4);
  s21_mod(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_uint_eq(s21_get_power(result), 4);
}
END_TEST

START_TEST(s21_mod_dec_error) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  value_1.bits[0] = 523467;
  int over = s21_mod(value_1, value_2, &result);
  ck_assert_uint_eq(over, s21_NAN);
}
END_TEST

START_TEST(s21_mod_sign) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  s21_decimal test = {0};
  value_1.bits[0] = 523467;
  value_2.bits[0] = 4294967295;
  test.bits[0] = 523467;
  s21_set_power(&value_1, 4);
  set_sign(&value_1);
  s21_mod(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_uint_eq(s21_get_power(result), 4);
  ck_assert_uint_eq(get_sign(result), 1);
}
END_TEST

START_TEST(s21_mod_over) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  s21_decimal test = {0};
  value_1.bits[0] = 4294967295;
  value_1.bits[1] = 4294967295;
  value_1.bits[2] = 4294967295;
  value_2.bits[0] = 523467;
  s21_set_power(&value_2, 10);
  s21_mod(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
}
END_TEST

START_TEST(s21_mod_over_norm) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  s21_decimal test = {0};
  value_1.bits[0] = 4294967295;
  value_1.bits[1] = 4294967295;
  value_1.bits[2] = 4294967295;
  value_2.bits[0] = 523467;
  test.bits[0] = 4257;
  s21_set_power(&value_2, 1);
  s21_mod(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
}
END_TEST

//  mikeleil

START_TEST(isEqual) {
  s21_decimal a = {{48, 0}}, b = {{48, 0}};
  ck_assert_uint_eq(s21_is_equal(a, b), 1);
}
END_TEST

START_TEST(isEqual1) {
  s21_decimal a = {{1, 1, 0, 0}}, b = {{1, 1, 1, 0}};
  ck_assert_uint_eq(s21_is_equal(a, b), 0);
}
END_TEST

// freidash

START_TEST(s21_mul_value_1_is_one) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  s21_decimal test = {0};
  value_1.bits[0] = 1;
  value_2.bits[0] = 10;
  test.bits[0] = 10;
  s21_mul(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  set_sign(&value_1);
  memset(&result, 0, sizeof(s21_decimal));
  s21_mul(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_uint_eq(get_sign(result), 1);
}
END_TEST

START_TEST(s21_mul_value_2_is_one) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  s21_decimal test = {0};
  value_1.bits[0] = 15;
  value_2.bits[0] = 1;
  test.bits[0] = 15;
  s21_mul(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
}
END_TEST

START_TEST(s21_mul_value_1_is_zero) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  s21_decimal test = {0};
  value_1.bits[0] = 0;
  value_2.bits[0] = 100;
  test.bits[0] = 0;
  s21_mul(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
}
END_TEST

START_TEST(s21_mul_value_2_is_zero) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  s21_decimal test = {0};
  value_1.bits[0] = 7;
  value_2.bits[0] = 0;
  test.bits[0] = 0;
  s21_mul(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
}
END_TEST

START_TEST(s21_mul_max) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  s21_decimal test = {0};
  value_1.bits[0] = 4294967295;
  value_1.bits[1] = 4294967295;
  value_1.bits[2] = 4294967295;
  value_2.bits[0] = 5;
  test.bits[0] = 4294967293;
  test.bits[1] = 4294967295;
  test.bits[2] = 2147483647;
  s21_set_power(&value_2, 1);
  int res = s21_mul(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_uint_eq(s21_get_power(result), 0);
  ck_assert_uint_eq(get_sign(result), 0);
  ck_assert_uint_eq(res, 0);
}
END_TEST

START_TEST(s21_mul_big_power) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  s21_decimal test = {0};
  value_1.bits[0] = 4294967295;
  value_2.bits[0] = 255;
  test.bits[0] = 4294967041;
  test.bits[1] = 254;
  s21_set_power(&value_2, 10);
  int res = s21_mul(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_uint_eq(s21_get_power(result), 10);
  ck_assert_uint_eq(get_sign(result), 0);
  ck_assert_uint_eq(res, 0);
}
END_TEST

START_TEST(s21_mul_big_negative_over) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  value_1.bits[0] = 4294967295;
  value_1.bits[1] = 4294967295;
  value_1.bits[2] = 4294967295;
  value_2.bits[0] = 15;
  s21_set_power(&value_2, 1);
  set_sign(&value_2);
  int res = s21_mul(value_1, value_2, &result);
  ck_assert_uint_eq(res, NEGATIVE_INF);
}
END_TEST

START_TEST(s21_mul_big_over) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  value_1.bits[0] = 4294967295;
  value_1.bits[1] = 4294967295;
  value_1.bits[2] = 4294967295;
  value_2.bits[0] = 15;
  s21_set_power(&value_2, 1);
  int res = s21_mul(value_1, value_2, &result);
  ck_assert_uint_eq(res, POZITIVE_INF);
}
END_TEST

START_TEST(s21_mul_norm) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  value_1.bits[0] = 4294967295;
  value_1.bits[1] = 4294967295;
  value_1.bits[2] = 4294967295;
  value_2.bits[0] = 15;
  s21_set_power(&value_2, 4);
  int res = s21_mul(value_1, value_2, &result);
  ck_assert_uint_eq(s21_get_power(result), 2);
  ck_assert_uint_eq(res, OK);
}
END_TEST

START_TEST(s21_mul_value_1_is_minus) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  s21_decimal test = {0};
  set_sign(&value_1);
  value_1.bits[0] = 15;
  value_2.bits[0] = 1;
  test.bits[0] = 15;
  s21_mul(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_uint_eq(get_sign(result), 1);
}
END_TEST

START_TEST(s21_mul_value_2_is_minus) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  s21_decimal test = {0};
  value_1.bits[0] = 15;
  set_sign(&value_2);
  value_2.bits[0] = 1;
  test.bits[0] = 15;
  s21_mul(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_uint_eq(get_sign(result), 1);
}
END_TEST

START_TEST(s21_mul_value_1_is_zero_minus) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  s21_decimal test = {0};
  set_sign(&value_1);
  value_1.bits[0] = 0;
  value_2.bits[0] = 100;
  test.bits[0] = 0;
  s21_mul(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_uint_eq(get_sign(result), 1);
}
END_TEST

START_TEST(s21_mul_value_2_is_zero_minus) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  s21_decimal test = {0};
  value_1.bits[0] = 7;
  set_sign(&value_2);
  value_2.bits[0] = 0;
  test.bits[0] = 0;
  s21_mul(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_uint_eq(get_sign(result), 1);
}
END_TEST

START_TEST(s21_mul_value_1_2_is_minus) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  s21_decimal test = {0};
  set_sign(&value_1);
  set_sign(&value_2);
  value_1.bits[0] = 0;
  value_2.bits[0] = 100;
  test.bits[0] = 0;
  s21_mul(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_uint_eq(get_sign(result), 0);
}
END_TEST

START_TEST(s21_mul_max_1) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  s21_decimal test = {0};
  value_1.bits[0] = 4294967295;
  value_1.bits[1] = 4294967295;
  value_1.bits[2] = 4294967295;
  set_sign(&value_1);
  value_2.bits[0] = 5;
  set_sign(&value_2);
  test.bits[0] = 4294967293;
  test.bits[1] = 4294967295;
  test.bits[2] = 2147483647;
  s21_set_power(&value_2, 1);
  int res = s21_mul(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_uint_eq(s21_get_power(result), 0);
  ck_assert_uint_eq(get_sign(result), 0);
  ck_assert_uint_eq(res, 0);
}
END_TEST

START_TEST(s21_mul_max_2) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  s21_decimal test = {0};
  value_1.bits[0] = 4294967295;
  set_sign(&value_1);
  value_1.bits[1] = 4294967295;
  value_1.bits[2] = 4294967295;
  value_2.bits[0] = 5;
  test.bits[0] = 4294967293;
  test.bits[1] = 4294967295;
  test.bits[2] = 2147483647;
  s21_set_power(&value_2, 1);
  int res = s21_mul(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_uint_eq(s21_get_power(result), 0);
  ck_assert_uint_eq(get_sign(result), 1);
  ck_assert_uint_eq(res, 0);
}
END_TEST

START_TEST(s21_mul_max_3) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  s21_decimal test = {0};
  set_sign(&value_1);
  value_1.bits[0] = 4294967295;
  value_1.bits[1] = 4294967295;
  value_1.bits[2] = 4294967295;
  value_2.bits[0] = 5;
  test.bits[0] = 4294967293;
  test.bits[1] = 4294967295;
  test.bits[2] = 2147483647;
  s21_set_power(&value_2, 1);
  int res = s21_mul(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_uint_eq(s21_get_power(result), 0);
  ck_assert_uint_eq(get_sign(result), 1);
  ck_assert_uint_eq(res, 0);
}
END_TEST

// s21_round
START_TEST(s21_round_positive_integer) {
  s21_decimal result = {0};
  s21_decimal value = {0};
  value.bits[0] = 11;
  s21_decimal test = {{11}};
  int s21_result = s21_round(value, &result);
  ck_assert_int_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 0);
  ck_assert_int_eq(s21_result, OK);
}
END_TEST

START_TEST(s21_round_null) {
  s21_decimal* result = NULL;
  s21_decimal value = {0};
  int s21_result = s21_round(value, result);
  ck_assert_int_eq(s21_result, CONVERT_ERROR);
}
END_TEST

START_TEST(s21_round_negative_integer) {
  s21_decimal result = {0};
  s21_decimal value = {0};
  value.bits[0] = 12;
  s21_decimal test = {{12}};
  set_sign(&value);
  int s21_result = s21_round(value, &result);
  ck_assert_int_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 1);
  ck_assert_int_eq(s21_result, OK);
}
END_TEST

START_TEST(s21_round_positive_non_integer_1) {
  s21_decimal result = {0};
  s21_decimal value = {0};
  value.bits[0] = 2463;
  s21_decimal test = {{2}};
  s21_set_power(&value, 3);
  int s21_result = s21_round(value, &result);
  ck_assert_int_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 0);
  ck_assert_int_eq(s21_result, OK);
}
END_TEST

START_TEST(s21_round_positive_non_integer_2) {
  s21_decimal result = {0};
  s21_decimal value = {0};
  value.bits[0] = 2863;
  s21_decimal test = {{3}};
  s21_set_power(&value, 3);
  int s21_result = s21_round(value, &result);
  ck_assert_int_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 0);
  ck_assert_int_eq(s21_result, OK);
}
END_TEST

START_TEST(s21_round_negative_non_integer_1) {
  s21_decimal result = {0};
  s21_decimal value = {0};
  value.bits[0] = 2463;
  s21_decimal test = {{2}};
  set_sign(&value);
  s21_set_power(&value, 3);
  int s21_result = s21_round(value, &result);
  ck_assert_int_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 1);
  ck_assert_int_eq(s21_result, OK);
}
END_TEST

START_TEST(s21_round_negative_non_integer_2) {
  s21_decimal result = {0};
  s21_decimal value = {0};
  value.bits[0] = 2753;
  s21_decimal test = {{3}};
  set_sign(&value);
  s21_set_power(&value, 3);
  int s21_result = s21_round(value, &result);
  ck_assert_int_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 1);
  ck_assert_int_eq(s21_result, OK);
}
END_TEST

START_TEST(s21_round_zero) {
  s21_decimal result = {0};
  s21_decimal value = {0};
  s21_decimal test = {0};
  int s21_result = s21_round(value, &result);
  ck_assert_int_eq(s21_result, OK);
  ck_assert_int_eq(get_sign(result), 0);
  ck_assert_int_eq(result.bits[0], test.bits[0]);
}
END_TEST

// s21_floor
START_TEST(s21_floor_positive_integer) {
  s21_decimal result = {0};
  s21_decimal value = {0};
  value.bits[0] = 7;
  s21_decimal test = {{7}};
  int s21_result = s21_floor(value, &result);
  ck_assert_int_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 0);
  ck_assert_int_eq(s21_result, OK);
}
END_TEST

START_TEST(s21_floor_null) {
  s21_decimal* result = NULL;
  s21_decimal value = {0};
  int s21_result = s21_floor(value, result);
  ck_assert_int_eq(s21_result, CONVERT_ERROR);
}
END_TEST

START_TEST(s21_floor_negative_integer) {
  s21_decimal result = {0};
  s21_decimal value = {0};
  value.bits[0] = 12;
  s21_decimal test = {{12}};
  set_sign(&value);
  int s21_result = s21_floor(value, &result);
  ck_assert_int_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 1);
  ck_assert_int_eq(s21_result, OK);
}
END_TEST

START_TEST(s21_floor_positive_non_integer) {
  s21_decimal result = {0};
  s21_decimal value = {0};
  value.bits[0] = 2463;
  s21_decimal test = {{2}};
  s21_set_power(&value, 3);
  int s21_result = s21_floor(value, &result);
  ck_assert_int_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 0);
  ck_assert_int_eq(s21_result, OK);
}
END_TEST

START_TEST(s21_floor_negative_non_integer) {
  s21_decimal result = {0};
  s21_decimal value = {0};
  value.bits[0] = 2463;
  s21_decimal test = {{3}};
  set_sign(&value);
  s21_set_power(&value, 3);
  int s21_result = s21_floor(value, &result);
  ck_assert_int_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 1);
  ck_assert_int_eq(s21_result, OK);
}
END_TEST

START_TEST(s21_floor_zero) {
  s21_decimal result = {0};
  s21_decimal value = {0};
  s21_decimal test = {0};
  int s21_result = s21_floor(value, &result);
  ck_assert_int_eq(s21_result, OK);
  ck_assert_int_eq(get_sign(result), 0);
  ck_assert_int_eq(result.bits[0], test.bits[0]);
}
END_TEST

START_TEST(s21_not_equal_null) {
  s21_decimal value = {0};
  s21_decimal test = {0};
  int res = s21_is_not_equal(value, test);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_not_equal_normal) {
  s21_decimal value = {{5}};
  s21_decimal test = {{6}};
  int res = s21_is_not_equal(value, test);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(s21_not_equal_negative) {
  s21_decimal value = {{5}};
  s21_decimal test = {{5}};
  set_sign(&value);
  int res = s21_is_not_equal(value, test);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(s21_sum_normal) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  s21_decimal test = {{1535}};

  value_1.bits[0] = 150;
  value_2.bits[0] = 35;
  s21_set_power(&value_2, 1);
  s21_add(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(s21_get_power(result), 1);
  ck_assert_int_eq(get_sign(result), 0);
}
END_TEST

START_TEST(s21_sum_both_neg) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  s21_decimal test = {{1535}};
  value_1.bits[0] = 150;
  value_2.bits[0] = 35;
  set_sign(&value_1);
  set_sign(&value_2);
  s21_set_power(&value_2, 1);
  s21_add(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(s21_get_power(result), 1);
  ck_assert_int_eq(get_sign(result), 1);
}
END_TEST

START_TEST(s21_sum_error) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  value_1.bits[0] = 4294967295;
  value_1.bits[1] = 4294967295;
  value_1.bits[2] = 4294967295;
  value_2.bits[0] = 35;

  int res = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(res, POZITIVE_INF);
  set_sign(&value_2);
  set_sign(&value_1);
  memset(&result, 0, sizeof(s21_decimal));
  res = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(res, NEGATIVE_INF);
}
END_TEST

START_TEST(s21_one_greater) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  value_1.bits[0] = 540;
  value_2.bits[0] = 560;
  s21_decimal test = {{20}};
  set_sign(&value_2);
  s21_add(value_1, value_2, &result);
  ck_assert_int_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 1);
}
END_TEST

START_TEST(s21_one_sign) {
  s21_decimal value_1 = {{150}};
  s21_decimal value_2 = {{50}};
  s21_decimal result = {0};
  s21_decimal test = {{100}};
  set_sign(&value_1);
  s21_add(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(s21_get_power(result), 0);
  ck_assert_int_eq(get_sign(result), 1);
  delete_sign(&value_1);
  set_sign(&value_2);
  memset(&result, 0, sizeof(s21_decimal));
  s21_add(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(s21_get_power(result), 0);
  ck_assert_int_eq(get_sign(result), 0);
}
END_TEST

START_TEST(s21_truncate_normal) {
  s21_decimal value_1 = {0};
  s21_decimal result = {0};
  s21_decimal test = {{150}};
  value_1.bits[0] = 150;
  s21_truncate(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 0);
}
END_TEST

START_TEST(s21_truncate_null) {
  s21_decimal value_1 = {0};
  s21_decimal result = {0};
  s21_decimal test = {{0}};
  s21_truncate(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 0);
}
END_TEST

START_TEST(s21_truncate_negative) {
  s21_decimal value_1 = {{150}};
  s21_decimal result = {0};
  s21_decimal test = {{150}};
  set_sign(&value_1);
  s21_truncate(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 1);
}
END_TEST

START_TEST(s21_truncate_pow) {
  s21_decimal value_1 = {{154345}};
  s21_decimal result = {0};
  s21_decimal test = {{154}};
  set_sign(&value_1);
  s21_set_power(&value_1, 3);
  s21_truncate(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 1);
}
END_TEST

START_TEST(s21_negate_normal) {
  s21_decimal value_1 = {{154345}};
  s21_decimal result = {0};
  s21_decimal test = {{154345}};
  set_sign(&value_1);
  s21_negate(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 0);
}
END_TEST

START_TEST(s21_negate_null) {
  s21_decimal value_1 = {{0}};
  s21_decimal result = {0};
  s21_decimal test = {0};
  s21_negate(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 1);
}
END_TEST

START_TEST(s21_negate_negative) {
  s21_decimal value_1 = {{123455}};
  s21_decimal result = {0};
  s21_decimal test = {{123455}};
  set_sign(&value_1);
  s21_negate(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 0);
}
END_TEST

START_TEST(s21_negate_pow) {
  s21_decimal value_1 = {{123455}};
  s21_decimal result = {0};
  s21_decimal test = {{123455}};
  set_sign(&value_1);
  s21_set_power(&value_1, 3);
  s21_negate(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 0);
  ck_assert_int_eq(s21_get_power(result), 3);
}
END_TEST

START_TEST(s21_decimal_float_normal) {
  s21_decimal value = {{8}};
  float a = 0;
  float b = 8.0;
  s21_from_decimal_to_float(value, &a);
  ck_assert_int_eq(get_sign(value), 0);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(s21_decimal_float_null) {
  s21_decimal value = {0};
  float a = 0.0;
  float b = 0.0;
  s21_from_decimal_to_float(value, &a);
  ck_assert_int_eq(get_sign(value), 0);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(s21_decimal_float_power) {
  s21_decimal value = {{8}};
  float a = 0.0;
  float b = -0.8;
  s21_set_power(&value, 1);
  set_sign(&value);
  s21_from_decimal_to_float(value, &a);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(s21_decimal_float_big_power) {
  s21_decimal value = {{8}};
  float a = 0.0;
  float b = -0.0000000000000000000000000008;
  s21_set_power(&value, 28);
  set_sign(&value);
  s21_from_decimal_to_float(value, &a);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(s21_decimal_float_power_max_value) {
  s21_decimal value = {0};
  value.bits[0] = 147484107;
  float a = 0.0;
  float b = -1.47484107;
  s21_set_power(&value, 8);
  set_sign(&value);
  s21_from_decimal_to_float(value, &a);
  ck_assert_float_eq_tol(a, b, 1e-6);
}
END_TEST

START_TEST(s21_decimal_float_power_max_dec) {
  s21_decimal value = {0};
  value.bits[0] = 214748;

  float a = 0.0;
  float b = -0.00000214748;
  s21_set_power(&value, 11);
  set_sign(&value);
  s21_from_decimal_to_float(value, &a);
  ck_assert_float_eq_tol(a, b, 1e-6);
}
END_TEST

START_TEST(s21_decimal_float_error) {
  s21_decimal value = {0};
  float* a = NULL;
  int res = s21_from_decimal_to_float(value, a);
  ck_assert_uint_eq(res, CONVERT_ERROR);
}
END_TEST

START_TEST(s21_float_dec_normal) {
  s21_decimal value_2 = {0};
  s21_decimal test = {0};
  float a = 0.8;
  float b = 0.0;
  s21_set_power(&test, 27);
  int res = s21_from_float_to_decimal(a, &value_2);
  s21_from_decimal_to_float(value_2, &b);
  ck_assert_uint_eq(res, 0);
  ck_assert_uint_eq(s21_get_power(value_2), s21_get_power(test));
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(s21_float_dec_negative) {
  s21_decimal value_2 = {0};
  s21_decimal test = {0};
  float a = -12.8;
  float b = 0.0;
  s21_set_power(&test, 26);
  int res = s21_from_float_to_decimal(a, &value_2);
  s21_from_decimal_to_float(value_2, &b);
  ck_assert_uint_eq(res, 0);
  ck_assert_uint_eq(s21_get_power(value_2), s21_get_power(test));
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(s21_float_dec_error) {
  s21_decimal* value_2 = NULL;
  float a = -12.8;
  int res = s21_from_float_to_decimal(a, value_2);
  ck_assert_uint_eq(res, CONVERT_ERROR);
}
END_TEST

Suite* s21_decimal_suite() {
  Suite* s;

  TCase *tc_mul, *tc_is_less, *tc_is_equal, *tc_is_less_or_equal,
      *tc_decimal_float, *tc_sub, *tc_div, *tc_mod, *tc_int_dec, *tc_floor,
      *tc_not_equal, *tc_sum, *tc_truncate, *tc_negate, *tc_round,
      *tc_is_greater, *tc_is_greater_or_equal, *tc_float_dec;

  s = suite_create("s21_decimal");

  tc_mul = tcase_create("s21_mul");
  tcase_add_test(tc_mul, s21_mul_value_1_is_one);
  tcase_add_test(tc_mul, s21_mul_value_2_is_one);
  tcase_add_test(tc_mul, s21_mul_value_1_is_zero);
  tcase_add_test(tc_mul, s21_mul_value_2_is_zero);
  tcase_add_test(tc_mul, s21_mul_max);
  tcase_add_test(tc_mul, s21_mul_big_power);
  tcase_add_test(tc_mul, s21_mul_big_over);
  tcase_add_test(tc_mul, s21_mul_norm);
  tcase_add_test(tc_mul, s21_mul_big_negative_over);
  tcase_add_test(tc_mul, s21_mul_value_1_is_minus);
  tcase_add_test(tc_mul, s21_mul_value_2_is_minus);
  tcase_add_test(tc_mul, s21_mul_value_1_is_zero_minus);
  tcase_add_test(tc_mul, s21_mul_value_2_is_zero_minus);
  tcase_add_test(tc_mul, s21_mul_value_1_2_is_minus);
  tcase_add_test(tc_mul, s21_mul_max_1);
  tcase_add_test(tc_mul, s21_mul_max_2);
  tcase_add_test(tc_mul, s21_mul_max_3);
  suite_add_tcase(s, tc_mul);

  tc_float_dec = tcase_create("s21_float_dec");
  tcase_add_test(tc_float_dec, s21_float_dec_normal);
  tcase_add_test(tc_float_dec, s21_float_dec_negative);
  tcase_add_test(tc_float_dec, s21_float_dec_error);
  suite_add_tcase(s, tc_float_dec);

  tc_decimal_float = tcase_create("s21_decimal_float");
  tcase_add_test(tc_decimal_float, s21_decimal_float_normal);
  tcase_add_test(tc_decimal_float, s21_decimal_float_null);
  tcase_add_test(tc_decimal_float, s21_decimal_float_power);
  tcase_add_test(tc_decimal_float, s21_decimal_float_big_power);
  tcase_add_test(tc_decimal_float, s21_decimal_float_power_max_value);
  tcase_add_test(tc_decimal_float, s21_decimal_float_power_max_dec);
  tcase_add_test(tc_decimal_float, s21_decimal_float_error);
  suite_add_tcase(s, tc_decimal_float);

  tc_negate = tcase_create("s21_negate");
  tcase_add_test(tc_negate, s21_negate_normal);
  tcase_add_test(tc_negate, s21_negate_null);
  tcase_add_test(tc_negate, s21_negate_negative);
  tcase_add_test(tc_negate, s21_negate_pow);
  suite_add_tcase(s, tc_negate);

  tc_truncate = tcase_create("s21_truncate");
  tcase_add_test(tc_truncate, s21_truncate_normal);
  tcase_add_test(tc_truncate, s21_truncate_null);
  tcase_add_test(tc_truncate, s21_truncate_negative);
  tcase_add_test(tc_truncate, s21_truncate_pow);
  suite_add_tcase(s, tc_truncate);

  tc_is_less = tcase_create("s21_is_less");
  tcase_add_test(tc_is_less, s21_is_less_null);
  tcase_add_test(tc_is_less, s21_is_less_normal);
  tcase_add_test(tc_is_less, s21_is_less_negative);
  tcase_add_test(tc_is_less, s21_is_less_pow);
  suite_add_tcase(s, tc_is_less);

  tc_is_greater = tcase_create("s21_is_greater");
  tcase_add_test(tc_is_greater, s21_is_greater_null);
  tcase_add_test(tc_is_greater, s21_is_greater_normal);
  tcase_add_test(tc_is_greater, s21_is_greater_negative);
  tcase_add_test(tc_is_greater, s21_is_greater_pow);
  tcase_add_test(tc_is_greater, s21_is_greater_two_negative);
  suite_add_tcase(s, tc_is_greater);

  tc_not_equal = tcase_create("s21_not_equal");
  tcase_add_test(tc_not_equal, s21_not_equal_null);
  tcase_add_test(tc_not_equal, s21_not_equal_normal);
  tcase_add_test(tc_not_equal, s21_not_equal_negative);
  suite_add_tcase(s, tc_not_equal);

  tc_is_equal = tcase_create("s21_is_equal");
  tcase_add_test(tc_is_equal, isEqual);
  tcase_add_test(tc_is_equal, isEqual1);
  suite_add_tcase(s, tc_is_equal);

  tc_is_less_or_equal = tcase_create("s21_is_less_or_equal");
  tcase_add_test(tc_is_less_or_equal, s21_is_less_or_equal_normal);
  tcase_add_test(tc_is_less_or_equal, s21_is_less_or_equal_with_sign);
  suite_add_tcase(s, tc_is_less_or_equal);

  tc_is_greater_or_equal = tcase_create("s21_is_greater_or_equal");
  tcase_add_test(tc_is_greater_or_equal, s21_is_greater_or_equal_normal);
  tcase_add_test(tc_is_greater_or_equal, s21_is_greater_or_equal_with_sign);
  suite_add_tcase(s, tc_is_greater_or_equal);

  tc_int_dec = tcase_create("s21_int_decimal");
  tcase_add_test(tc_int_dec, s21_int_and_decimal_nul);
  tcase_add_test(tc_int_dec, s21_int_and_decimal_max);
  tcase_add_test(tc_int_dec, s21_int_and_decimal_whith_pow);
  tcase_add_test(tc_int_dec, s21_int_and_decimal_big_pow);
  tcase_add_test(tc_int_dec, s21_int_and_decimal_error);
  tcase_add_test(tc_int_dec, s21_int_and_decimal_sign);
  suite_add_tcase(s, tc_int_dec);

  tc_sub = tcase_create("sub");
  tcase_add_test(tc_sub, s21_sub_normal);
  tcase_add_test(tc_sub, s21_sub_one_sign);
  tcase_add_test(tc_sub, s21_sub_two_sign);
  tcase_add_test(tc_sub, s21_sub_inf);
  suite_add_tcase(s, tc_sub);

  tc_sum = tcase_create("sum");
  tcase_add_test(tc_sum, s21_sum_normal);
  tcase_add_test(tc_sum, s21_sum_both_neg);
  tcase_add_test(tc_sum, s21_one_sign);
  tcase_add_test(tc_sum, s21_sum_error);
  tcase_add_test(tc_sum, s21_one_greater);
  suite_add_tcase(s, tc_sum);

  tc_div = tcase_create("div");
  tcase_add_test(tc_div, s21_div_normal);
  tcase_add_test(tc_div, s21_div_scale);
  tcase_add_test(tc_div, s21_div_zero);
  tcase_add_test(tc_div, s21_div_negative);
  tcase_add_test(tc_div, s21_div_normalize);
  tcase_add_test(tc_div, s21_div_max);
  tcase_add_test(tc_div, s21_div_pow_norm);
  tcase_add_test(tc_div, s21_div_pi);
  tcase_add_test(tc_div, s21_div_pos_over);
  tcase_add_test(tc_div, s21_div_neg_over);
  tcase_add_test(tc_div, s21_div_one);
  tcase_add_test(tc_div, s21_div_min_pow);
  tcase_add_test(tc_div, s21_div_min_pow_second_dec);
  tcase_add_test(tc_div, s21_div_pow_small);
  suite_add_tcase(s, tc_div);

  tc_mod = tcase_create("mod");
  tcase_add_test(tc_mod, s21_mod_max_dec);
  tcase_add_test(tc_mod, s21_mod_max_dec_and_two);
  tcase_add_test(tc_mod, s21_mod_max_dec_and_biguint);
  tcase_add_test(tc_mod, s21_mod_dec_with_pow);
  tcase_add_test(tc_mod, s21_mod_dec_revers);
  tcase_add_test(tc_mod, s21_mod_dec_error);
  tcase_add_test(tc_mod, s21_mod_sign);
  tcase_add_test(tc_mod, s21_mod_over);
  tcase_add_test(tc_mod, s21_mod_over_norm);
  suite_add_tcase(s, tc_mod);

  tc_floor = tcase_create("s21_floor");
  tcase_add_test(tc_floor, s21_floor_positive_integer);
  tcase_add_test(tc_floor, s21_floor_negative_integer);
  tcase_add_test(tc_floor, s21_floor_positive_non_integer);
  tcase_add_test(tc_floor, s21_floor_negative_non_integer);
  tcase_add_test(tc_floor, s21_floor_zero);
  tcase_add_test(tc_floor, s21_floor_null);
  suite_add_tcase(s, tc_floor);

  tc_round = tcase_create("s21_round");
  tcase_add_test(tc_round, s21_round_positive_integer);
  tcase_add_test(tc_round, s21_round_negative_integer);
  tcase_add_test(tc_round, s21_round_positive_non_integer_1);
  tcase_add_test(tc_round, s21_round_positive_non_integer_2);
  tcase_add_test(tc_round, s21_round_negative_non_integer_1);
  tcase_add_test(tc_round, s21_round_negative_non_integer_2);
  tcase_add_test(tc_round, s21_round_zero);
  tcase_add_test(tc_round, s21_round_null);
  suite_add_tcase(s, tc_round);
  return s;
}

int main() {
  int no_failed = 0;
  Suite* s;
  SRunner* runner;

  s = s21_decimal_suite();
  runner = srunner_create(s);

  srunner_run_all(runner, CK_NORMAL);
  no_failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
