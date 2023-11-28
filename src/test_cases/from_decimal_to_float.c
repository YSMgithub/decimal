#include <check.h>

#include "../s21_decimal.h"

// s21_from_decimal_to_float TESTS
START_TEST(s21_from_decimal_to_float_test1) {
  float f1 = 1.23;
  float f2;
  s21_decimal d;

  int error1 = s21_from_float_to_decimal(f1, &d);
  ck_assert_int_eq(error1, 0);
  int error2 = s21_from_decimal_to_float(d, &f2);
  ck_assert_int_eq(error2, 0);
  ck_assert_float_eq(f1, f2);
}
END_TEST

START_TEST(s21_from_decimal_to_float_test2) {
  float f1 = -INFINITY;
  float f2;
  s21_decimal d;

  ck_assert_int_eq(s21_from_float_to_decimal(f1, &d), 1);
  ck_assert_int_eq(s21_from_decimal_to_float(d, &f2), 1);
  ck_assert_float_eq(f1, f2);
}
END_TEST

START_TEST(s21_from_decimal_to_float_test3) {
  float f1 = INFINITY;
  float f2;
  s21_decimal d;

  ck_assert_int_eq(s21_from_float_to_decimal(f1, &d), 1);
  ck_assert_int_eq(s21_from_decimal_to_float(d, &f2), 1);
  ck_assert_float_eq(f1, f2);
}
END_TEST

START_TEST(s21_from_decimal_to_float_test4) {
  float f1 = 0.1234567;
  float f2;
  s21_decimal d;

  ck_assert_int_eq(s21_from_float_to_decimal(f1, &d), 0);
  ck_assert_int_eq(s21_from_decimal_to_float(d, &f2), 0);
  ck_assert_float_eq(f1, f2);
}
END_TEST
