#include <check.h>
#include "../s21_decimal.h"

// s21_from_int_to_decimal TESTS
START_TEST(s21_from_int_to_decimal_test1) {
  int i = -7;
  s21_decimal d;

  ck_assert_int_eq(s21_from_int_to_decimal(i, &d), 0);
  ck_assert_uint_eq(d.bits[0], 0b00000000000000000000000000000111);
  ck_assert_uint_eq(d.bits[3], 0b10000000000000000000000000000000);
}
END_TEST

START_TEST(s21_from_int_to_decimal_test2) {
  int i = 0;
  s21_decimal d;

  ck_assert_int_eq(s21_from_int_to_decimal(i, &d), 0);
  ck_assert_uint_eq(d.bits[LOW], 0);
  ck_assert_uint_eq(d.bits[MID], 0);
  ck_assert_uint_eq(d.bits[HIGH], 0);
  ck_assert_uint_eq(d.bits[SCALE], 0);
}
END_TEST
