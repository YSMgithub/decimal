#include <check.h>

#include "../s21_decimal.h"

// s21_add TESTS
START_TEST(s21_add_test_1) {
  s21_decimal d1 = {{0, 0, 0, 0}, s21_NAN};
  s21_decimal d2 = {{0, 0, 0, 0}, s21_NAN};
  s21_decimal res = s21_add(d1, d2);
  ck_assert_int_eq(res.value_type, s21_NAN);
  ck_assert_uint_eq(res.bits[0], 0);
  ck_assert_uint_eq(res.bits[1], 0);
  ck_assert_uint_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 0);
}
END_TEST

START_TEST(s21_add_test_2) {
  s21_decimal d1 = {{0, 0, 0, 0}, s21_INFINITY};
  s21_decimal d2 = {{0, 0, 0, 0}, s21_INFINITY};
  s21_decimal res = s21_add(d1, d2);
  ck_assert_int_eq(res.value_type, s21_INFINITY);
  ck_assert_uint_eq(res.bits[0], 0);
  ck_assert_uint_eq(res.bits[1], 0);
  ck_assert_uint_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 0);
}
END_TEST

START_TEST(s21_add_test_3) {
  s21_decimal d1 = {{0, 0, 0, 0}, s21_NEGATIVE_INFINITY};
  s21_decimal d2 = {{0, 0, 0, 0}, s21_NEGATIVE_INFINITY};
  s21_decimal res = s21_add(d1, d2);
  ck_assert_int_eq(res.value_type, s21_NEGATIVE_INFINITY);
  ck_assert_uint_eq(res.bits[0], 0);
  ck_assert_uint_eq(res.bits[1], 0);
  ck_assert_uint_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 0);
}
END_TEST

START_TEST(s21_add_test_4) {
  s21_decimal d1 = {{0, 0, 0, 0}, s21_NAN};
  s21_decimal d2 = {{0, 0, 0, 0}, s21_INFINITY};
  s21_decimal res = s21_add(d1, d2);
  ck_assert_int_eq(res.value_type, s21_NAN);
  ck_assert_uint_eq(res.bits[0], 0);
  ck_assert_uint_eq(res.bits[1], 0);
  ck_assert_uint_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 0);
}
END_TEST

START_TEST(s21_add_test_5) {
  s21_decimal d1 = {{0, 0, 0, 0}, s21_NAN};
  s21_decimal d2 = {{0, 0, 0, 0}, s21_NEGATIVE_INFINITY};
  s21_decimal res = s21_add(d1, d2);
  ck_assert_int_eq(res.value_type, s21_NAN);
  ck_assert_uint_eq(res.bits[0], 0);
  ck_assert_uint_eq(res.bits[1], 0);
  ck_assert_uint_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 0);
}
END_TEST

START_TEST(s21_add_test_6) {
  s21_decimal d1 = {{0, 0, 0, 0}, s21_NAN};
  s21_decimal d2 = {{1, 0, 0, 0}, 0};
  s21_decimal res = s21_add(d1, d2);
  ck_assert_int_eq(res.value_type, s21_NAN);
  ck_assert_uint_eq(res.bits[0], 0);
  ck_assert_uint_eq(res.bits[1], 0);
  ck_assert_uint_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 0);
}
END_TEST

START_TEST(s21_add_test_7) {
  s21_decimal d1 = {{0, 0, 0, 0}, s21_NAN};
  s21_decimal d2 = {{1, 0, 0, 2147483648}, 0};  // -1
  s21_decimal res = s21_add(d1, d2);
  ck_assert_int_eq(res.value_type, s21_NAN);
  ck_assert_uint_eq(res.bits[0], 0);
  ck_assert_uint_eq(res.bits[1], 0);
  ck_assert_uint_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 0);
}
END_TEST

START_TEST(s21_add_test_8) {
  s21_decimal d1 = {{0, 0, 0, 0}, s21_INFINITY};
  s21_decimal d2 = {{1, 0, 0, 0}, 0};
  s21_decimal res = s21_add(d1, d2);
  ck_assert_int_eq(res.value_type, s21_INFINITY);
  ck_assert_uint_eq(res.bits[0], 0);
  ck_assert_uint_eq(res.bits[1], 0);
  ck_assert_uint_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 0);
}
END_TEST

START_TEST(s21_add_test_9) {
  s21_decimal d1 = {{1, 0, 0, 0}, 0};
  s21_decimal d2 = {{0, 0, 0, 0}, s21_INFINITY};
  s21_decimal res = s21_add(d1, d2);
  ck_assert_int_eq(res.value_type, s21_INFINITY);
  ck_assert_uint_eq(res.bits[0], 0);
  ck_assert_uint_eq(res.bits[1], 0);
  ck_assert_uint_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 0);
}
END_TEST

START_TEST(s21_add_test_10) {
  s21_decimal d1 = {{0, 0, 0, 0}, s21_INFINITY};
  s21_decimal d2 = {{1, 0, 0, 2147483648}, 0};  // -1
  s21_decimal res = s21_add(d1, d2);
  ck_assert_int_eq(res.value_type, s21_INFINITY);
  ck_assert_uint_eq(res.bits[0], 0);
  ck_assert_uint_eq(res.bits[1], 0);
  ck_assert_uint_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 0);
}
END_TEST

START_TEST(s21_add_test_11) {
  s21_decimal d1 = {{1, 0, 0, 2147483648}, 0};  // -1
  s21_decimal d2 = {{0, 0, 0, 0}, s21_INFINITY};
  s21_decimal res = s21_add(d1, d2);
  ck_assert_int_eq(res.value_type, s21_INFINITY);
  ck_assert_uint_eq(res.bits[0], 0);
  ck_assert_uint_eq(res.bits[1], 0);
  ck_assert_uint_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 0);
}
END_TEST

START_TEST(s21_add_test_12) {
  s21_decimal d1 = {{0, 0, 0, 0}, s21_INFINITY};
  s21_decimal d2 = {{0, 0, 0, 0}, s21_NEGATIVE_INFINITY};
  s21_decimal res = s21_add(d1, d2);
  ck_assert_int_eq(res.value_type, s21_NAN);
  ck_assert_uint_eq(res.bits[0], 0);
  ck_assert_uint_eq(res.bits[1], 0);
  ck_assert_uint_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 0);
}
END_TEST

START_TEST(s21_add_test_13) {
  s21_decimal d1 = {{0, 0, 0, 0}, s21_NEGATIVE_INFINITY};
  s21_decimal d2 = {{0, 0, 0, 0}, s21_INFINITY};
  s21_decimal res = s21_add(d1, d2);
  ck_assert_int_eq(res.value_type, s21_NAN);
  ck_assert_uint_eq(res.bits[0], 0);
  ck_assert_uint_eq(res.bits[1], 0);
  ck_assert_uint_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 0);
}
END_TEST

START_TEST(s21_add_test_14) {
  s21_decimal d1 = {{0, 0, 0, 0}, s21_NEGATIVE_INFINITY};
  s21_decimal d2 = {{100, 0, 0, 0}, 0};
  s21_decimal res = s21_add(d1, d2);
  ck_assert_int_eq(res.value_type, s21_NEGATIVE_INFINITY);
  ck_assert_uint_eq(res.bits[0], 0);
  ck_assert_uint_eq(res.bits[1], 0);
  ck_assert_uint_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 0);
}
END_TEST

START_TEST(s21_add_test_15) {
  s21_decimal d1 = {{100, 0, 0, 0}, 0};
  s21_decimal d2 = {{0, 0, 0, 0}, s21_NEGATIVE_INFINITY};
  s21_decimal res = s21_add(d1, d2);
  ck_assert_int_eq(res.value_type, s21_NEGATIVE_INFINITY);
  ck_assert_uint_eq(res.bits[0], 0);
  ck_assert_uint_eq(res.bits[1], 0);
  ck_assert_uint_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 0);
}
END_TEST

START_TEST(s21_add_test_16) {
  s21_decimal d1 = {{0, 0, 0, 0}, s21_NEGATIVE_INFINITY};
  s21_decimal d2 = {{100, 0, 0, 2147483648}, 0};  // -100
  s21_decimal res = s21_add(d1, d2);
  ck_assert_int_eq(res.value_type, s21_NEGATIVE_INFINITY);
  ck_assert_uint_eq(res.bits[0], 0);
  ck_assert_uint_eq(res.bits[1], 0);
  ck_assert_uint_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 0);
}
END_TEST

START_TEST(s21_add_test_17) {
  s21_decimal d1 = {{100, 0, 0, 2147483648}, 0};  // -100
  s21_decimal d2 = {{0, 0, 0, 0}, s21_NEGATIVE_INFINITY};
  s21_decimal res = s21_add(d1, d2);
  ck_assert_int_eq(res.value_type, s21_NEGATIVE_INFINITY);
  ck_assert_uint_eq(res.bits[0], 0);
  ck_assert_uint_eq(res.bits[1], 0);
  ck_assert_uint_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 0);
}
END_TEST

START_TEST(s21_add_test_18) {
  s21_decimal d1 = {{0, 0, 0, 196608}, 0};  // 0.000
  s21_decimal d2 = {{0, 0, 0, 0}, 0};
  s21_decimal res = s21_add(d1, d2);
  ck_assert_int_eq(res.value_type, 0);
  ck_assert_uint_eq(res.bits[0], 0);
  ck_assert_uint_eq(res.bits[1], 0);
  ck_assert_uint_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 196608);  // ответ 0.000
}
END_TEST

START_TEST(s21_add_test_19) {
  s21_decimal d1 = {{0, 0, 0, 0}, 0};
  s21_decimal d2 = {{0, 0, 0, 2147483648}, 0};  // -0
  s21_decimal res = s21_add(d1, d2);
  ck_assert_int_eq(res.value_type, 0);
  ck_assert_uint_eq(res.bits[0], 0);
  ck_assert_uint_eq(res.bits[1], 0);
  ck_assert_uint_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 0);
}
END_TEST

START_TEST(s21_add_test_20) {
  s21_decimal d1 = {{0, 0, 0, 2147483648}, 0};  // -0
  s21_decimal d2 = {{0, 0, 0, 196608}, 0};      // 0.000
  s21_decimal res = s21_add(d1, d2);
  ck_assert_int_eq(res.value_type, 0);
  ck_assert_uint_eq(res.bits[0], 0);
  ck_assert_uint_eq(res.bits[1], 0);
  ck_assert_uint_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 196608);  // ответ 0.000
}
END_TEST

START_TEST(s21_add_test_21) {
  s21_decimal d1 = {{0, 0, 0, 2147483648}, 0};  // -0
  s21_decimal d2 = {{0, 0, 0, 2147483648}, 0};  // -0
  s21_decimal res = s21_add(d1, d2);
  ck_assert_int_eq(res.value_type, 0);
  ck_assert_uint_eq(res.bits[0], 0);
  ck_assert_uint_eq(res.bits[1], 0);
  ck_assert_uint_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 0);  // ответ 0
}
END_TEST

START_TEST(s21_add_test_22) {
  s21_decimal d1 = {{1, 0, 0, 0}, 0};  // 1
  s21_decimal d2 = {{2, 0, 0, 0}, 0};  // 2
  s21_decimal res = s21_add(d1, d2);
  ck_assert_int_eq(res.value_type, 0);
  ck_assert_uint_eq(res.bits[0], 3);
  ck_assert_uint_eq(res.bits[1], 0);
  ck_assert_uint_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 0);
}
END_TEST

START_TEST(s21_add_test_23) {
  s21_decimal d1 = {{2, 0, 0, 0}, 0};  // 2
  s21_decimal d2 = {{1, 0, 0, 0}, 0};  // 1
  s21_decimal res = s21_add(d1, d2);
  ck_assert_int_eq(res.value_type, 0);
  ck_assert_uint_eq(res.bits[0], 3);
  ck_assert_uint_eq(res.bits[1], 0);
  ck_assert_uint_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 0);
}
END_TEST

START_TEST(s21_add_test_24) {
  s21_decimal d1 = {{1, 0, 0, 0}, 0};           // 1
  s21_decimal d2 = {{2, 0, 0, 2147483648}, 0};  // -2
  s21_decimal res = s21_add(d1, d2);
  ck_assert_int_eq(res.value_type, 0);
  ck_assert_uint_eq(res.bits[0], 1);
  ck_assert_uint_eq(res.bits[1], 0);
  ck_assert_uint_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 2147483648);
}
END_TEST

START_TEST(s21_add_test_25) {
  s21_decimal d1 = {{2, 0, 0, 2147483648}, 0};  // -2
  s21_decimal d2 = {{1, 0, 0, 0}, 0};           // 1
  s21_decimal res = s21_add(d1, d2);
  ck_assert_int_eq(res.value_type, 0);
  ck_assert_uint_eq(res.bits[0], 1);
  ck_assert_uint_eq(res.bits[1], 0);
  ck_assert_uint_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 2147483648);
}
END_TEST

START_TEST(s21_add_test_26) {
  s21_decimal d1 = {{1, 0, 0, 2147483648}, 0};  // -1
  s21_decimal d2 = {{2, 0, 0, 0}, 0};           // 2
  s21_decimal res = s21_add(d1, d2);
  ck_assert_int_eq(res.value_type, 0);
  ck_assert_uint_eq(res.bits[0], 1);
  ck_assert_uint_eq(res.bits[1], 0);
  ck_assert_uint_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 0);
}
END_TEST

START_TEST(s21_add_test_27) {
  s21_decimal d1 = {{2, 0, 0, 0}, 0};           // 2
  s21_decimal d2 = {{1, 0, 0, 2147483648}, 0};  // -1
  s21_decimal res = s21_add(d1, d2);
  ck_assert_int_eq(res.value_type, 0);
  ck_assert_uint_eq(res.bits[0], 1);
  ck_assert_uint_eq(res.bits[1], 0);
  ck_assert_uint_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 0);
}
END_TEST

START_TEST(s21_add_test_28) {
  s21_decimal d1 = {{1, 0, 0, 2147483648}, 0};  // -1
  s21_decimal d2 = {{2, 0, 0, 2147483648}, 0};  // -2
  s21_decimal res = s21_add(d1, d2);
  ck_assert_int_eq(res.value_type, 0);
  ck_assert_uint_eq(res.bits[0], 3);
  ck_assert_uint_eq(res.bits[1], 0);
  ck_assert_uint_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 2147483648);
}
END_TEST

START_TEST(s21_add_test_29) {
  s21_decimal d1 = {{2, 0, 0, 2147483648}, 0};  // -2
  s21_decimal d2 = {{1, 0, 0, 2147483648}, 0};  // -1
  s21_decimal res = s21_add(d1, d2);
  ck_assert_int_eq(res.value_type, 0);
  ck_assert_uint_eq(res.bits[0], 3);
  ck_assert_uint_eq(res.bits[1], 0);
  ck_assert_uint_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 2147483648);
}
END_TEST

START_TEST(s21_add_test_30) {
  s21_decimal d1 = {{4294967295, 4294967295, 4294967295, 0},
                    0};  // max_decimal 79228162514264337593543950335
  s21_decimal d2 = {{1, 0, 0, 0}, 0};
  s21_decimal res = s21_add(d1, d2);
  ck_assert_int_eq(res.value_type, s21_INFINITY);
  ck_assert_uint_eq(res.bits[0], 0);
  ck_assert_uint_eq(res.bits[1], 0);
  ck_assert_uint_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 0);
}
END_TEST

START_TEST(s21_add_test_31) {
  s21_decimal d1 = {{4294967295, 4294967295, 4294967295, 0},
                    0};  // max_decimal 79228162514264337593543950335
  s21_decimal d2 = {{1, 0, 0, 2147483648}, 0};
  s21_decimal res = s21_add(d1, d2);
  ck_assert_int_eq(res.value_type, 0);
  ck_assert_uint_eq(res.bits[0], 4294967294);
  ck_assert_uint_eq(res.bits[1], 4294967295);
  ck_assert_uint_eq(res.bits[2],
                    4294967295);  // ответ 79228162514264337593543950334
  ck_assert_uint_eq(res.bits[3], 0);
}
END_TEST

START_TEST(s21_add_test_32) {
  s21_decimal d1 = {{4294967295, 4294967295, 4294967295, 2147483648},
                    0};  // min_decimal -79228162514264337593543950335
  s21_decimal d2 = {{1, 0, 0, 0}, 0};  // 1
  s21_decimal res = s21_add(d1, d2);
  ck_assert_int_eq(res.value_type, 0);
  ck_assert_uint_eq(res.bits[0], 4294967294);
  ck_assert_uint_eq(res.bits[1], 4294967295);
  ck_assert_uint_eq(res.bits[2], 4294967295);
  ck_assert_uint_eq(res.bits[3],
                    2147483648);  // ответ -79228162514264337593543950334
}
END_TEST

START_TEST(s21_add_test_33) {
  s21_decimal d1 = {{4294967295, 4294967295, 4294967295, 2147483648},
                    0};  // min_decimal -79228162514264337593543950335
  s21_decimal d2 = {{1, 0, 0, 2147483648}, 0};  // -1
  s21_decimal res = s21_add(d1, d2);
  ck_assert_int_eq(res.value_type, s21_NEGATIVE_INFINITY);
  ck_assert_uint_eq(res.bits[0], 0);
  ck_assert_uint_eq(res.bits[1], 0);
  ck_assert_uint_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 0);
}
END_TEST

START_TEST(s21_add_test_34) {
  s21_decimal d1 = {{4294967294, 4294967295, 4294967295, 0},
                    0};  // max_decimal-1 (79228162514264337593543950334)
  s21_decimal d2 = {{4, 0, 0, 65536}, 0};  // 0.4
  s21_decimal res = s21_add(d1, d2);
  ck_assert_int_eq(res.value_type, 0);
  ck_assert_uint_eq(res.bits[0], 4294967294);
  ck_assert_uint_eq(res.bits[1], 4294967295);
  ck_assert_uint_eq(res.bits[2],
                    4294967295);  // ответ 79228162514264337593543950334
  ck_assert_uint_eq(res.bits[3], 0);
}
END_TEST

START_TEST(s21_add_test_35) {
  s21_decimal d1 = {{4294967294, 4294967295, 4294967295, 0},
                    0};  // max_decimal-1 (79228162514264337593543950334)
  s21_decimal d2 = {{5, 0, 0, 65536}, 0};  // 0.5
  s21_decimal res = s21_add(d1, d2);
  ck_assert_int_eq(res.value_type, 0);
  ck_assert_uint_eq(res.bits[0], 4294967294);
  ck_assert_uint_eq(res.bits[1], 4294967295);
  ck_assert_uint_eq(res.bits[2],
                    4294967295);  // ответ 79228162514264337593543950334
  ck_assert_uint_eq(res.bits[3], 0);
}
END_TEST

START_TEST(s21_add_test_36) {
  s21_decimal d1 = {{4294967294, 4294967295, 4294967295, 0},
                    0};  // max_decimal-1 (79228162514264337593543950334)
  s21_decimal d2 = {{6, 0, 0, 65536}, 0};  // 0.6
  s21_decimal res = s21_add(d1, d2);
  ck_assert_int_eq(res.value_type, 0);
  ck_assert_uint_eq(res.bits[0], 4294967295);
  ck_assert_uint_eq(res.bits[1], 4294967295);
  ck_assert_uint_eq(res.bits[2],
                    4294967295);  // ответ 79228162514264337593543950335
  ck_assert_uint_eq(res.bits[3], 0);
}
END_TEST

START_TEST(s21_add_test_37) {
  s21_decimal d1 = {{4294967295, 4294967295, 4294967295, 0},
                    0};  // max_decimal (79228162514264337593543950335)
  s21_decimal d2 = {{4, 0, 0, 65536}, 0};  // 0.4
  s21_decimal res = s21_add(d1, d2);
  ck_assert_int_eq(res.value_type, 0);
  ck_assert_uint_eq(res.bits[0], 4294967295);
  ck_assert_uint_eq(res.bits[1], 4294967295);
  ck_assert_uint_eq(res.bits[2],
                    4294967295);  // ответ 79228162514264337593543950335
  ck_assert_uint_eq(res.bits[3], 0);
}
END_TEST

START_TEST(s21_add_test_38) {
  s21_decimal d1 = {{4294967295, 4294967295, 4294967295, 0},
                    0};  // max_decimal (79228162514264337593543950335)
  s21_decimal d2 = {{5, 0, 0, 65536}, 0};  // 0.5
  s21_decimal res = s21_add(d1, d2);
  ck_assert_int_eq(res.value_type, s21_INFINITY);
  ck_assert_uint_eq(res.bits[0], 0);
  ck_assert_uint_eq(res.bits[1], 0);
  ck_assert_uint_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 0);
}
END_TEST

START_TEST(s21_add_test_39) {
  s21_decimal d1 = {{4294967295, 4294967295, 4294967295, 0},
                    0};  // max_decimal (79228162514264337593543950335)
  s21_decimal d2 = {{6, 0, 0, 65536}, 0};  // 0.6
  s21_decimal res = s21_add(d1, d2);
  ck_assert_int_eq(res.value_type, s21_INFINITY);
  ck_assert_uint_eq(res.bits[0], 0);
  ck_assert_uint_eq(res.bits[1], 0);
  ck_assert_uint_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 0);
}
END_TEST

START_TEST(s21_add_test_40) {
  s21_decimal d1 = {{4294967295, 4294967295, 4294967295, 0},
                    0};  // max_decimal (79228162514264337593543950335)
  s21_decimal d2 = {{500000001, 0, 0, 589824}, 0};  // 0.500000001
  s21_decimal res = s21_add(d1, d2);
  ck_assert_int_eq(res.value_type, s21_INFINITY);
  ck_assert_uint_eq(res.bits[0], 0);
  ck_assert_uint_eq(res.bits[1], 0);
  ck_assert_uint_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 0);
}
END_TEST
