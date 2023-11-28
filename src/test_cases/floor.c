#include <check.h>

#include "../s21_decimal.h"

// s21_floor TESTS
START_TEST(s21_floor_test1) {
  float f1 = 1.5;
  float f2 = 1.0;
  s21_decimal d;

  ck_assert_int_eq(s21_from_float_to_decimal(f1, &d), 0);
  d = s21_floor(d);
  ck_assert_int_eq(s21_from_decimal_to_float(d, &f1), 0);
  ck_assert_float_eq(f1, f2);
}
END_TEST

START_TEST(s21_floor_test2) {
  float f1 = 0.0;
  float f2 = 0.0;
  s21_decimal d;

  ck_assert_int_eq(s21_from_float_to_decimal(f1, &d), 0);
  d = s21_floor(d);
  ck_assert_int_eq(s21_from_decimal_to_float(d, &f1), 0);
  ck_assert_float_eq(f1, f2);
}
END_TEST

START_TEST(s21_floor_test3) {
  float f1 = -2.0;
  float f2 = -2.0;
  s21_decimal d;

  ck_assert_int_eq(s21_from_float_to_decimal(f1, &d), 0);
  d = s21_floor(d);
  ck_assert_int_eq(s21_from_decimal_to_float(d, &f1), 0);
  ck_assert_float_eq(f1, f2);
}
END_TEST

START_TEST(s21_floor_test4) {
  float f1 = -2.5;
  float f2 = -3.0;
  s21_decimal d;

  ck_assert_int_eq(s21_from_float_to_decimal(f1, &d), 0);
  d = s21_floor(d);
  ck_assert_int_eq(s21_from_decimal_to_float(d, &f1), 0);
  ck_assert_float_eq(f1, f2);
}
END_TEST
