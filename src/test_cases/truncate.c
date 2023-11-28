#include <check.h>
#include "../s21_decimal.h"

// s21_truncate TESTS
START_TEST(s21_truncate_test1) {
  float f1 = 867.5309;
  float f2 = 867.0;
  s21_decimal d;

  int error = s21_from_float_to_decimal(f1, &d);
  ck_assert_int_eq(error, 0);
  d = s21_truncate(d);
  error = s21_from_decimal_to_float(d, &f1);
  ck_assert_int_eq(error, 0);
  ck_assert_float_eq(f1, f2);
}
END_TEST
