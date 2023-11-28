#include <check.h>
#include "../s21_decimal.h"

// s21_negate TESTS
START_TEST(s21_negate_test1) {
  s21_decimal d = {{0, 0, 0, 0}, s21_NORMAL_VALUE};

  d = s21_negate(d);
  ck_assert_uint_eq(d.bits[3], 0b10000000000000000000000000000000);
}
END_TEST

START_TEST(s21_negate_test2) {
  s21_decimal d = {{0, 0, 0, 0}, s21_INFINITY};

  d = s21_negate(d);
  ck_assert_int_eq(d.value_type, s21_NEGATIVE_INFINITY);
}
END_TEST

START_TEST(s21_negate_test3) {
  s21_decimal d = {{0, 0, 0, 0}, s21_NEGATIVE_INFINITY};

  d = s21_negate(d);
  ck_assert_int_eq(d.value_type, s21_INFINITY);
}
END_TEST
