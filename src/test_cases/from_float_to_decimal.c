#include <check.h>

#include "../s21_decimal.h"

// s21_from_float_to_decimal TESTS
START_TEST(s21_from_float_to_decimal_test1) {
  s21_decimal d;
  float f = -0.0;

  int error = s21_from_float_to_decimal(f, &d);
  ck_assert_int_eq(error, 0);
  ck_assert_uint_eq(d.bits[0], 0);
  ck_assert_uint_eq(d.bits[1], 0);
  ck_assert_uint_eq(d.bits[2], 0);
  ck_assert_uint_eq(d.bits[3], 0b10000000000000000000000000000000);
  ck_assert_int_eq(d.value_type, 0);
}
END_TEST

START_TEST(s21_from_float_to_decimal_test2) {
  s21_decimal d;
  float f = 12345.0;

  int error = s21_from_float_to_decimal(f, &d);
  ck_assert_int_eq(error, 0);
  ck_assert_uint_eq(d.bits[0], 0b00000000101111000101111010101000);
  ck_assert_uint_eq(d.bits[1], 0);
  ck_assert_uint_eq(d.bits[2], 0);
  ck_assert_uint_eq(d.bits[3], 0b00000000000000110000000000000000);
  ck_assert_int_eq(d.value_type, 0);
}
END_TEST

START_TEST(s21_from_float_to_decimal_test3) {
  s21_decimal d;
  float f = 1.0E+38;

  ck_assert_int_eq(s21_from_float_to_decimal(f, &d), 1);
  ck_assert_int_eq(d.value_type, s21_INFINITY);
}
END_TEST

START_TEST(s21_from_float_to_decimal_test4) {
  float f = 0.0;

  ck_assert_int_eq(s21_from_float_to_decimal(f, NULL), 1);
}
END_TEST
