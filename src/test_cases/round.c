#include <check.h>
#include "../s21_decimal.h"

// s21_round TESTS
START_TEST(s21_round_test_1) {
  s21_decimal d = {{0, 0, 0, 0}, s21_NAN};
  d = s21_round(d);
    
  ck_assert_uint_eq(d.bits[0], 0);
  ck_assert_uint_eq(d.bits[1], 0);
  ck_assert_uint_eq(d.bits[2], 0);
  ck_assert_uint_eq(d.bits[3], 0);
  ck_assert_int_eq(d.value_type, s21_NAN);
}
END_TEST

START_TEST(s21_round_test_2) {
  s21_decimal d = {{0, 0, 0, 0}, s21_INFINITY};
  d = s21_round(d);
    
  ck_assert_uint_eq(d.bits[0], 0);
  ck_assert_uint_eq(d.bits[1], 0);
  ck_assert_uint_eq(d.bits[2], 0);
  ck_assert_uint_eq(d.bits[3], 0);
  ck_assert_int_eq(d.value_type, s21_INFINITY);
}
END_TEST

START_TEST(s21_round_test_3) {
  s21_decimal d = {{0, 0, 0, 0}, s21_NEGATIVE_INFINITY};
  d = s21_round(d);
    
  ck_assert_uint_eq(d.bits[0], 0);
  ck_assert_uint_eq(d.bits[1], 0);
  ck_assert_uint_eq(d.bits[2], 0);
  ck_assert_uint_eq(d.bits[3], 0);
  ck_assert_int_eq(d.value_type, s21_NEGATIVE_INFINITY);
}
END_TEST

START_TEST(s21_round_test_4) {
  s21_decimal d = {{0, 0, 0, 2147483648}, 0};  // -0
  d = s21_round(d);
    
  ck_assert_uint_eq(d.bits[0], 0);
  ck_assert_uint_eq(d.bits[1], 0);
  ck_assert_uint_eq(d.bits[2], 0);
  ck_assert_uint_eq(d.bits[3], 0);
  ck_assert_int_eq(d.value_type, 0);
}
END_TEST

START_TEST(s21_round_test_5) {
  s21_decimal d = {{0, 0, 0, 2149318656}, 0};  // -0*10^-28
  d = s21_round(d);
    
  ck_assert_uint_eq(d.bits[0], 0);
  ck_assert_uint_eq(d.bits[1], 0);
  ck_assert_uint_eq(d.bits[2], 0);
  ck_assert_uint_eq(d.bits[3], 0);
  ck_assert_int_eq(d.value_type, 0);
}
END_TEST

START_TEST(s21_round_test_6) {
  s21_decimal d = {{5, 0, 0, 65536}, 0};  // 0.5
  d = s21_round(d);
    
  ck_assert_uint_eq(d.bits[0], 0);
  ck_assert_uint_eq(d.bits[1], 0);
  ck_assert_uint_eq(d.bits[2], 0);
  ck_assert_uint_eq(d.bits[3], 0);
  ck_assert_int_eq(d.value_type, 0);
}
END_TEST

START_TEST(s21_round_test_7) {
  s21_decimal d = {{5, 0, 0, 2147549184}, 0};  // -0.5
  d = s21_round(d);
    
  ck_assert_uint_eq(d.bits[0], 0);
  ck_assert_uint_eq(d.bits[1], 0);
  ck_assert_uint_eq(d.bits[2], 0);
  ck_assert_uint_eq(d.bits[3], 0);
  ck_assert_int_eq(d.value_type, 0);
}
END_TEST

START_TEST(s21_round_test_8) {
  s21_decimal d = {{6, 0, 0, 65536}, 0};  // 0.6
  d = s21_round(d);
    
  ck_assert_uint_eq(d.bits[0], 1);
  ck_assert_uint_eq(d.bits[1], 0);
  ck_assert_uint_eq(d.bits[2], 0);
  ck_assert_uint_eq(d.bits[3], 0);
  ck_assert_int_eq(d.value_type, 0);
}
END_TEST

START_TEST(s21_round_test_9) {
  s21_decimal d = {{6, 0, 0, 2147549184}, 0};  // -0.6
  d = s21_round(d);
    
  ck_assert_uint_eq(d.bits[0], 1);
  ck_assert_uint_eq(d.bits[1], 0);
  ck_assert_uint_eq(d.bits[2], 0);
  ck_assert_uint_eq(d.bits[3], 2147483648);
  ck_assert_int_eq(d.value_type, 0);
}
END_TEST

START_TEST(s21_round_test_10) {
  s21_decimal d = {{501, 0, 0, 196608}, 0};  // 0.501
  d = s21_round(d);
    
  ck_assert_uint_eq(d.bits[0], 1);
  ck_assert_uint_eq(d.bits[1], 0);
  ck_assert_uint_eq(d.bits[2], 0);
  ck_assert_uint_eq(d.bits[3], 0);
  ck_assert_int_eq(d.value_type, 0);
}
END_TEST

START_TEST(s21_round_test_11) {
  s21_decimal d = {{501, 0, 0, 2147680256}, 0};  // -0.501
  d = s21_round(d);
    
  ck_assert_uint_eq(d.bits[0], 1);
  ck_assert_uint_eq(d.bits[1], 0);
  ck_assert_uint_eq(d.bits[2], 0);
  ck_assert_uint_eq(d.bits[3], 2147483648);
  ck_assert_int_eq(d.value_type, 0);
}
END_TEST

START_TEST(s21_round_test_12) {
  s21_decimal d = {{4294967295, 4294967295, 4294967295, 1835008}, 0};  // max_decimal*10^-28
  d = s21_round(d);
    
  ck_assert_uint_eq(d.bits[0], 8);
  ck_assert_uint_eq(d.bits[1], 0);
  ck_assert_uint_eq(d.bits[2], 0);
  ck_assert_uint_eq(d.bits[3], 0);
  ck_assert_int_eq(d.value_type, 0);
}
END_TEST
