// Tests: sscanf: floats, unsigned, mixed.
#include "s21_string_test.h"

// [%f] / [%g] / %[%G] //
START_TEST(sscanf_floats1) {
  long double a1 = 1, a2 = 0, b1 = 1, b2 = 0, c1 = 1, c2 = 0, d1 = 1, d2 = 0;

  const char str[] = "53.1 -4.1135 41.3333 +2.0001";
  const char fstr[] = "%Lf %Lf %Lf %Lf";

  int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_double_eq(a1, a2);
  ck_assert_double_eq(b1, b2);
  ck_assert_double_eq(c1, c2);
  ck_assert_double_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_floats2) {
  double a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;

  const char str[] = "0.00001 -4123123 4. .";
  const char fstr[] = "%lf %lf %lf %lf";

  int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_double_eq(a1, a2);
  ck_assert_double_eq(b1, b2);
  ck_assert_double_eq(c1, c2);
  ck_assert_double_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_floats3) {
  float a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;

  const char str[] = ". . . .";
  const char fstr[] = "%f %f %f %f";

  int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_double_eq(a1, a2);
  ck_assert_double_eq(b1, b2);
  ck_assert_double_eq(c1, c2);
  ck_assert_double_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_floats4) {
  long double a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;

  const char str[] = "513.41 -4.14135 414.3333 +112.0001";
  const char fstr[] = "%Lf %Lf %Lf %Lf";

  int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_double_eq(a1, a2);
  ck_assert_double_eq(b1, b2);
  ck_assert_double_eq(c1, c2);
  ck_assert_double_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_floats5) {
  float a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0;

  const char str[] = "53.1 -4.1135 411231.3 +2.0001";
  const char fstr[] = "%*f %f %f %f";

  int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1);
  int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2);

  ck_assert_int_eq(res1, res2);
  ck_assert_float_eq(a1, a2);
  ck_assert_float_eq(b1, b2);
  ck_assert_float_eq(c1, c2);
}
END_TEST

START_TEST(sscanf_floats_sci1) {
  float a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;

  const char str[] = "1.4441 1.e+4 -3.31e-4 0.444e-5";
  const char fstr[] = "%G %G %G %G";

  int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_double_eq(a1, a2);
  ck_assert_double_eq(b1, b2);
  ck_assert_double_eq(c1, c2);
  ck_assert_double_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_floats_sci2) {
  float a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;

  const char str[] = "inf 1.e+4 NaN 0.444e-5";
  const char fstr[] = "%G %G %G %G";

  int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_ldouble_eq(a1, a2);
  // Unfortunately, assertions for inf do not work correctly in libcheck
  // ck_assert_ldouble_infinite(a1);
  // ck_assert_ldouble_infinite(a2);
  ck_assert_double_eq(b1, b2);
  ck_assert_float_nan(c1);
  ck_assert_float_nan(c2);
  ck_assert_double_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_floats_sci3) {
  float a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;

  const char str[] = "inF InF inF INF";
  const char fstr[] = "%G %G %G %G";

  int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_ldouble_eq(a1, a2);
  ck_assert_double_eq(b1, b2);
  ck_assert_double_eq(c1, c2);
  ck_assert_double_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_floats_sci4) {
  float a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;

  const char str[] = "Nan NAN 0.0000 0";
  const char fstr[] = "%G %G %G %G";

  int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_float_nan(a1);
  ck_assert_float_nan(a2);
  ck_assert_float_nan(b1);
  ck_assert_float_nan(b2);
  ck_assert_ldouble_eq(c1, c2);
  ck_assert_ldouble_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_floats_sci5) {
  float a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;

  const char str[] =
      "nAN           INF                   -0.1111         1e-10";
  const char fstr[] = "%G %G %G %G";

  int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_float_nan(a1);
  ck_assert_float_nan(a2);
  ck_assert_ldouble_eq(b1, b2);
  ck_assert_ldouble_eq(c1, c2);
  ck_assert_ldouble_eq(d1, d2);
}
END_TEST

// [%u] //
START_TEST(sscanf_uint1) {
  unsigned short a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  const char str[] = "-1337 +21 --5008 3000";
  const char fstr[] = "%hu %hu %hu %hu";

  int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_uint_eq(res1, res2);
  ck_assert_uint_eq(a1, a2);
  ck_assert_uint_eq(b1, b2);
  ck_assert_uint_eq(c1, c2);
  ck_assert_uint_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_uint2) {
  unsigned long long int a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0,
                         d2 = 0;
  const char str[] = "-1337 233333331 5008 3000";
  const char fstr[] = "%1llu %2llu %5llu %4llu";

  int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_uint3) {
  unsigned long long int a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0;
  long long d1 = 0, d2 = 0;
  long double v1, v2;

  const char str[] =
      "\t\t\t\t\t\n 3      adsfdfa%$$$$`adfasdfasdfaszcvzcxvcv -1337 "
      "anurobich+ 21 -5008 -33000 0.3333";
  const char fstr[] = "%*s %*s %llu %s %llu %llu %lld %Lf";

  char s1[BUFF_SIZE] = {'\0'};
  char s2[BUFF_SIZE] = {'\0'};

  int16_t res1 = s21_sscanf(str, fstr, &a1, s1, &b1, &c1, &d1, &v1);
  int16_t res2 = sscanf(str, fstr, &a2, s2, &b2, &c2, &d2, &v2);

  ck_assert_uint_eq(res1, res2);
  ck_assert_str_eq(s1, s2);
  ck_assert_uint_eq(a1, a2);
  ck_assert_uint_eq(b1, b2);
  ck_assert_uint_eq(c1, c2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_ldouble_eq_tol(v1, v2, 0.0001);
}
END_TEST

START_TEST(sscanf_uint4) {
  unsigned short a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  const char str[] = "-1337 +21 --5008 3000";
  const char fstr[] = "%hu %hu %hu %hu";

  int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_uint5) {
  unsigned short a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  const char str[] = "-1337 +21 --5008 3000";
  const char fstr[] = "%hu %hu %hu %hu";

  int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_uint6) {
  unsigned short a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  const char str[] = "-1337 +21 --5008 3000";
  const char fstr[] = "%hu %hu %hu %hu";

  int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_upeer_hex_base_version) {
  uint32_t a1, a2;
  const char str[] = "F";
  const char fstr[] = "%X";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(sscanf_upeer_hex_overflow) {
  uint32_t a1, a2;
  const char str[] = "0xFFFFFFFF";
  const char fstr[] = "%X";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(sscanf_upeer_hex_0x) {
  uint32_t a1, a2;
  const char str[] = "0x";
  const char fstr[] = "%X";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(sscanf_upeer_hex_0X) {
  uint32_t a1, a2;
  const char str[] = "0X";
  const char fstr[] = "%X";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(sscanf_upeer_hex_empty) {
  uint32_t a1, a2;
  const char str[] = "";
  const char fstr[] = "%X";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sscanf_upeer_hex_fail) {
  uint32_t a1, a2;
  const char str[] = "qF";
  const char fstr[] = "%X";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sscanf_upeer_hex_spaces_tabs_sns) {
  uint32_t a1, a2;
  const char str[] = "          \n             \n     F";
  const char fstr[] = "%X";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(sscanf_upeer_hex_short) {
  uint16_t a1, a2;
  const char str[] = "F";
  const char fstr[] = "%hX";
  uint16_t res1 = s21_sscanf(str, fstr, &a1);
  uint16_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(sscanf_upeer_hex_long) {
  unsigned long int a1, a2;
  const char str[] = "F";
  const char fstr[] = "%lX";
  uint16_t res1 = s21_sscanf(str, fstr, &a1);
  uint16_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(sscanf_upeer_hex_longlong) {
  unsigned long long int a1, a2;
  const char str[] = "F";
  const char fstr[] = "%llX";
  uint16_t res1 = s21_sscanf(str, fstr, &a1);
  uint16_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(sscanf_upeer_hex_2x) {
  uint32_t a1, a2;
  const char str[] = "0xFF0x0xFFF 0xFFxFF";
  const char fstr[] = "%X";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(sscanf_upeer_hex_star) {
  const char str[] = "0xFF0x0xFFF 0xFFxFF";
  const char fstr[] = "%*X";
  uint32_t res1 = s21_sscanf(str, fstr);
  uint32_t res2 = sscanf(str, fstr);

  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sscanf_upeer_hex_nohex) {
  uint32_t a1, a2;
  const char str[] = "tqwqpl";
  const char fstr[] = "%X";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sscanf_upeer_hex_lower) {
  uint32_t a1, a2;
  const char str[] = "abcdef";
  const char fstr[] = "%X";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(sscanf_upeer_hex_sign) {
  uint32_t a1, a2;
  const char str[] = "-f";
  const char fstr[] = "%X";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(sscanf_lower_hex_base_version) {
  uint32_t a1, a2;
  const char str[] = "f";
  const char fstr[] = "%x";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(sscanf_lower_hex_overflow) {
  uint32_t a1, a2;
  const char str[] = "0xfffffffffffffffffff";
  const char fstr[] = "%x";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(sscanf_lower_hex_0x) {
  uint32_t a1, a2;
  const char str[] = "0x";
  const char fstr[] = "%x";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(sscanf_lower_hex_0X) {
  uint32_t a1, a2;
  const char str[] = "0X";
  const char fstr[] = "%x";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(sscanf_lower_hex_empty) {
  uint32_t a1, a2;
  const char str[] = "";
  const char fstr[] = "%x";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sscanf_lower_hex_fail) {
  uint32_t a1, a2;
  const char str[] = "qF";
  const char fstr[] = "%x";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sscanf_lower_hex_spaces_tabs_sns) {
  uint32_t a1, a2;
  const char str[] = "          \n             \n     F";
  const char fstr[] = "%x";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(sscanf_lower_hex_short) {
  uint16_t a1, a2;
  const char str[] = "ff";
  const char fstr[] = "%hx";
  uint16_t res1 = s21_sscanf(str, fstr, &a1);
  uint16_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(sscanf_lower_hex_long) {
  unsigned long int a1, a2;
  const char str[] = "ff";
  const char fstr[] = "%lx";
  uint16_t res1 = s21_sscanf(str, fstr, &a1);
  uint16_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(sscanf_lower_hex_longlong) {
  unsigned long long int a1, a2;
  const char str[] = "faaaaaaaaaaaaf";
  const char fstr[] = "%llx";
  uint16_t res1 = s21_sscanf(str, fstr, &a1);
  uint16_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  // ck_assert_unsigned long long int_eq(a1, a2);
  // ck_assert_uint64_eq(a1, a2);
  ck_assert_uint_eq(a1, a2);
}
END_TEST

START_TEST(sscanf_lower_hex_2x) {
  uint32_t a1, a2;
  const char str[] = "0xFF0x0xFFF 0xFFxFF";
  const char fstr[] = "%x";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(sscanf_lower_hex_star) {
  const char str[] = "0xFF0x0xFFF 0xFFxFF";
  const char fstr[] = "%*x";
  uint32_t res1 = s21_sscanf(str, fstr);
  uint32_t res2 = sscanf(str, fstr);

  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sscanf_lower_hex_nohex) {
  uint32_t a1, a2;
  const char str[] = "tqwqpl";
  const char fstr[] = "%x";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sscanf_lower_hex_lower) {
  uint32_t a1, a2;
  const char str[] = "abcdef";
  const char fstr[] = "%x";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(sscanf_lower_hex_sign) {
  uint32_t a1, a2;
  const char str[] = "-f";
  const char fstr[] = "%x";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(upper_hex_len) {
  uint32_t a1, a2;
  const char str[] = "123531FFF";
  const char fstr[] = "%2X";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(sscanf_lower_hex_len) {
  uint32_t a1, a2;
  const char str[] = "123531FFF";
  const char fstr[] = "%2x";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(sscanf_octal_base_version) {
  uint32_t a1, a2;
  const char str[] = "777";
  const char fstr[] = "%o";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(sscanf_octal_overflow) {
  uint32_t a1, a2;
  const char str[] = "0x7777777777777777777777";
  const char fstr[] = "%o";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(sscanf_octal_0x) {
  uint32_t a1, a2;
  const char str[] = "0x";
  const char fstr[] = "%o";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(sscanf_octal_0X) {
  uint32_t a1, a2;
  const char str[] = "0X";
  const char fstr[] = "%o";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(sscanf_octal_empty) {
  uint32_t a1, a2;
  const char str[] = "";
  const char fstr[] = "%o";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sscanf_octal_fail) {
  uint32_t a1, a2;
  const char str[] = "q1";
  const char fstr[] = "%o";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sscanf_octal_spaces_tabs_sns) {
  uint32_t a1, a2;
  const char str[] = "          \n             \n     5";
  const char fstr[] = "%o";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(sscanf_octal_short) {
  uint16_t a1, a2;
  const char str[] = "12";
  const char fstr[] = "%ho";
  uint16_t res1 = s21_sscanf(str, fstr, &a1);
  uint16_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(sscanf_octal_long) {
  unsigned long int a1, a2;
  const char str[] = "57234";
  const char fstr[] = "%lo";
  uint16_t res1 = s21_sscanf(str, fstr, &a1);
  uint16_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(sscanf_octal_longlong) {
  unsigned long long int a1, a2;
  const char str[] = "12356226137";
  const char fstr[] = "%llo";
  uint16_t res1 = s21_sscanf(str, fstr, &a1);
  uint16_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(sscanf_octal_2x) {
  uint32_t a1, a2;
  const char str[] = "0x12320x213x123213";
  const char fstr[] = "%o";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(sscanf_octal_star) {
  const char str[] = "521561612";
  const char fstr[] = "%*o";
  uint32_t res1 = s21_sscanf(str, fstr);
  uint32_t res2 = sscanf(str, fstr);

  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sscanf_octal_nohex) {
  uint32_t a1, a2;
  const char str[] = "tqwqpl";
  const char fstr[] = "%o";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sscanf_octal_lower) {
  uint32_t a1, a2;
  const char str[] = "01234567";
  const char fstr[] = "%o";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(sscanf_octal_sign) {
  uint32_t a1, a2;
  const char str[] = "-66";
  const char fstr[] = "%o";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(sscanf_octal_len) {
  uint32_t a1, a2;
  const char str[] = "123531";
  const char fstr[] = "%2o";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(sscanf_buff1) {
  int32_t a1, a2;
  int32_t b1, b2;
  const char str[] = "12 keppa 12";
  const char fstr[] = "%d keppa %d";
  int32_t res1 = s21_sscanf(str, fstr, &a1, &b1);
  int32_t res2 = sscanf(str, fstr, &a2, &b2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
}
END_TEST

START_TEST(sscanf_buff2) {
  int32_t a1, a2;
  int32_t b1, b2;
  const char str[] = "12keppa12";
  const char fstr[] = "%dkeppa%d";
  int32_t res1 = s21_sscanf(str, fstr, &a1, &b1);
  int32_t res2 = sscanf(str, fstr, &a2, &b2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
}
END_TEST

START_TEST(sscanf_pointer1) {
  int *a1 = 0, *a2 = 0, *b1 = 0, *b2 = 0, *c1 = 0, *c2 = 0, *d1 = 0, *d2 = 0;
  const char str[] = "0xFFFF 0xAAAA 0x7123 0xBBC1FF";
  const char fstr[] = "%p %p %p %p";

  int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_ptr_eq(a1, a2);
  ck_assert_ptr_eq(b1, b2);
  ck_assert_ptr_eq(c1, c2);
  ck_assert_ptr_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_pointer2) {
  int *a1 = 0, *a2 = 0, *b1 = 0, *b2 = 0, *c1 = 0, *c2 = 0, *d1 = 0, *d2 = 0;
  const char str[] = "0xFFFF 0xAAAA 0x7123 0xBBC1FF";
  const char fstr[] = "%p %p %p %p";

  int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_ptr_eq(a1, a2);
  ck_assert_ptr_eq(b1, b2);
  ck_assert_ptr_eq(c1, c2);
  ck_assert_ptr_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_pointer3) {
  int *a1 = 0, *a2 = 0, *b1 = 0, *b2 = 0, *c1 = 0, *c2 = 0, *d1 = 0, *d2 = 0;
  const char str[] = "0xFFFF 0xAAAA 0x7123 0xBBC1FF";
  const char fstr[] = "%p %p %p %p";

  int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_ptr_eq(a1, a2);
  ck_assert_ptr_eq(b1, b2);
  ck_assert_ptr_eq(c1, c2);
  ck_assert_ptr_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_pointer4) {
  int *a1 = 0, *a2 = 0, *b1 = 0, *b2 = 0, *c1 = 0, *c2 = 0, *d1 = 0, *d2 = 0;
  const char str[] = "0xFFFF 0xAAAA 0x7123 0xBBC1FF";
  const char fstr[] = "%p %p %p %p";

  int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_ptr_eq(a1, a2);
  ck_assert_ptr_eq(b1, b2);
  ck_assert_ptr_eq(c1, c2);
  ck_assert_ptr_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_hard1) {
  int a1 = 0, a2 = 5, a3 = 3, a4 = 9;
  int32_t n1 = 500, n2 = 10000;

  const char str[] = "123123SkipMePlease!!!!123";
  const char fstr[] = "%dSkipMePlease!!!!%d %n";

  int16_t res1 = s21_sscanf(str, fstr, &a1, &a3, &n1);
  int16_t res2 = sscanf(str, fstr, &a2, &a4, &n2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(n1, n2);
  ck_assert_int_eq(a3, a4);
  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(sscanf_buff3) {
  int32_t a1, a2;
  int32_t b1 = 0, b2 = 0;
  const char str[] = "12keppa12";
  const char fstr[] = "%dkeppapos%d";
  int32_t res1 = s21_sscanf(str, fstr, &a1, &b1);
  int32_t res2 = sscanf(str, fstr, &a2, &b2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
}
END_TEST

START_TEST(sscanf_perc1) {
  int32_t a1, a2;
  int32_t b1 = 80, b2 = 33;
  int32_t c1 = 55, c2 = 33;
  const char str[] = "12 % 13 % 14";
  const char fstr[] = "%d %% %d %% %d";
  int32_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1);
  int32_t res2 = sscanf(str, fstr, &a2, &b2, &c2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(sscanf_perc2) {
  int32_t a1, a2;
  int32_t b1 = 80, b2 = 33;
  int32_t c1 = 55, c2 = 33;
  const char str[] = "12%13%14";
  const char fstr[] = "%d%%%d%%%d";
  int32_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1);
  int32_t res2 = sscanf(str, fstr, &a2, &b2, &c2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(sscanf_perc3) {
  int32_t a1 = 1234, a2 = 33333;

  const char str[] = "%%%16";
  const char fstr[] = "%%%%%%%d";
  int32_t res1 = s21_sscanf(str, fstr, &a1);
  int32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(sscanf_perc4) {
  const char str[] = "%%%";
  const char fstr[] = "%%%%%%";
  int32_t res1 = s21_sscanf(str, fstr);
  int32_t res2 = sscanf(str, fstr);

  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sscanf_perc5) {
  int32_t a1 = 1234, a2 = 33333;
  int32_t b1 = 1234, b2 = 33333;

  const char str[] = "%%123%888";
  const char fstr[] = "%%%%%d%%%d";
  int32_t res1 = s21_sscanf(str, fstr, &a1, &b1);
  int32_t res2 = sscanf(str, fstr, &a2, &b2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
}
END_TEST

START_TEST(sscanf_mixed_ptrs1) {
  int *a1 = 0, *a2 = 0, *b1 = 0, *b2 = 0, *c1 = 0, *c2 = 0, *d1 = 0, *d2 = 0;

  const char str[] = "0xFFFF 0xAAA 7123 0xBBC1FF";
  const char fstr[] = "%p %p %p %p";

  int32_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int32_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_ptr_eq(a1, a2);
  ck_assert_ptr_eq(b1, b2);
  ck_assert_ptr_eq(c1, c2);
  ck_assert_ptr_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_mixed_ptrs2) {
  char *a1 = 0, *a2 = 0, *b1 = 0, *b2 = 0, *c1 = 0, *c2 = 0, *d1 = 0, *d2 = 0;

  const char str[] = "0x4 0x3 0x2 0x1";
  const char fstr[] = "%p %p %p %p";

  int32_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int32_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_ptr_eq(a1, a2);
  ck_assert_ptr_eq(b1, b2);
  ck_assert_ptr_eq(c1, c2);
  ck_assert_ptr_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_mixed_ptrs3) {
  int *a1 = 0, *a2 = 0, *b1 = 0, *b2 = 0, *c1 = 0, *c2 = 0, *d1 = 0, *d2 = 0;

  const char str[] = "03033 0333 0123 0123 0x123 0xFFFFF 0xBBC1FF";
  const char fstr[] = "%p %p %p %p";

  int32_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int32_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_ptr_eq(a1, a2);
  ck_assert_ptr_eq(b1, b2);
  ck_assert_ptr_eq(c1, c2);
  ck_assert_ptr_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_mixed_ptrs4) {
  int *a1 = 0, *a2 = 0, *b1 = 0, *b2 = 0, *c1 = 0, *c2 = 0, *d1 = 0, *d2 = 0;

  const char str[] = "0xABCDEF 0xAAA 7123 0xBBC1FF";
  const char fstr[] = "%p %p %p %p";

  int32_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int32_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_ptr_eq(a1, a2);
  ck_assert_ptr_eq(b1, b2);
  ck_assert_ptr_eq(c1, c2);
  ck_assert_ptr_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_mixed_ptrs5) {
  int *a1 = 0, *a2 = 0, *b1 = 0, *b2 = 0, *c1 = 0, *c2 = 0, *d1 = 0, *d2 = 0;

  const char str[] = "NULL";
  const char fstr[] = "%p %p %p %p";

  int32_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int32_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_ptr_eq(a1, a2);
  ck_assert_ptr_eq(b1, b2);
  ck_assert_ptr_eq(c1, c2);
  ck_assert_ptr_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_hard3) {
  char a1, a2;
  char b1[256] = {'\0'};
  char b2[256] = {'\0'};
  float c1, c2;
  short int d1, d2;
  long long int e1, e2;

  const char str[] = "$AmIIn%%sane? %\n\n\n \n \n \n\t   InF 0 %FIN9D-ME%";
  const char fstr[] = "%c%5s%%%*s %%  %G %hi %%FIN%lldDME%%";

  int32_t res1 = s21_sscanf(str, fstr, &a1, b1, &c1, &d1, &e1);
  int32_t res2 = sscanf(str, fstr, &a2, b2, &c2, &d2, &e2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_str_eq(b1, b2);
  ck_assert_float_infinite(c1);
  ck_assert_float_infinite(c2);
  ck_assert_int_eq(d1, d2);
  ck_assert_int_eq(e1, e2);
}
END_TEST

START_TEST(sscanf_hard4) {
  char a1, a2;
  char b1, b2;
  char c1, c2;
  char d1, d2;

  const char str[] = "%%$Char!StressssT%%estus!&&&";
  const char fstr[] = "%% %*c%*c%*c%*c%*c %c %c %c %c ### %*c";

  int32_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int32_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_hard5) {
  char a1, a2;
  char b1, b2;
  char c1, c2;
  char d1, d2;
  const char str[] =
      "%%$Char!StressssVIm User Aboba %% %%% %%% %% % % %% % "
      "% % %% % % %% %T%%estus!%%&&&";
  const char fstr[] =
      "%% %*c%*c%*c%*c%*c %c %c %c %c %% %% %% %% %% %% %% "
      "%% %% %% %% %% %% %% %% %% ### %*c";

  int32_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int32_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST
// sscanf <-

Suite *suite_sscanf_2(void) {
  Suite *s = suite_create("sscanf_2");
  TCase *tc = tcase_create("sscanf_2_tc");

  tcase_add_test(tc, sscanf_uint1);
  tcase_add_test(tc, sscanf_uint2);
  tcase_add_test(tc, sscanf_uint3);
  tcase_add_test(tc, sscanf_uint4);
  tcase_add_test(tc, sscanf_uint5);
  tcase_add_test(tc, sscanf_uint6);
  tcase_add_test(tc, sscanf_floats1);
  tcase_add_test(tc, sscanf_floats2);
  tcase_add_test(tc, sscanf_floats3);
  tcase_add_test(tc, sscanf_floats4);
  tcase_add_test(tc, sscanf_floats5);
  tcase_add_test(tc, sscanf_floats_sci1);
  tcase_add_test(tc, sscanf_floats_sci2);
  tcase_add_test(tc, sscanf_floats_sci3);
  tcase_add_test(tc, sscanf_floats_sci4);
  tcase_add_test(tc, sscanf_floats_sci5);
  tcase_add_test(tc, sscanf_upeer_hex_base_version);
  tcase_add_test(tc, sscanf_upeer_hex_overflow);
  tcase_add_test(tc, sscanf_upeer_hex_0x);
  tcase_add_test(tc, sscanf_upeer_hex_0X);
  tcase_add_test(tc, sscanf_upeer_hex_empty);
  tcase_add_test(tc, sscanf_upeer_hex_fail);
  tcase_add_test(tc, sscanf_upeer_hex_spaces_tabs_sns);
  tcase_add_test(tc, sscanf_upeer_hex_short);
  tcase_add_test(tc, sscanf_upeer_hex_long);
  tcase_add_test(tc, sscanf_upeer_hex_longlong);
  tcase_add_test(tc, sscanf_upeer_hex_2x);
  tcase_add_test(tc, sscanf_upeer_hex_star);
  tcase_add_test(tc, sscanf_upeer_hex_nohex);
  tcase_add_test(tc, sscanf_upeer_hex_lower);
  tcase_add_test(tc, sscanf_upeer_hex_sign);
  tcase_add_test(tc, upper_hex_len);
  tcase_add_test(tc, sscanf_lower_hex_base_version);
  tcase_add_test(tc, sscanf_lower_hex_overflow);
  tcase_add_test(tc, sscanf_lower_hex_0x);
  tcase_add_test(tc, sscanf_lower_hex_0X);
  tcase_add_test(tc, sscanf_lower_hex_empty);
  tcase_add_test(tc, sscanf_lower_hex_fail);
  tcase_add_test(tc, sscanf_lower_hex_spaces_tabs_sns);
  tcase_add_test(tc, sscanf_lower_hex_short);
  tcase_add_test(tc, sscanf_lower_hex_long);
  tcase_add_test(tc, sscanf_lower_hex_longlong);
  tcase_add_test(tc, sscanf_lower_hex_2x);
  tcase_add_test(tc, sscanf_lower_hex_star);
  tcase_add_test(tc, sscanf_lower_hex_nohex);
  tcase_add_test(tc, sscanf_lower_hex_lower);
  tcase_add_test(tc, sscanf_lower_hex_sign);
  tcase_add_test(tc, sscanf_lower_hex_len);
  tcase_add_test(tc, sscanf_octal_base_version);
  tcase_add_test(tc, sscanf_octal_overflow);
  tcase_add_test(tc, sscanf_octal_0x);
  tcase_add_test(tc, sscanf_octal_0X);
  tcase_add_test(tc, sscanf_octal_empty);
  tcase_add_test(tc, sscanf_octal_fail);
  tcase_add_test(tc, sscanf_octal_spaces_tabs_sns);
  tcase_add_test(tc, sscanf_octal_short);
  tcase_add_test(tc, sscanf_octal_long);
  tcase_add_test(tc, sscanf_octal_longlong);
  tcase_add_test(tc, sscanf_octal_2x);
  tcase_add_test(tc, sscanf_octal_star);
  tcase_add_test(tc, sscanf_octal_nohex);
  tcase_add_test(tc, sscanf_octal_lower);
  tcase_add_test(tc, sscanf_octal_sign);
  tcase_add_test(tc, sscanf_octal_len);
  tcase_add_test(tc, sscanf_pointer1);
  tcase_add_test(tc, sscanf_pointer2);
  tcase_add_test(tc, sscanf_pointer3);
  tcase_add_test(tc, sscanf_pointer4);
  tcase_add_test(tc, sscanf_buff1);
  tcase_add_test(tc, sscanf_buff2);
  tcase_add_test(tc, sscanf_buff3);
  tcase_add_test(tc, sscanf_perc1);
  tcase_add_test(tc, sscanf_perc2);
  tcase_add_test(tc, sscanf_perc3);
  tcase_add_test(tc, sscanf_perc4);
  tcase_add_test(tc, sscanf_perc5);
  tcase_add_test(tc, sscanf_mixed_ptrs1);
  tcase_add_test(tc, sscanf_mixed_ptrs2);
  tcase_add_test(tc, sscanf_mixed_ptrs3);
  tcase_add_test(tc, sscanf_mixed_ptrs4);
  tcase_add_test(tc, sscanf_mixed_ptrs5);
  tcase_add_test(tc, sscanf_hard1);
  tcase_add_test(tc, sscanf_hard3);
  tcase_add_test(tc, sscanf_hard4);
  tcase_add_test(tc, sscanf_hard5);

  suite_add_tcase(s, tc);
  return s;
}
