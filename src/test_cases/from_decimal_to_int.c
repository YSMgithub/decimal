#include <check.h>
#include "../s21_decimal.h"

// s21_from_decimal_to_int TESTS
START_TEST(s21_from_decimal_to_int_test1) {
  int i1 = -8675309;
  int i2;
  s21_decimal d;

  ck_assert_int_eq(s21_from_int_to_decimal(i1, &d), 0);
  ck_assert_int_eq(s21_from_decimal_to_int(d, &i2), 0);
  ck_assert_int_eq(i1, i2);
}
END_TEST

START_TEST(s21_from_decimal_to_int_test2) {
  int i1 = -0;
  int i2;
  s21_decimal d;

  ck_assert_int_eq(s21_from_int_to_decimal(i1, &d), 0);
  ck_assert_int_eq(s21_from_decimal_to_int(d, &i2), 0);
  ck_assert_int_eq(i1, i2);
}
END_TEST
