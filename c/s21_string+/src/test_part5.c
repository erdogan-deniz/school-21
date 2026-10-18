// Tests: to_upper, to_lower, trim, insert.
#include "s21_string_test.h"

// to_lower ->
START_TEST(to_lower_test1) {
  char str[] = "ShLePa V TaZ1Ke?";
  char expected[] = "shlepa v taz1ke?";
  char *got = s21_to_lower(str);
  ck_assert_str_eq(got, expected);
  if (got) free(got);
}
END_TEST

START_TEST(to_lower_test2) {
  char str[] = "123456789Q";
  char expected[] = "123456789q";
  char *got = s21_to_lower(str);
  ck_assert_str_eq(got, expected);
  if (got) free(got);
}
END_TEST

START_TEST(to_lower_test3) {
  char str[] = "Space created";
  char expected[] = "space created";
  char *got = s21_to_lower(str);
  ck_assert_str_eq(got, expected);
  if (got) free(got);
}
END_TEST

START_TEST(to_lower_test4) {
  char str[] = "";
  char expected[] = "";
  char *got = s21_to_lower(str);
  ck_assert_str_eq(got, expected);
  if (got) free(got);
}
END_TEST

START_TEST(to_lower_test5) {
  char str[] = "";
  char expected[] = "";
  char *got = s21_to_lower(str);
  ck_assert_str_eq(got, expected);
  if (got) free(got);
}
END_TEST
// to_lower <-

// trim ->
START_TEST(trim_all_empty) {
  char str[] = "";
  char trim_ch[] = "";
  char *expected = "";
  char *got = s21_trim(str, trim_ch);
  ck_assert_pstr_eq(got, expected);
  if (got) free(got);
}
END_TEST

START_TEST(trim_str_empty) {
  char str[] = "";
  char trim_ch[] = "+!0-aeoi2o3i23iuhuhh3O*YADyagsduyoaweq213";
  char expected[] = "";
  char *got = s21_trim(str, trim_ch);
  ck_assert_str_eq(got, expected);
  if (got) free(got);
}
END_TEST

START_TEST(trim_empty) {
  char str[] = "+!0-aeoi2o3i23iuhuhh3O*YADyagsduyoaweq213";
  char trim_ch[] = "";
  char *expected = "+!0-aeoi2o3i23iuhuhh3O*YADyagsduyoaweq213";
  char *got = s21_trim(str, trim_ch);
  ck_assert_str_eq(got, expected);
  if (got) free(got);
}
END_TEST

START_TEST(trim_and_str_eq) {
  char str[] = "+!0-aeoi2o3i23iuhuhh3O*YADyagsduyoaweq213";
  char trim_ch[] = "+!0-aeoi2o3i23iuhuhh3O*YADyagsduyoaweq213";
  char expected[] = "";
  char *got = s21_trim(str, trim_ch);
  ck_assert_str_eq(got, expected);
  if (got) free(got);
}
END_TEST

START_TEST(trim_test1) {
  char str[] = "+!!++Abo+ba++00";
  char trim_ch[] = "+!0-";
  char expected[] = "Abo+ba";
  char *got = (char *)s21_trim(str, trim_ch);
  ck_assert_str_eq(got, expected);
  if (got) free(got);
}
END_TEST

START_TEST(trim_test2) {
  char str[] = "Ab000cd0";
  char trim_ch[] = "003";
  char expected[] = "Ab000cd";
  char *got = s21_trim(str, trim_ch);
  ck_assert_str_eq(got, expected);
  if (got) free(got);
}
END_TEST

START_TEST(trim_test3) {
  char str[] = "DoNotTouch";
  char trim_ch[] = "Not";
  char expected[] = "DoNotTouch";
  char *got = s21_trim(str, trim_ch);
  ck_assert_str_eq(got, expected);
  if (got) free(got);
}
END_TEST

START_TEST(trim_test4) {
  char str[] = "&* !!sc21 * **";
  char trim_ch[] = "&!* ";
  char expected[] = "sc21";
  char *got = s21_trim(str, trim_ch);
  ck_assert_str_eq(got, expected);
  if (got) free(got);
}
END_TEST

START_TEST(trim_test5) {
  char str[] = " Good morning!    ";
  char trim_ch[] = " ";
  char expected[] = "Good morning!";
  char *got = s21_trim(str, trim_ch);
  ck_assert_str_eq(got, expected);
  if (got) free(got);
}
END_TEST

START_TEST(trim_empty_spaces) {
  char str[] = "        abc         ";
  char trim_ch[] = "";
  char *expected = "abc";
  char *got = s21_trim(str, trim_ch);
  ck_assert_pstr_eq(got, expected);
  if (got) free(got);
}
END_TEST

START_TEST(trim_null_ptr_trim_chars) {
  char str[] = "        abc         ";
  char *trim_ch = s21_NULL;
  char expected[] = "abc";
  char *got = s21_trim(str, trim_ch);
  ck_assert_str_eq(got, expected);
  if (got) free(got);
}
END_TEST
// trim <-

// to_upper ->
START_TEST(to_upper_test1) {
  char str[] = "good job";
  char expected[] = "GOOD JOB";
  char *got = s21_to_upper(str);
  ck_assert_str_eq(got, expected);
  if (got) free(got);
}
END_TEST

START_TEST(to_upper_test2) {
  char str[] = "empty";
  char expected[] = "EMPTY";
  char *got = s21_to_upper(str);
  ck_assert_str_eq(got, expected);
  if (got) free(got);
}
END_TEST

START_TEST(to_upper_test3) {
  char str[] = "1+1*1";
  char expected[] = "1+1*1";
  char *got = s21_to_upper(str);
  ck_assert_str_eq(got, expected);
  if (got) free(got);
}
END_TEST

START_TEST(to_upper_test4) {
  char str[] = " ";
  char expected[] = " ";
  char *got = s21_to_upper(str);
  ck_assert_str_eq(got, expected);
  if (got) free(got);
}
END_TEST

START_TEST(to_upper_test5) {
  char str[] = "";
  char expected[] = "";
  char *got = s21_to_upper(str);
  ck_assert_str_eq(got, expected);
  if (got) free(got);
}
END_TEST
// to_upper <-

// insert ->
START_TEST(insert_test1) {
  char str[] = "Shlepa";
  char src[] = "I love my . He is very kind!";
  s21_size_t index = 10;
  char expected[] = "I love my Shlepa. He is very kind!";
  char *got = (char *)s21_insert(src, str, index);
  ck_assert_str_eq(got, expected);
  if (got) free(got);
}
END_TEST

START_TEST(insert_test2) {
  char str[] = "Hello, ";
  char src[] = "Aboba!";
  s21_size_t index = 0;
  char expected[] = "Hello, Aboba!";
  char *got = (char *)s21_insert(src, str, index);
  ck_assert_str_eq(got, expected);
  if (got) free(got);
}
END_TEST

START_TEST(insert_test3) {
  char str[] = "";
  char src[] = "";
  s21_size_t index = 100;
  char *expected = s21_NULL;
  char *got = (char *)s21_insert(src, str, index);
  ck_assert_pstr_eq(got, expected);
  if (got) free(got);
}
END_TEST

START_TEST(insert_test4) {
  char *src = s21_NULL;
  char *str = s21_NULL;
  s21_size_t index = 100;
  char *expected = s21_NULL;
  char *got = (char *)s21_insert(src, str, index);
  ck_assert_ptr_eq(got, expected);
  if (got) free(got);
}
END_TEST

START_TEST(insert_test5) {
  char str[] = "Monkey";
  char src[] = "Space  ";
  s21_size_t index = 6;
  char expected[] = "Space Monkey ";
  char *got = (char *)s21_insert(src, str, index);
  ck_assert_str_eq(got, expected);
  if (got) free(got);
}
END_TEST

// insert <-

Suite *suite_part5(void) {
  Suite *s = suite_create("part5");
  TCase *tc = tcase_create("part5_tc");

  tcase_add_test(tc, to_lower_test1);
  tcase_add_test(tc, to_lower_test2);
  tcase_add_test(tc, to_lower_test3);
  tcase_add_test(tc, to_lower_test4);
  tcase_add_test(tc, to_lower_test5);
  tcase_add_test(tc, trim_all_empty);
  tcase_add_test(tc, trim_str_empty);
  tcase_add_test(tc, trim_empty);
  tcase_add_test(tc, trim_and_str_eq);
  tcase_add_test(tc, trim_test1);
  tcase_add_test(tc, trim_test2);
  tcase_add_test(tc, trim_test3);
  tcase_add_test(tc, trim_test4);
  tcase_add_test(tc, trim_test5);
  tcase_add_test(tc, trim_empty_spaces);
  tcase_add_test(tc, trim_null_ptr_trim_chars);
  tcase_add_test(tc, to_upper_test1);
  tcase_add_test(tc, to_upper_test2);
  tcase_add_test(tc, to_upper_test3);
  tcase_add_test(tc, to_upper_test4);
  tcase_add_test(tc, to_upper_test5);
  tcase_add_test(tc, insert_test1);
  tcase_add_test(tc, insert_test2);
  tcase_add_test(tc, insert_test3);
  tcase_add_test(tc, insert_test4);
  tcase_add_test(tc, insert_test5);

  suite_add_tcase(s, tc);
  return s;
}
