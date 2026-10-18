// Tests: string functions.
#include "s21_string_test.h"

/* -----===== PART-2 =====----- */
/* -----===== START =====----- */
// strlen ->
START_TEST(strlen_empty) {
  char src[] = "";
  ck_assert_int_eq(s21_strlen(src), strlen(src));
}
END_TEST

START_TEST(strlen_abosal) {
  char src[] = "abosal";
  ck_assert_int_eq(s21_strlen(src), strlen(src));
}
END_TEST

START_TEST(strlen_num) {
  char src[] = "987623456124678";
  ck_assert_int_eq(s21_strlen(src), strlen(src));
}
END_TEST

START_TEST(strlen_string) {
  char src[] =
      "987623456124678qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM";
  ck_assert_int_eq(s21_strlen(src), strlen(src));
}
END_TEST

START_TEST(strlen_abosal_no_dal) {
  char src[] = "abosal\0no_dal";
  ck_assert_int_eq(s21_strlen(src), strlen(src));
}
END_TEST

START_TEST(strlen_dai_mne_pen) {
  char src[] = "dai_mne_pen(321321)...123...123";
  ck_assert_int_eq(s21_strlen(src), strlen(src));
}
END_TEST

START_TEST(strlen_Floppy_disk) {
  char src[] = "Floppy_disk";
  ck_assert_int_eq(s21_strlen(src), strlen(src));
}
END_TEST

START_TEST(strlen_Russky_kot_Shlepa) {
  char src[] = "Russky_kot_Shlepa";
  ck_assert_int_eq(s21_strlen(src), strlen(src));
}
END_TEST

START_TEST(strlen_kot_Vasily) {
  char src[] = "kot Vasily";
  ck_assert_int_eq(s21_strlen(src), strlen(src));
}
END_TEST

START_TEST(strlen_floppa) {
  char src[] = "floppa";
  ck_assert_int_eq(s21_strlen(src), strlen(src));
}
END_TEST
// strlen <-

// strncat ->
START_TEST(strncat_all_empty) {
  char src[] = "";
  char res[] = "";
  char expected[] = "";
  s21_size_t n_byte = 0;
  s21_strncat(res, src, n_byte);
  strncat(expected, src, n_byte);
  ck_assert_mem_ge(res, expected, n_byte);
}
END_TEST

START_TEST(strncat_zero_byte) {
  char src[] = "abosal";
  char res[10] = "";
  char expected[10] = "";
  s21_size_t n_byte = 0;
  s21_strncat(res, src, n_byte);
  strncat(expected, src, n_byte);
  ck_assert_mem_ge(res, expected, n_byte);
}
END_TEST

START_TEST(strncat_empty_src) {
  char src[] = "";
  char res[10] = "cd";
  char expected[10] = "cd";
  s21_size_t n_byte = 0;
  s21_strncat(res, src, n_byte);
  strncat(expected, src, n_byte);
  ck_assert_mem_ge(res, expected, n_byte);
}
END_TEST

START_TEST(strncat_cd_abosa) {
  char src[] = "abosal";
  char res[10] = "cd";
  char expected[10] = "cd";
  s21_size_t n_byte = 5;
  s21_strncat(res, src, n_byte);
  strncat(expected, src, n_byte);
  ck_assert_mem_ge(res, expected, n_byte);
}
END_TEST

START_TEST(strncat_string) {
  char src[] = "abosal";
  char res[25] = "koleka";
  char expected[25] = "koleka";
  s21_size_t n_byte = 6;
  s21_strncat(res, src, n_byte);
  strncat(expected, src, n_byte);
  ck_assert_mem_ge(res, expected, n_byte);
}
END_TEST

START_TEST(strncat_BIGFLOPPA) {
  char src[] = "BIGFLOPPA";
  char res[25] = "BIGFLOPPA";
  char expected[25] = "BIGFLOPPA";
  s21_size_t n_byte = 5;
  s21_strncat(res, src, n_byte);
  strncat(expected, src, n_byte);
  ck_assert_mem_ge(res, expected, n_byte);
}
END_TEST

START_TEST(strncat_BIGFLOPPA2) {
  char src[] = "BIGFLOPPA";
  char res[25] = "BIGFLOPPA";
  char expected[25] = "BIGFLOPPA";
  s21_size_t n_byte = 0;
  s21_strncat(res, src, n_byte);
  strncat(expected, src, n_byte);
  ck_assert_mem_ge(res, expected, n_byte);
}
END_TEST

START_TEST(strncat_BIGFLOPPA3) {
  char src[] = "BIGFLOPPA";
  char res[25] = "BIGFLOPPA";
  char expected[25] = "BIGFLOPPA";
  s21_size_t n_byte = 1;
  s21_strncat(res, src, n_byte);
  strncat(expected, src, n_byte);
  ck_assert_mem_ge(res, expected, n_byte);
}
END_TEST

START_TEST(strncat_BIGFLOPPA4) {
  char src[] = "BIGFLOPPA";
  char res[25] = "BIGFLOPPA";
  char expected[25] = "BIGFLOPPA";
  s21_size_t n_byte = 10;
  s21_strncat(res, src, n_byte);
  strncat(expected, src, n_byte);
  ck_assert_mem_ge(res, expected, n_byte);
}
END_TEST

START_TEST(strncat_zero_char) {
  char src[] = "\0";
  char res[25] = "BIGFLOPPA";
  char expected[25] = "BIGFLOPPA";
  s21_size_t n_byte = 1;
  s21_strncat(res, src, n_byte);
  strncat(expected, src, n_byte);
  ck_assert_mem_ge(res, expected, n_byte);
}
END_TEST
// strncat <-

// strncmp ->
START_TEST(strncmp_empty) {
  char str1[] = "";
  char str2[] = "";
  s21_size_t n_byte = 0;
  int got = s21_strncmp(str1, str2, n_byte);
  int expected = strncmp(str1, str2, n_byte);
  if (got > 1) got = 1;
  if (expected > 1) expected = 1;
  if (got < -1) got = -1;
  if (expected < -1) expected = -1;
  ck_assert_int_eq(got, expected);
}
END_TEST

START_TEST(strncmp_floppa_) {
  char str1[] = "floppa";
  char str2[] = "";
  s21_size_t n_byte = 0;
  int got = s21_strncmp(str1, str2, n_byte);
  int expected = strncmp(str1, str2, n_byte);
  if (got > 1) got = 1;
  if (expected > 1) expected = 1;
  if (got < -1) got = -1;
  if (expected < -1) expected = -1;
  ck_assert_int_eq(got, expected);
}
END_TEST

START_TEST(strncmp__floppa) {
  char str1[] = "";
  char str2[] = "floppa";
  s21_size_t n_byte = 0;
  int got = s21_strncmp(str1, str2, n_byte);
  int expected = strncmp(str1, str2, n_byte);
  if (got > 1) got = 1;
  if (expected > 1) expected = 1;
  if (got < -1) got = -1;
  if (expected < -1) expected = -1;
  ck_assert_int_eq(got, expected);
}
END_TEST

START_TEST(strncmp_floppa_floppa) {
  char str1[] = "floppa";
  char str2[] = "floppa";
  s21_size_t n_byte = 6;
  int got = s21_strncmp(str1, str2, n_byte);
  int expected = strncmp(str1, str2, n_byte);
  if (got > 1) got = 1;
  if (expected > 1) expected = 1;
  if (got < -1) got = -1;
  if (expected < -1) expected = -1;
  ck_assert_int_eq(got, expected);
}
END_TEST

START_TEST(strncmp_floppa_floppa_zero_byte) {
  char str1[] = "floppabazbazkotya";
  char str2[] = "floppabaz";
  s21_size_t n_byte = 10;
  int got = s21_strncmp(str1, str2, n_byte);
  int expected = strncmp(str1, str2, n_byte);
  if (got > 1) got = 1;
  if (expected > 1) expected = 1;
  if (got < -1) got = -1;
  if (expected < -1) expected = -1;
  ck_assert_int_eq(got, expected);
}
END_TEST

START_TEST(strncmp_floppa_floppa_one_byte) {
  char str1[] = "floppa";
  char str2[] = "floppa";
  s21_size_t n_byte = 1;
  int got = s21_strncmp(str1, str2, n_byte);
  int expected = strncmp(str1, str2, n_byte);
  if (got > 1) got = 1;
  if (expected > 1) expected = 1;
  if (got < -1) got = -1;
  if (expected < -1) expected = -1;
  ck_assert_int_eq(got, expected);
}
END_TEST
// strncmp <-

// strrchr ->
START_TEST(strrchr_empty) {
  char str1[] = "";
  char str2 = '\0';
  ck_assert_pstr_eq(s21_strrchr(str1, str2), strrchr(str1, str2));
}
END_TEST

START_TEST(strrchr_floppy_) {
  char str1[] = "floppy";
  char str2 = '\0';
  ck_assert_pstr_eq(s21_strrchr(str1, str2), strrchr(str1, str2));
}
END_TEST

START_TEST(strrchr__floppy) {
  char str1[] = "";
  char str2 = 'f';
  ck_assert_pstr_eq(s21_strrchr(str1, str2), strrchr(str1, str2));
}
END_TEST

START_TEST(strrchr_poki_doki_o) {
  char str1[] = "poki doki";
  char str2 = 'o';
  ck_assert_pstr_eq(s21_strrchr(str1, str2), strrchr(str1, str2));
}
END_TEST

START_TEST(strrchr_poki_doki_i) {
  char str1[] = "poki doki";
  char str2 = 'i';
  ck_assert_pstr_eq(s21_strrchr(str1, str2), strrchr(str1, str2));
}
END_TEST

START_TEST(strrchr_poki_doki_p) {
  char str1[] = "poki p dokip";
  char str2 = 'p';
  ck_assert_pstr_eq(s21_strrchr(str1, str2), strrchr(str1, str2));
}
END_TEST

START_TEST(strrchr_find_big_P) {
  char str1[] = "ppPpppppppppP";
  char str2 = 'P';
  ck_assert_pstr_eq(s21_strrchr(str1, str2), strrchr(str1, str2));
}
END_TEST

START_TEST(strrchr_find_zero) {
  char str1[] = "123456789";
  char str2 = '0';
  ck_assert_pstr_eq(s21_strrchr(str1, str2), strrchr(str1, str2));
}
END_TEST
// strrchr <-

// strpbrk ->
START_TEST(strpbrk_empty) {
  char str1[] = "";
  char str2[] = "";
  ck_assert_pstr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

START_TEST(strpbrk_floppy_) {
  char str1[] = "floppy";
  char str2[] = "";
  ck_assert_pstr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

START_TEST(strpbrk__floppy) {
  char str1[] = "";
  char str2[] = "floppy";
  ck_assert_pstr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

START_TEST(strpbrk_poki_doki_o) {
  char str1[] = "poki doki";
  char str2[] = "o";
  ck_assert_pstr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

START_TEST(strpbrk_poki_doki_i) {
  char str1[] = "poki doki";
  char str2[] = "i";
  ck_assert_pstr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

START_TEST(strpbrk_poki_doki_p) {
  char str1[] = "poki doki";
  char str2[] = "p";
  ck_assert_pstr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

START_TEST(strpbrk_find_big_P) {
  char str1[] = "ppppppppppppP";
  char str2[] = "P";
  ck_assert_pstr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

START_TEST(strpbrk_find_zero) {
  char str1[] = "ppppppppppppP";
  char str2[] = "\0";
  ck_assert_pstr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST
// strpbrk <-

// strspn ->
START_TEST(strspn_empty) {
  char src[] = "";
  char res[] = "";
  ck_assert_int_eq(s21_strspn(res, src), strspn(res, src));
}
END_TEST

START_TEST(strspn_gora_) {
  char src[] = "gora";
  char res[] = "";
  ck_assert_int_eq(s21_strspn(res, src), strspn(res, src));
}
END_TEST

START_TEST(strspn__gora) {
  char src[] = "";
  char res[] = "gora";
  ck_assert_int_eq(s21_strspn(res, src), strspn(res, src));
}
END_TEST

START_TEST(strspn_any_register) {
  char src[] = "gora";
  char res[] = "gOra";
  ck_assert_int_eq(s21_strspn(res, src), strspn(res, src));
}
END_TEST

START_TEST(strspn_num_num) {
  char src[] = "123";
  char res[] = "123";
  ck_assert_int_eq(s21_strspn(res, src), strspn(res, src));
}
END_TEST

START_TEST(strspn_long_num_num) {
  char src[] = "12345";
  char res[] = "123";
  ck_assert_int_eq(s21_strspn(res, src), strspn(res, src));
}
END_TEST

START_TEST(strspn_num_long_num) {
  char src[] = "123";
  char res[] = "12345";
  ck_assert_int_eq(s21_strspn(res, src), strspn(res, src));
}
END_TEST

START_TEST(strspn_any_num) {
  char src[] = "1234567890";
  char res[] = "0987654321";
  ck_assert_int_eq(s21_strspn(res, src), strspn(res, src));
}
END_TEST

START_TEST(strspn_num_with_letter) {
  char src[] = "1A2A3A4A5A";
  char res[] = "123";
  ck_assert_int_eq(s21_strspn(res, src), strspn(res, src));
}
END_TEST

START_TEST(strspn_num_with_letter2) {
  char src[] = "a1aaa23aaa41235";
  char res[] = "123";
  ck_assert_int_eq(s21_strspn(res, src), strspn(res, src));
}
END_TEST

START_TEST(strspn_basic_test) {
  char src[] = "absD";
  char res[] = "aD";
  ck_assert_int_eq(s21_strspn(res, src), strspn(res, src));
}
END_TEST

START_TEST(strspn_any_sim) {
  char src[] = "32ASDASDPare[0g9jf m07y271234567890";
  char res[] = "0987654321";
  ck_assert_int_eq(s21_strspn(res, src), strspn(res, src));
}
END_TEST

START_TEST(strspn_upper_letter) {
  char src[] = "32ASDASDPare[0g9jf m07y271234567890";
  char res[] = "1234567890QWERTYUIOPASDFGHJKLZXCVBNM";
  ck_assert_int_eq(s21_strspn(res, src), strspn(res, src));
}
END_TEST

START_TEST(strspn_lower_letter) {
  char src[] = "32jersASDASDPare[0g9jf m07y271234567890";
  char res[] = "1234567890qwertyuiopasdfghjklczxcvbnm";
  ck_assert_int_eq(s21_strspn(res, src), strspn(res, src));
}
END_TEST

START_TEST(strspn_not_uniq_sim) {
  char src[] =
      "333333333333333333333333333333333333333333333333333333333333333333333333"
      "33333333333333";
  char res[] =
      "111111111111111111111111111111111111111111111111111111111111111111111111"
      "11111111111113";
  ck_assert_int_eq(s21_strspn(res, src), strspn(res, src));
}
END_TEST
// strspn <-

// strerror ->

START_TEST(strerror_1) {
  for (int i = -123; i < 0; i++) {
    ck_assert_str_eq(s21_strerror(i), strerror(i));
  }
  for (int i = 0; i <= 106; i++) {
    ck_assert_str_eq(s21_strerror(i), strerror(i));
  }
  for (int i = 107; i <= 234; i++) {
    ck_assert_str_eq(s21_strerror(i), strerror(i));
  }
}

END_TEST

// strerror <-

// strstr ->
START_TEST(strstr_empty_string_haystack_and_needle) {
  char haystack[] = "";
  char needle[] = "";
  ck_assert_pstr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(strstr_empty_string_haystack) {
  char haystack[] = "";
  char needle[] = "jho1faQsdkjnSa3aefwf8hiuJafeHioj";
  ck_assert_pstr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(strstr_empty_string_needle) {
  char haystack[] = "safQhilufas7MaSef2345wknwefnkjHawe2fhilu";
  char needle[] = "";
  ck_assert_pstr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(strstr_toxic_test) {
  char haystack[] = "You are toxic!";
  char needle[] = "toxic";
  ck_assert_pstr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(strstr_not_word_in_haystack) {
  char haystack[] = "There is no right word in this test!";
  char needle[] = "NOT";
  ck_assert_pstr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(strstr_words_with_any_register) {
  char haystack[] = "AbOBosNyTSa";
  char needle[] = "aBoboSNYTsa";
  ck_assert_pstr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(strstr_repeated_words) {
  char haystack[] = "AD AD AD";
  char needle[] = "AD";
  ck_assert_pstr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(strstr_word_at_end) {
  char haystack[] = "22 321 123";
  char needle[] = "123";
  ck_assert_pstr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(strstr_one_simbol_in_needle_and_haystack) {
  char haystack[] = "1";
  char needle[] = "1";
  ck_assert_pstr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(strstr_one_simbol_in_needle) {
  char haystack[] =
      "13625523478437263475984675342345sdghyftrg freshtsyASFWEt wEafe";
  char needle[] = " ";
  ck_assert_pstr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(strstr_one_simbol_in_haystack) {
  char haystack[] = "-";
  char needle[] = "1234567890qwertyuiopasdfghjk-";
  ck_assert_pstr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST
// strstr <-

// // strtok ->
START_TEST(strtok_correct_token_string) {
  char str1[] = "Aboba++Floppa_! Kotya====!Shleppa";
  char str2[] = "Aboba++Floppa_! Kotya====!Shleppa";
  const char delims[] = "+_! =";
  char *got = s21_strtok(str1, delims);
  char *expected = strtok(str2, delims);
  ck_assert_uint_eq(s21_strlen(got), s21_strlen(expected));
  ck_assert_str_eq(got, expected);
  while (got && expected) {
    got = s21_strtok(s21_NULL, delims);
    expected = strtok(s21_NULL, delims);
    if (got || expected) {
      ck_assert_str_eq(got, expected);
    } else {
      ck_assert_ptr_null(got);
      ck_assert_ptr_null(expected);
    }
  }
}
END_TEST

START_TEST(strtok_hard_token_string) {
  char str1[] = "++Aboba++Floppa_! Kotya===!Shleppa+++ A +";
  char str2[] = "++Aboba++Floppa_! Kotya===!Shleppa+++ A +";
  const char delims[] = "+_! =";
  char *got = s21_strtok(str1, delims);
  char *expected = strtok(str2, delims);
  ck_assert_uint_eq(s21_strlen(got), s21_strlen(expected));
  ck_assert_str_eq(got, expected);
  while (got && expected) {
    got = s21_strtok(s21_NULL, delims);
    expected = strtok(s21_NULL, delims);
    if (got || expected) {
      ck_assert_str_eq(got, expected);
    } else {
      ck_assert_ptr_null(got);
      ck_assert_ptr_null(expected);
    }
  }
}
END_TEST

START_TEST(strtok_unary_delimiters) {
  char str1[] = "Aboba+Anuroba_Floppa!Kotya_Kekus";
  char str2[] = "Aboba+Anuroba_Floppa!Kotya_Kekus";
  const char delims[] = "+_! =";
  char *got = s21_strtok(str1, delims);
  char *expected = strtok(str2, delims);
  ck_assert_uint_eq(s21_strlen(got), s21_strlen(expected));
  ck_assert_str_eq(got, expected);
  while (got && expected) {
    got = s21_strtok(s21_NULL, delims);
    expected = strtok(s21_NULL, delims);
    if (got || expected) {
      ck_assert_str_eq(got, expected);
    } else {
      ck_assert_ptr_null(got);
      ck_assert_ptr_null(expected);
    }
  }
}
END_TEST

START_TEST(strtok_no_delims) {
  char str1[] = "AbobaHasNoDelims";
  char str2[] = "AbobaHasNoDelims";
  const char delims[] = "+_! =";
  char *got = s21_strtok(str1, delims);
  char *expected = strtok(str2, delims);
  ck_assert_uint_eq(s21_strlen(got), s21_strlen(expected));
  ck_assert_str_eq(got, expected);
  while (got && expected) {
    got = s21_strtok(s21_NULL, delims);
    expected = strtok(s21_NULL, delims);
    if (got || expected) {
      ck_assert_str_eq(got, expected);
    } else {
      ck_assert_ptr_null(got);
      ck_assert_ptr_null(expected);
    }
  }
}
END_TEST

START_TEST(strtok_only_delims) {
  char str1[] = "++++++++";
  char str2[] = "++++++++";
  const char delims[] = "+_! =";
  char *got = s21_strtok(str1, delims);
  char *expected = strtok(str2, delims);
  ck_assert_ptr_null(got);
  ck_assert_ptr_null(expected);
}
END_TEST

START_TEST(strtok_too_many_uses_non_segfault) {
  char str1[] = "Aboba_Floppa_Roba";
  char str2[] = "Aboba_Floppa_Roba";
  const char delims[] = "+_! =";
  char *got = s21_strtok(str1, delims);
  char *expected = strtok(str2, delims);
  ck_assert_uint_eq(s21_strlen(got), s21_strlen(expected));
  ck_assert_str_eq(got, expected);
  int i = 5;
  while (i) {
    got = s21_strtok(s21_NULL, delims);
    expected = strtok(s21_NULL, delims);
    i--;
    if (got || expected) {
      ck_assert_str_eq(got, expected);
    } else {
      ck_assert_ptr_null(got);
      ck_assert_ptr_null(expected);
    }
  }
}
END_TEST

START_TEST(strtok_even_n_of_delims) {
  char str1[] = "Roba++++Kepa++A++++B__V";
  char str2[] = "Roba++++Kepa++A++++B__V";
  const char delims[] = "+_! =";
  char *got = s21_strtok(str1, delims);
  char *expected = strtok(str2, delims);
  ck_assert_uint_eq(s21_strlen(got), s21_strlen(expected));
  ck_assert_str_eq(got, expected);
  while (got && expected) {
    got = s21_strtok(s21_NULL, delims);
    expected = strtok(s21_NULL, delims);
    if (got || expected) {
      ck_assert_str_eq(got, expected);
    } else {
      ck_assert_ptr_null(got);
      ck_assert_ptr_null(expected);
    }
  }
}
END_TEST

START_TEST(strtok_odd_n_of_delims) {
  char str1[] = "Aboba__+Floppa_  Roba";
  char str2[] = "Aboba__+Floppa_  Roba";
  const char delims[] = "+_! =";
  char *got = s21_strtok(str1, delims);
  char *expected = strtok(str2, delims);
  ck_assert_uint_eq(s21_strlen(got), s21_strlen(expected));
  ck_assert_str_eq(got, expected);
  while (got && expected) {
    got = s21_strtok(s21_NULL, delims);
    expected = strtok(s21_NULL, delims);
    if (got || expected) {
      ck_assert_str_eq(got, expected);
    } else {
      ck_assert_ptr_null(got);
      ck_assert_ptr_null(expected);
    }
  }
}
END_TEST

START_TEST(strtok_mixed_n_of_delims) {
  char str1[] = "Aboba__Floppa_+++Roba_Kepa";
  char str2[] = "Aboba__Floppa_+++Roba_Kepa";
  const char delims[] = "+_! =";
  char *got = s21_strtok(str1, delims);
  char *expected = strtok(str2, delims);
  ck_assert_uint_eq(s21_strlen(got), s21_strlen(expected));
  ck_assert_str_eq(got, expected);
  while (got && expected) {
    got = s21_strtok(s21_NULL, delims);
    expected = strtok(s21_NULL, delims);
    if (got || expected) {
      ck_assert_str_eq(got, expected);
    } else {
      ck_assert_ptr_null(got);
      ck_assert_ptr_null(expected);
    }
  }
}
END_TEST

START_TEST(strtok_hard_mixed) {
  char str1[] = "     Aboba__+ Flo!ppa_   Roba+";
  char str2[] = "     Aboba__+ Flo!ppa_   Roba+";
  const char delims[] = "+_! =";
  char *got = s21_strtok(str1, delims);
  char *expected = strtok(str2, delims);
  ck_assert_uint_eq(s21_strlen(got), s21_strlen(expected));
  ck_assert_str_eq(got, expected);
  while (got || expected) {
    got = s21_strtok(s21_NULL, delims);
    expected = strtok(s21_NULL, delims);
    if (got || expected) {
      ck_assert_str_eq(got, expected);
    } else {
      ck_assert_ptr_null(got);
      ck_assert_ptr_null(expected);
    }
  }
}
END_TEST

START_TEST(strtok_mixed_hard_incorrect) {
  char str1[] = "!Stepa__ !M!ish a____Anton+An!!!drey";
  char str2[] = "!Stepa__ !M!ish a____Anton+An!!!drey";
  const char delims[] = "+_! =";
  char *got = s21_strtok(str1, delims);
  char *expected = strtok(str2, delims);
  ck_assert_uint_eq(s21_strlen(got), s21_strlen(expected));
  ck_assert_str_eq(got, expected);
  while (got || expected) {
    got = s21_strtok(s21_NULL, delims);
    expected = strtok(s21_NULL, delims);
    if (got || expected) {
      ck_assert_str_eq(got, expected);
    } else {
      ck_assert_ptr_null(got);
      ck_assert_ptr_null(expected);
    }
  }
}
END_TEST

START_TEST(strtok_very_hard_mixed) {
  char str1[] = "!       A!B!C!D!E!!F!!G";
  char str2[] = "!       A!B!C!D!E!!F!!G";
  const char delims[] = "+_! =";
  char *got = s21_strtok(str1, delims);
  char *expected = strtok(str2, delims);
  ck_assert_uint_eq(s21_strlen(got), s21_strlen(expected));
  ck_assert_str_eq(got, expected);
  while (got || expected) {
    got = s21_strtok(s21_NULL, delims);
    expected = strtok(s21_NULL, delims);
    if (got || expected) {
      ck_assert_str_eq(got, expected);
      ck_assert_uint_eq(s21_strlen(got), s21_strlen(expected));
    } else {
      ck_assert_ptr_null(got);
      ck_assert_ptr_null(expected);
    }
  }
}
END_TEST
// strtok <-

// strncpy ->
START_TEST(strncpy_empty) {
  char src[] = "";
  char res[] = "";
  char exp[] = "";
  s21_size_t n_byte = 0;
  s21_strncpy(res, src, n_byte);
  strncpy(exp, src, n_byte);
  ck_assert_str_eq(res, exp);
}
END_TEST

START_TEST(strncpy_zero_byte) {
  char src[] = "123";
  char res[] = "123";
  char exp[] = "123";
  s21_size_t n_byte = 0;
  s21_strncpy(res, src, n_byte);
  strncpy(exp, src, n_byte);
  ck_assert_str_eq(res, exp);
}
END_TEST

START_TEST(strncpy_empty_src) {
  char src[] = "";
  char res[] = "123";
  char exp[] = "123";
  s21_size_t n_byte = 0;
  s21_strncpy(res, src, n_byte);
  strncpy(exp, src, n_byte);
  ck_assert_str_eq(res, exp);
}
END_TEST

START_TEST(strncpy_one_byte) {
  char src[] = "123";
  char res[5] = "123";
  char exp[5] = "123";
  s21_size_t n_byte = 1;
  s21_strncpy(res, src, n_byte);
  strncpy(exp, src, n_byte);
  ck_assert_str_eq(res, exp);
}
END_TEST

START_TEST(strncpy_two_byte) {
  char src[] = "123";
  char res[7] = "123";
  char exp[7] = "123";
  s21_size_t n_byte = 2;
  s21_strncpy(res, src, n_byte);
  strncpy(exp, src, n_byte);
  ck_assert_str_eq(res, exp);
}
END_TEST

START_TEST(strncpy_string) {
  char src[] = "Str1ng";
  char res[7 + 7] = "Str1ng";
  char exp[7 + 7] = "Str1ng";
  s21_size_t n_byte = 7;
  s21_strncpy(res, src, n_byte);
  strncpy(exp, src, n_byte);
  ck_assert_str_eq(res, exp);
}
END_TEST
// strncpy <-

// strcspn ->
START_TEST(strcspn_empty) {
  char src[] = "";
  char res[] = "";
  ck_assert_int_eq(s21_strcspn(res, src), strcspn(res, src));
}
END_TEST

START_TEST(strcspn_gora_) {
  char src[] = "gora";
  char res[] = "";
  ck_assert_int_eq(s21_strcspn(res, src), strcspn(res, src));
}
END_TEST

START_TEST(strcspn__gora) {
  char src[] = "";
  char res[] = "gora";
  ck_assert_int_eq(s21_strcspn(res, src), strcspn(res, src));
}
END_TEST

START_TEST(strcspn_any_register) {
  char src[] = "gora";
  char res[] = "gOra";
  ck_assert_int_eq(s21_strcspn(res, src), strcspn(res, src));
}
END_TEST

START_TEST(strcspn_num_num) {
  char src[] = "123";
  char res[] = "123";
  ck_assert_int_eq(s21_strcspn(res, src), strcspn(res, src));
}
END_TEST

START_TEST(strcspn_long_num_num) {
  char src[] = "12345";
  char res[] = "123";
  ck_assert_int_eq(s21_strcspn(res, src), strcspn(res, src));
}
END_TEST

START_TEST(strcspn_num_long_num) {
  char src[] = "123";
  char res[] = "12345";
  ck_assert_int_eq(s21_strcspn(res, src), strcspn(res, src));
}
END_TEST

START_TEST(strcspn_any_num) {
  char src[] = "1234567890";
  char res[] = "0987654321";
  ck_assert_int_eq(s21_strcspn(res, src), strcspn(res, src));
}
END_TEST

START_TEST(strcspn_num_with_letter) {
  char src[] = "1A2A3A4A5A";
  char res[] = "123";
  ck_assert_int_eq(s21_strcspn(res, src), strcspn(res, src));
}
END_TEST

START_TEST(strcspn_num_with_letter2) {
  char src[] = "a1aaa23aaa41235";
  char res[] = "123";
  ck_assert_int_eq(s21_strcspn(res, src), strcspn(res, src));
}
END_TEST

START_TEST(strcspn_basic_test) {
  char src[] = "absD";
  char res[] = "aD";
  ck_assert_int_eq(s21_strcspn(res, src), strcspn(res, src));
}
END_TEST

START_TEST(strcspn_any_sim) {
  char src[] = "32ASDASDPare[0g9jf m07y271234567890";
  char res[] = "0987654321";
  ck_assert_int_eq(s21_strcspn(res, src), strcspn(res, src));
}
END_TEST

START_TEST(strcspn_upper_letter) {
  char src[] = "32ASDASDPare[0g9jf m07y271234567890";
  char res[] = "1234567890QWERTYUIOPASDFGHJKLZXCVBNM";
  ck_assert_int_eq(s21_strcspn(res, src), strcspn(res, src));
}
END_TEST

START_TEST(strcspn_lower_letter) {
  char src[] = "32jersASDASDPare[0g9jf m07y271234567890";
  char res[] = "1234567890qwertyuiopasdfghjklczxcvbnm";
  ck_assert_int_eq(s21_strcspn(res, src), strcspn(res, src));
}
END_TEST

START_TEST(strcspn_not_uniq_sim) {
  char src[] =
      "333333333333333333333333333333333333333333333333333333333333333333333333"
      "33333333333333";
  char res[] =
      "111111111111111111111111111111111111111111111111111111111111111111111111"
      "11111111111113";
  ck_assert_int_eq(s21_strcspn(res, src), strcspn(res, src));
}
END_TEST
// strcspn <-

// strcmp ->
START_TEST(strcmp_Heloboba_Heloboba) {
  char a[] = "Heloboba";
  char b[] = "Heloboba";
  int got = s21_strcmp(a, b);
  int expected = strcmp(a, b);
  if (got > 1) got = 1;
  if (expected > 1) expected = 1;
  if (got < -1) got = -1;
  if (expected < -1) expected = -1;
  ck_assert_int_eq(got, expected);
}
END_TEST

START_TEST(strcmp_HEloboba_Heloboba) {
  char a[] = "HEloboba";
  char b[] = "Heloboba";
  int got = s21_strcmp(a, b);
  int expected = strcmp(a, b);
  if (got > 1) got = 1;
  if (expected > 1) expected = 1;
  if (got < -1) got = -1;
  if (expected < -1) expected = -1;
  ck_assert_int_eq(got, expected);
}
END_TEST

START_TEST(strcmp_Hel0boba_Helob0ba) {
  char a[] = "Hel0boba";
  char b[] = "Helob0ba";
  int got = s21_strcmp(a, b);
  int expected = strcmp(a, b);
  if (got > 1) got = 1;
  if (expected > 1) expected = 1;
  if (got < -1) got = -1;
  if (expected < -1) expected = -1;
  ck_assert_int_eq(got, expected);
}
END_TEST

START_TEST(strcmp_Heloboba_) {
  char a[] = "Heloboba";
  char b[] = "";
  int got = s21_strcmp(a, b);
  int expected = strcmp(a, b);
  if (got > 1) got = 1;
  if (expected > 1) expected = 1;
  if (got < -1) got = -1;
  if (expected < -1) expected = -1;
  ck_assert_int_eq(got, expected);
}
END_TEST

START_TEST(strcmp__Heloboba) {
  char a[] = "";
  char b[] = "Heloboba";
  int got = s21_strcmp(a, b);
  int expected = strcmp(a, b);
  if (got > 1) got = 1;
  if (expected > 1) expected = 1;
  if (got < -1) got = -1;
  if (expected < -1) expected = -1;
  ck_assert_int_eq(got, expected);
}
END_TEST

START_TEST(strcmp_Heloboba) {
  char a[] = "L(8)L";
  char b[] = "L(8)L";
  int got = s21_strcmp(a, b);
  int expected = strcmp(a, b);
  if (got > 1) got = 1;
  if (expected > 1) expected = 1;
  if (got < -1) got = -1;
  if (expected < -1) expected = -1;
  ck_assert_int_eq(got, expected);
}
END_TEST

START_TEST(strcmp_empty) {
  char a[] = "";
  char b[] = "";
  int got = s21_strcmp(a, b);
  int expected = strcmp(a, b);
  if (got > 1) got = 1;
  if (expected > 1) expected = 1;
  if (got < -1) got = -1;
  if (expected < -1) expected = -1;
  ck_assert_int_eq(got, expected);
}
END_TEST

START_TEST(strcmp_only_num) {
  char a[] = "1234567890";
  char b[] = "1234567890";
  int got = s21_strcmp(a, b);
  int expected = strcmp(a, b);
  if (got > 1) got = 1;
  if (expected > 1) expected = 1;
  if (got < -1) got = -1;
  if (expected < -1) expected = -1;
  ck_assert_int_eq(got, expected);
}
END_TEST
// strcmp <-

// strchr ->
START_TEST(strchr_abobasnutsa_find_a) {
  char src[] = "abobasnutsa";
  char find = 'a';
  ck_assert_pstr_eq(s21_strchr(src, find), strchr(src, find));
}
END_TEST

START_TEST(strchr_abobasnutAsa_find_A) {
  char src[] = "abobasnutAsa";
  char find = 'A';
  ck_assert_pstr_eq(s21_strchr(src, find), strchr(src, find));
}
END_TEST

START_TEST(strchr_abobasnutA1sa_find_1) {
  char src[] = "abobasnutA1sa";
  char find = '1';
  ck_assert_pstr_eq(s21_strchr(src, find), strchr(src, find));
}
END_TEST

START_TEST(strchr_abobasnutAsa_find_Z) {
  char src[] = "abobasnutAsa";
  char find = 'Z';
  ck_assert_pstr_eq(s21_strchr(src, find), strchr(src, find));
}
END_TEST

START_TEST(strchr_abobasnutAsa_find_3) {
  char src[] = "abobasnutAsa";
  char find = '3';
  ck_assert_pstr_eq(s21_strchr(src, find), strchr(src, find));
}
END_TEST

START_TEST(strchr_empty_src) {
  char src[] = "";
  char find = '3';
  ck_assert_pstr_eq(s21_strchr(src, find), strchr(src, find));
}
END_TEST
// strchr <-

// strcpy ->
START_TEST(strcpy_aboba_floppa) {
  char src[] = " floppa!!!";
  char res[5 + 15] = "aboba ";
  char expected[5 + 15] = "aboba ";
  s21_strcpy(res, src);
  strcpy(expected, src);
  ck_assert_str_eq(res, expected);
}
END_TEST

START_TEST(strcpy__floppa) {
  char src[] = "Floppa!!!";
  char res[5 + 15] = "";
  char expected[5 + 15] = "";
  s21_strcpy(res, src);
  strcpy(expected, src);
  ck_assert_str_eq(res, expected);
}
END_TEST

START_TEST(strcpy_aboba_) {
  char src[] = "";
  char res[5 + 15] = "abobas";
  char expected[5 + 15] = "abobas";
  s21_strcpy(res, src);
  strcpy(expected, src);
  ck_assert_str_eq(res, expected);
}
END_TEST

START_TEST(strcpy_empty) {
  char src[] = "";
  char res[5 + 15] = "";
  char expected[5 + 15] = "";
  s21_strcpy(res, src);
  strcpy(expected, src);
  ck_assert_str_eq(res, expected);
}
END_TEST

START_TEST(strcpy_empty_num) {
  char src[] = "1";
  char res[5 + 15] = "";
  char expected[5 + 15] = "";
  s21_strcpy(res, src);
  strcpy(expected, src);
  ck_assert_str_eq(res, expected);
}
END_TEST

START_TEST(strcpy_hello) {
  char src[] = " my dear friend\"";
  char res[5 + 15] = "Hello";
  char expected[5 + 15] = "Hello";
  s21_strcpy(res, src);
  strcpy(expected, src);
  ck_assert_str_eq(res, expected);
}
END_TEST

START_TEST(strcpy_over_string) {
  char src[] = "ab\0ba";
  char res[10 + 9] = "Gre\0t";
  char expected[10 + 9] = "Gre\0t";
  s21_strcpy(res, src);
  strcpy(expected, src);
  ck_assert_str_eq(res, expected);
}
END_TEST

START_TEST(strcpy_hard_test) {
  char src[] = "ad[sofijpoiajsdf pj98981h23 p9h floppa!!!";
  char res[49 + 42] = "as[oidjf paijsdf j9oqh2837o4h hUW auhduash W8awd";
  char expected[49 + 42] = "as[oidjf paijsdf j9oqh2837o4h hUW auhduash W8awd";
  s21_strcpy(res, src);
  strcpy(expected, src);
  ck_assert_str_eq(res, expected);
}
END_TEST
// strcpy <-

// strcat ->
START_TEST(strcat_Hello_aboba) {
  char src[] = " aboba!!!";
  char res[5 + 10] = "Hello";
  char expected[5 + 10] = "Hello";
  s21_strcat(res, src);
  strcat(expected, src);
  ck_assert_str_eq(res, expected);
}
END_TEST

START_TEST(strcat_zero_first) {
  char src[] = " aboba!!!";
  char res[0 + 10] = "";
  char expected[0 + 10] = "";
  s21_strcat(res, src);
  strcat(expected, src);
  ck_assert_str_eq(res, expected);
}
END_TEST

START_TEST(strcat_zero_last) {
  char src[] = "";
  char res[] = "Hello";
  char expected[] = "Hello";
  s21_strcat(res, src);
  strcat(expected, src);
  ck_assert_str_eq(res, expected);
}
END_TEST

START_TEST(strcat_any_letters_with_register) {
  char src[] = "asdfj  asdf aisdfjaiushdfASD SAD asDSad ASDAsdwqqeAS";
  char res[5 + 53] = "Hello";
  char expected[5 + 53] = "Hello";
  s21_strcat(res, src);
  strcat(expected, src);
  ck_assert_str_eq(res, expected);
}
END_TEST

START_TEST(strcat_any_letters_with_register_and_num) {
  char src[] = "asd0fj  asd1f aisdfjw6234A1241SD SA5 asDSad 89SDAsdw7qqeAS";
  char res[5 + 59] = "Hello";
  char expected[5 + 59] = "Hello";
  s21_strcat(res, src);
  strcat(expected, src);
  ck_assert_str_eq(res, expected);
}
END_TEST

START_TEST(strcat_any_letters_with_register_and_num_and_sim) {
  char src[] =
      "asd0fj  asd1f aisdfjw6234A1241SD SA5 asDSad 89SDAsdw7qqeAS)(?!.,";
  char res[5 + 65] = "Hello";
  char expected[5 + 65] = "Hello";
  s21_strcat(res, src);
  strcat(expected, src);
  ck_assert_str_eq(res, expected);
}
END_TEST
// strcat <-

Suite *suite_str(void) {
  Suite *s = suite_create("str");
  TCase *tc = tcase_create("str_tc");

  tcase_add_test(tc, strerror_1);
  tcase_add_test(tc, strlen_empty);
  tcase_add_test(tc, strlen_abosal);
  tcase_add_test(tc, strlen_num);
  tcase_add_test(tc, strlen_string);
  tcase_add_test(tc, strlen_abosal_no_dal);
  tcase_add_test(tc, strlen_dai_mne_pen);
  tcase_add_test(tc, strlen_Floppy_disk);
  tcase_add_test(tc, strlen_floppa);
  tcase_add_test(tc, strlen_kot_Vasily);
  tcase_add_test(tc, strlen_Russky_kot_Shlepa);
  tcase_add_test(tc, strncat_all_empty);
  tcase_add_test(tc, strncat_zero_byte);
  tcase_add_test(tc, strncat_empty_src);
  tcase_add_test(tc, strncat_cd_abosa);
  tcase_add_test(tc, strncat_string);
  tcase_add_test(tc, strncat_BIGFLOPPA);
  tcase_add_test(tc, strncat_BIGFLOPPA2);
  tcase_add_test(tc, strncat_BIGFLOPPA3);
  tcase_add_test(tc, strncat_BIGFLOPPA4);
  tcase_add_test(tc, strncat_zero_char);
  tcase_add_test(tc, strncmp_empty);
  tcase_add_test(tc, strncmp_floppa_);
  tcase_add_test(tc, strncmp__floppa);
  tcase_add_test(tc, strncmp_floppa_floppa);
  tcase_add_test(tc, strncmp_floppa_floppa_zero_byte);
  tcase_add_test(tc, strncmp_floppa_floppa_one_byte);
  tcase_add_test(tc, strrchr_empty);
  tcase_add_test(tc, strrchr_floppy_);
  tcase_add_test(tc, strrchr__floppy);
  tcase_add_test(tc, strrchr_poki_doki_o);
  tcase_add_test(tc, strrchr_poki_doki_i);
  tcase_add_test(tc, strrchr_poki_doki_p);
  tcase_add_test(tc, strrchr_find_big_P);
  tcase_add_test(tc, strrchr_find_zero);
  tcase_add_test(tc, strpbrk_empty);
  tcase_add_test(tc, strpbrk_floppy_);
  tcase_add_test(tc, strpbrk__floppy);
  tcase_add_test(tc, strpbrk_poki_doki_o);
  tcase_add_test(tc, strpbrk_poki_doki_i);
  tcase_add_test(tc, strpbrk_poki_doki_p);
  tcase_add_test(tc, strpbrk_find_big_P);
  tcase_add_test(tc, strpbrk_find_zero);
  tcase_add_test(tc, strspn_empty);
  tcase_add_test(tc, strspn_gora_);
  tcase_add_test(tc, strspn__gora);
  tcase_add_test(tc, strspn_any_register);
  tcase_add_test(tc, strspn_num_num);
  tcase_add_test(tc, strspn_long_num_num);
  tcase_add_test(tc, strspn_num_long_num);
  tcase_add_test(tc, strspn_any_num);
  tcase_add_test(tc, strspn_num_with_letter);
  tcase_add_test(tc, strspn_num_with_letter2);
  tcase_add_test(tc, strspn_basic_test);
  tcase_add_test(tc, strspn_any_sim);
  tcase_add_test(tc, strspn_upper_letter);
  tcase_add_test(tc, strspn_lower_letter);
  tcase_add_test(tc, strspn_not_uniq_sim);
  tcase_add_test(tc, strstr_empty_string_haystack_and_needle);
  tcase_add_test(tc, strstr_empty_string_haystack);
  tcase_add_test(tc, strstr_empty_string_needle);
  tcase_add_test(tc, strstr_toxic_test);
  tcase_add_test(tc, strstr_not_word_in_haystack);
  tcase_add_test(tc, strstr_words_with_any_register);
  tcase_add_test(tc, strstr_repeated_words);
  tcase_add_test(tc, strstr_word_at_end);
  tcase_add_test(tc, strstr_one_simbol_in_needle_and_haystack);
  tcase_add_test(tc, strstr_one_simbol_in_needle);
  tcase_add_test(tc, strstr_one_simbol_in_haystack);
  tcase_add_test(tc, strtok_correct_token_string);
  tcase_add_test(tc, strtok_hard_token_string);
  tcase_add_test(tc, strtok_unary_delimiters);
  tcase_add_test(tc, strtok_no_delims);
  tcase_add_test(tc, strtok_only_delims);
  tcase_add_test(tc, strtok_too_many_uses_non_segfault);
  tcase_add_test(tc, strtok_even_n_of_delims);
  tcase_add_test(tc, strtok_odd_n_of_delims);
  tcase_add_test(tc, strtok_mixed_n_of_delims);
  tcase_add_test(tc, strtok_hard_mixed);
  tcase_add_test(tc, strtok_mixed_hard_incorrect);
  tcase_add_test(tc, strtok_very_hard_mixed);
  tcase_add_test(tc, strncpy_empty);
  tcase_add_test(tc, strncpy_zero_byte);
  tcase_add_test(tc, strncpy_empty_src);
  tcase_add_test(tc, strncpy_one_byte);
  tcase_add_test(tc, strncpy_two_byte);
  tcase_add_test(tc, strncpy_string);
  tcase_add_test(tc, strcspn_empty);
  tcase_add_test(tc, strcspn_gora_);
  tcase_add_test(tc, strcspn__gora);
  tcase_add_test(tc, strcspn_any_register);
  tcase_add_test(tc, strcspn_num_num);
  tcase_add_test(tc, strcspn_long_num_num);
  tcase_add_test(tc, strcspn_num_long_num);
  tcase_add_test(tc, strcspn_any_num);
  tcase_add_test(tc, strcspn_num_with_letter);
  tcase_add_test(tc, strcspn_num_with_letter2);
  tcase_add_test(tc, strcspn_basic_test);
  tcase_add_test(tc, strcspn_any_sim);
  tcase_add_test(tc, strcspn_upper_letter);
  tcase_add_test(tc, strcspn_lower_letter);
  tcase_add_test(tc, strcspn_not_uniq_sim);
  tcase_add_test(tc, strcmp_Heloboba_Heloboba);
  tcase_add_test(tc, strcmp_HEloboba_Heloboba);
  tcase_add_test(tc, strcmp_Hel0boba_Helob0ba);
  tcase_add_test(tc, strcmp_Heloboba_);
  tcase_add_test(tc, strcmp__Heloboba);
  tcase_add_test(tc, strcmp_Heloboba);
  tcase_add_test(tc, strcmp_empty);
  tcase_add_test(tc, strcmp_only_num);
  tcase_add_test(tc, strchr_abobasnutsa_find_a);
  tcase_add_test(tc, strchr_abobasnutAsa_find_A);
  tcase_add_test(tc, strchr_abobasnutA1sa_find_1);
  tcase_add_test(tc, strchr_abobasnutAsa_find_Z);
  tcase_add_test(tc, strchr_abobasnutAsa_find_3);
  tcase_add_test(tc, strchr_empty_src);
  tcase_add_test(tc, strcpy_aboba_floppa);
  tcase_add_test(tc, strcpy__floppa);
  tcase_add_test(tc, strcpy_aboba_);
  tcase_add_test(tc, strcpy_empty);
  tcase_add_test(tc, strcpy_empty_num);
  tcase_add_test(tc, strcpy_hello);
  tcase_add_test(tc, strcpy_over_string);
  tcase_add_test(tc, strcpy_hard_test);
  tcase_add_test(tc, strcat_Hello_aboba);
  tcase_add_test(tc, strcat_zero_first);
  tcase_add_test(tc, strcat_zero_last);
  tcase_add_test(tc, strcat_any_letters_with_register);
  tcase_add_test(tc, strcat_any_letters_with_register_and_num);
  tcase_add_test(tc, strcat_any_letters_with_register_and_num_and_sim);

  suite_add_tcase(s, tc);
  return s;
}
