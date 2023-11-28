#include <check.h>
#include "../s21_decimal.h"

// s21_is_greater TESTS
START_TEST(s21_is_greater_test_1) {
  s21_decimal d1 = {{0, 0, 0, 0}, s21_NAN};
  s21_decimal d2 = {{0, 0, 0, 0}, s21_NAN};
  ck_assert_int_eq(s21_is_greater(d1, d2), 1);
  }
END_TEST

START_TEST(s21_is_greater_test_2) {
  s21_decimal d1 = {{0, 0, 0, 0}, s21_INFINITY};
  s21_decimal d2 = {{0, 0, 0, 0}, s21_INFINITY};
  ck_assert_int_eq(s21_is_greater(d1, d2), 1);
  }
END_TEST

START_TEST(s21_is_greater_test_3) {
  s21_decimal d1 = {{0, 0, 0, 0}, s21_NEGATIVE_INFINITY};
  s21_decimal d2 = {{0, 0, 0, 0}, s21_NEGATIVE_INFINITY};
  ck_assert_int_eq(s21_is_greater(d1, d2), 1);
  }
END_TEST

START_TEST(s21_is_greater_test_4) {
  s21_decimal d1 = {{0, 0, 0, 0}, s21_NAN};
  s21_decimal d2 = {{10, 0, 0, 0}, 0}; 
  ck_assert_int_eq(s21_is_greater(d1, d2), 1);
  }
END_TEST

START_TEST(s21_is_greater_test_5) {
  s21_decimal d1 = {{10, 0, 0, 0}, 0};
  s21_decimal d2 = {{0, 0, 0, 0}, s21_NAN};
  ck_assert_int_eq(s21_is_greater(d1, d2), 1);
  }
END_TEST

START_TEST(s21_is_greater_test_6) {
  s21_decimal d1 = {{0, 0, 0, 0}, s21_INFINITY};
  s21_decimal d2 = {{10, 0, 0, 0}, 0};
  ck_assert_int_eq(s21_is_greater(d1, d2), 0);
  }
END_TEST

START_TEST(s21_is_greater_test_7) {
  s21_decimal d1 = {{10, 0, 0, 0}, 0};
  s21_decimal d2 = {{0, 0, 0, 0}, s21_INFINITY};
  ck_assert_int_eq(s21_is_greater(d1, d2), 1);
  }
END_TEST

START_TEST(s21_is_greater_test_8) {
  s21_decimal d1 = {{0, 0, 0, 0}, s21_INFINITY}; 
  s21_decimal d2 = {{10, 0, 0, 2147483648}, 0};  // -10
  ck_assert_int_eq(s21_is_greater(d1, d2), 0);
  }
END_TEST

START_TEST(s21_is_greater_test_9) {
  s21_decimal d1 = {{10, 0, 0, 2147483648}, 0};  // -10
  s21_decimal d2 = {{0, 0, 0, 0}, s21_INFINITY};
  ck_assert_int_eq(s21_is_greater(d1, d2), 1);
  }
END_TEST

START_TEST(s21_is_greater_test_10) {
  s21_decimal d1 = {{0, 0, 0, 0}, s21_INFINITY};
  s21_decimal d2 = {{0, 0, 0, 0}, s21_NEGATIVE_INFINITY};
  ck_assert_int_eq(s21_is_greater(d1, d2), 0);
  }
END_TEST

START_TEST(s21_is_greater_test_11) {
  s21_decimal d1 = {{0, 0, 0, 0}, s21_NEGATIVE_INFINITY};
  s21_decimal d2 = {{0, 0, 0, 0}, s21_INFINITY};
  ck_assert_int_eq(s21_is_greater(d1, d2), 1);
  }
END_TEST

START_TEST(s21_is_greater_test_12) {
  s21_decimal d1 = {{0, 0, 0, 0}, s21_NEGATIVE_INFINITY};
  s21_decimal d2 = {{25, 0, 0, 0}, 0};  // 25
  ck_assert_int_eq(s21_is_greater(d1, d2), 1);
  }
END_TEST

START_TEST(s21_is_greater_test_13) {
  s21_decimal d1 = {{25, 0, 0, 0}, 0};  // 25
  s21_decimal d2 = {{0, 0, 0, 0}, s21_NEGATIVE_INFINITY};
  ck_assert_int_eq(s21_is_greater(d1, d2), 0);
  }
END_TEST

START_TEST(s21_is_greater_test_14) {
  s21_decimal d1 = {{0, 0, 0, 0}, s21_NEGATIVE_INFINITY};
  s21_decimal d2 = {{25, 0, 0, 2147483648}, 0};  // -25
  ck_assert_int_eq(s21_is_greater(d1, d2), 1);
  }
END_TEST

START_TEST(s21_is_greater_test_15) {
  s21_decimal d1 = {{25, 0, 0, 2147483648}, 0};  // -25
  s21_decimal d2 = {{0, 0, 0, 0}, s21_NEGATIVE_INFINITY};
  ck_assert_int_eq(s21_is_greater(d1, d2), 0);
  }
END_TEST

START_TEST(s21_is_greater_test_16) {
  s21_decimal d1 = {{0, 0, 0, 0}, 0};
  s21_decimal d2 = {{0, 0, 0, 0}, 0};
  ck_assert_int_eq(s21_is_greater(d1, d2), 1);
  }
END_TEST

START_TEST(s21_is_greater_test_17) {
  s21_decimal d1 = {{0, 0, 0, 0}, 0};
  s21_decimal d2 = {{0, 0, 0, 2147483648}, 0};  // -0
  ck_assert_int_eq(s21_is_greater(d1, d2), 1);
  }
END_TEST

START_TEST(s21_is_greater_test_18) {
  s21_decimal d1 = {{0, 0, 0, 2147483648}, 0};  // -0
  s21_decimal d2 = {{0, 0, 0, 0}, 0};
  ck_assert_int_eq(s21_is_greater(d1, d2), 1);
  }
END_TEST

START_TEST(s21_is_greater_test_19) {
  s21_decimal d1 = {{1, 0, 0, 0}, 0};
  s21_decimal d2 = {{2, 0, 0, 0}, 0};
  ck_assert_int_eq(s21_is_greater(d1, d2), 1);
  }
END_TEST

START_TEST(s21_is_greater_test_20) {
  s21_decimal d1 = {{2, 0, 0, 0}, 0};
  s21_decimal d2 = {{1, 0, 0, 0}, 0};
  ck_assert_int_eq(s21_is_greater(d1, d2), 0);
  }
END_TEST

START_TEST(s21_is_greater_test_21) {
  s21_decimal d1 = {{1, 0, 0, 2147483648}, 0};  // -1
  s21_decimal d2 = {{2, 0, 0, 0}, 0};
  ck_assert_int_eq(s21_is_greater(d1, d2), 1);
  }
END_TEST

START_TEST(s21_is_greater_test_22) {
  s21_decimal d1 = {{2, 0, 0, 0}, 0};
  s21_decimal d2 = {{1, 0, 0, 2147483648}, 0};  // -1
  ck_assert_int_eq(s21_is_greater(d1, d2), 0);
  }
END_TEST

START_TEST(s21_is_greater_test_23) {
  s21_decimal d1 = {{1, 0, 0, 2147483648}, 0};  // -1
  s21_decimal d2 = {{2, 0, 0, 2147483648}, 0};  // -2
  ck_assert_int_eq(s21_is_greater(d1, d2), 0);
  }
END_TEST

START_TEST(s21_is_greater_test_24) {
  s21_decimal d1 = {{2, 0, 0, 2147483648}, 0};  // -2
  s21_decimal d2 = {{1, 0, 0, 2147483648}, 0};  // -1
  ck_assert_int_eq(s21_is_greater(d1, d2), 1);
  }
END_TEST

START_TEST(s21_is_greater_test_25) {
  s21_decimal d1 = {{25, 0, 0, 131072}, 0};  // 0.25
  s21_decimal d2 = {{251, 0, 0, 196608}, 0};  // 0.251
  ck_assert_int_eq(s21_is_greater(d1, d2), 1);
  }
END_TEST

START_TEST(s21_is_greater_test_26) {
  s21_decimal d1 = {{251, 0, 0, 196608}, 0};  // 0.251
  s21_decimal d2 = {{25, 0, 0, 131072}, 0};  // 0.25
  ck_assert_int_eq(s21_is_greater(d1, d2), 0);
  }
END_TEST

START_TEST(s21_is_greater_test_27) {
  s21_decimal d1 = {{25, 0, 0, 2147614720}, 0};  // -0.25
  s21_decimal d2 = {{251, 0, 0, 2147680256}, 0};  // -0.251
  ck_assert_int_eq(s21_is_greater(d1, d2), 0);
  }
END_TEST

START_TEST(s21_is_greater_test_28) {
  s21_decimal d1 = {{251, 0, 0, 2147680256}, 0};  // -0.251
  s21_decimal d2 = {{25, 0, 0, 2147614720}, 0};  // -0.25
  ck_assert_int_eq(s21_is_greater(d1, d2), 1);
  }
END_TEST

START_TEST(s21_is_greater_test_29) {
  s21_decimal d1 = {{1, 0, 0, 1835008}, 0};  // 1*10^-28
  s21_decimal d2 = {{1, 0, 0, 1769472}, 0};  // 1*10^-27
  ck_assert_int_eq(s21_is_greater(d1, d2), 1);
  }
END_TEST

START_TEST(s21_is_greater_test_30) {
  s21_decimal d1 = {{1, 0, 0, 1769472}, 0};  // 1*10^-27
  s21_decimal d2 = {{1, 0, 0, 1835008}, 0};  // 1*10^-28
  ck_assert_int_eq(s21_is_greater(d1, d2), 0);
  }
END_TEST

START_TEST(s21_is_greater_test_31) {
  s21_decimal d1 = {{4294967295, 4294967295, 4294967295, 0}, 0};  // max_decimal
  s21_decimal d2 = {{4294967295, 4294967295, 4294967295, 1835008}, 0};  // max_decimal*10^-28
  ck_assert_int_eq(s21_is_greater(d1, d2), 0);
  }
END_TEST

START_TEST(s21_is_greater_test_32) {
  s21_decimal d1 = {{4294967295, 4294967295, 4294967295, 1835008}, 0};  // max_decimal*10^-28
  s21_decimal d2 = {{4294967295, 4294967295, 4294967295, 0}, 0};  // max_decimal
  ck_assert_int_eq(s21_is_greater(d1, d2), 1);
  }
END_TEST

START_TEST(s21_is_greater_test_33) {
  s21_decimal d1 = {{2576980378, 2576980377, 429496729, 0}, 0};  // 7922816251426433759354395034 (28 цифр)
  s21_decimal d2 = {{4294967295, 4294967295, 4294967295, 65536}, 0};  // max_decimal*10^-1
  ck_assert_int_eq(s21_is_greater(d1, d2), 0);
  }
END_TEST

START_TEST(s21_is_greater_test_34) {
  s21_decimal d1 = {{4294967295, 4294967295, 4294967295, 65536}, 0};  // max_decimal*10^-1
  s21_decimal d2 = {{2576980378, 2576980377, 429496729, 0}, 0};  // 7922816251426433759354395034 (28 цифр)
  ck_assert_int_eq(s21_is_greater(d1, d2), 1);
  }
END_TEST

START_TEST(s21_is_greater_test_35) {
  s21_decimal d1 = {{15, 0, 0, 65536}, 0};  // 1.5
  s21_decimal d2 = {{2, 0, 0, 0}, 0};  // 2
  ck_assert_int_eq(s21_is_greater(d1, d2), 1);
  }
END_TEST

START_TEST(s21_is_greater_test_36) {
  s21_decimal d1 = {{2, 0, 0, 0}, 0};  // 2
  s21_decimal d2 = {{15, 0, 0, 65536}, 0};  // 1.5
  ck_assert_int_eq(s21_is_greater(d1, d2), 0);
  }
END_TEST
