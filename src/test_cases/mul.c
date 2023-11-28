#include <check.h>
#include "../s21_decimal.h"

//s21_mul TESTS
START_TEST(s21_mul_test_1) { //+
  s21_decimal left = {{0, 0, 0, 0}, 0};
  s21_decimal right = {{0, 0, 0, 0}, 0};
  s21_decimal res = s21_mul(left, right);
  ck_assert_int_eq(res.value_type, 0);
  ck_assert_uint_eq(res.bits[0], 0);
  ck_assert_uint_eq(res.bits[1], 0);
  ck_assert_uint_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 0);
}
END_TEST

START_TEST(s21_mul_test_2) { //+
  s21_decimal left = {{1, 0, 0, 0}, s21_NAN};
  s21_decimal right = {{1, 0, 0, 0}, 0};
  s21_decimal res = s21_mul(left, right);
  ck_assert_int_eq(res.value_type, s21_NAN);
  ck_assert_uint_eq(res.bits[0], 0);
  ck_assert_uint_eq(res.bits[1], 0);
  ck_assert_uint_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 0);
}
END_TEST

START_TEST(s21_mul_test_3) { //+
  s21_decimal left = {{1, 0, 0, 0}, 0};
  s21_decimal right = {{1, 0, 0, 0}, s21_NAN};
  s21_decimal res = s21_mul(left, right);
  ck_assert_int_eq(res.value_type, s21_NAN);
  ck_assert_uint_eq(res.bits[0], 0);
  ck_assert_uint_eq(res.bits[1], 0);
  ck_assert_uint_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 0);
}
END_TEST

START_TEST(s21_mul_test_4) { //+
  s21_decimal left = {{1, 0, 0, 0}, s21_NAN};
  s21_decimal right = {{1, 0, 0, 0}, s21_INFINITY};
  s21_decimal res = s21_mul(left, right);
  ck_assert_int_eq(res.value_type, s21_NAN);
  ck_assert_uint_eq(res.bits[0], 0);
  ck_assert_uint_eq(res.bits[1], 0);
  ck_assert_uint_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 0);
}
END_TEST

START_TEST(s21_mul_test_5) { //+
  s21_decimal left = {{1, 0, 0, 0}, s21_NAN};
  s21_decimal right = {{1, 0, 0, 0}, s21_NEGATIVE_INFINITY};
  s21_decimal res = s21_mul(left, right);
  ck_assert_int_eq(res.value_type, s21_NAN);
  ck_assert_uint_eq(res.bits[0], 0);
  ck_assert_uint_eq(res.bits[1], 0);
  ck_assert_uint_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 0);
}
END_TEST

START_TEST(s21_mul_test_6) { //+
  s21_decimal left = {{0, 0, 0, 0}, s21_INFINITY};
  s21_decimal right = {{0, 0, 0, 0}, 0};
  s21_decimal res = s21_mul(left, right);
  ck_assert_int_eq(res.value_type, s21_NAN);
  ck_assert_uint_eq(res.bits[0], 0);
  ck_assert_uint_eq(res.bits[1], 0);
  ck_assert_uint_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 0);
}
END_TEST

START_TEST(s21_mul_test_7) { //+
  s21_decimal left = {{0, 0, 0, 0}, s21_NEGATIVE_INFINITY};
  s21_decimal right = {{0, 0, 0, 0}, 0};
  s21_decimal res = s21_mul(left, right);
  ck_assert_int_eq(res.value_type, s21_NAN);
  ck_assert_uint_eq(res.bits[0], 0);
  ck_assert_uint_eq(res.bits[1], 0);
  ck_assert_uint_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 0);
}
END_TEST

START_TEST(s21_mul_test_8) { //+
  s21_decimal left = {{0, 0, 0, 0}, s21_INFINITY};
  s21_decimal right = {{1, 0, 0, 0}, 0};
  s21_decimal res = s21_mul(left, right);
  ck_assert_int_eq(res.value_type, s21_INFINITY);
  ck_assert_uint_eq(res.bits[0], 0);
  ck_assert_uint_eq(res.bits[1], 0);
  ck_assert_uint_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 0);
}
END_TEST

START_TEST(s21_mul_test_9) { //+
  s21_decimal left = {{0, 0, 0, 0}, s21_INFINITY};
  s21_decimal right = {{0, 0, 0, 0}, s21_INFINITY};
  s21_decimal res = s21_mul(left, right);
  ck_assert_int_eq(res.value_type, s21_INFINITY);
  ck_assert_uint_eq(res.bits[0], 0);
  ck_assert_uint_eq(res.bits[1], 0);
  ck_assert_uint_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 0);
}
END_TEST

START_TEST(s21_mul_test_10) { //+
  s21_decimal left = {{0, 0, 0, 0}, s21_INFINITY};
  s21_decimal right = {{1, 0, 0, 2147483648}, 0};  // -1
  s21_decimal res = s21_mul(left, right);
  ck_assert_int_eq(res.value_type, s21_NEGATIVE_INFINITY);
  ck_assert_uint_eq(res.bits[0], 0);
  ck_assert_uint_eq(res.bits[1], 0);
  ck_assert_uint_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 0);
}
END_TEST

START_TEST(s21_mul_test_11) { //+
  s21_decimal left = {{1, 0, 0, 2147483648}, 0};  // -1
  s21_decimal right = {{0, 0, 0, 0}, s21_NEGATIVE_INFINITY};
  s21_decimal res = s21_mul(left, right);
  ck_assert_int_eq(res.value_type, s21_INFINITY);
  ck_assert_uint_eq(res.bits[0], 0);
  ck_assert_uint_eq(res.bits[1], 0);
  ck_assert_uint_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 0);
}
END_TEST

START_TEST(s21_mul_test_12) { //+
  s21_decimal left = {{0, 0, 0, 0}, s21_INFINITY};
  s21_decimal right = {{0, 0, 0, 0}, s21_NEGATIVE_INFINITY};
  s21_decimal res = s21_mul(left, right);
  ck_assert_int_eq(res.value_type, s21_NEGATIVE_INFINITY);
  ck_assert_uint_eq(res.bits[0], 0);
  ck_assert_uint_eq(res.bits[1], 0);
  ck_assert_uint_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 0);
}
END_TEST

START_TEST(s21_mul_test_13) { //+
  s21_decimal left = {{0, 0, 0, 0}, s21_NEGATIVE_INFINITY};
  s21_decimal right = {{0, 0, 0, 0}, s21_INFINITY};
  s21_decimal res = s21_mul(left, right);
  ck_assert_int_eq(res.value_type, s21_NEGATIVE_INFINITY);
  ck_assert_uint_eq(res.bits[0], 0);
  ck_assert_uint_eq(res.bits[1], 0);
  ck_assert_uint_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 0);
}
END_TEST

START_TEST(s21_mul_test_14) { //+
  s21_decimal left = {{0, 0, 0, 0}, s21_NEGATIVE_INFINITY};
  s21_decimal right = {{0, 0, 0, 0}, s21_NEGATIVE_INFINITY};
  s21_decimal res = s21_mul(left, right);
  ck_assert_int_eq(res.value_type, s21_INFINITY);
  ck_assert_uint_eq(res.bits[0], 0);
  ck_assert_uint_eq(res.bits[1], 0);
  ck_assert_uint_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 0);
}
END_TEST

START_TEST(s21_mul_test_15) { //+
  s21_decimal left = {{100, 0, 0, 0}, 0};
  s21_decimal right = {{0, 0, 0, 0}, s21_NEGATIVE_INFINITY};
  s21_decimal res = s21_mul(left, right);
  ck_assert_int_eq(res.value_type, s21_NEGATIVE_INFINITY);
  ck_assert_uint_eq(res.bits[0], 0);
  ck_assert_uint_eq(res.bits[1], 0);
  ck_assert_uint_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 0);
}
END_TEST

START_TEST(s21_mul_test_16) { //+
  s21_decimal left = {{0, 0, 0, 0}, s21_NEGATIVE_INFINITY};
  s21_decimal right = {{100, 0, 0, 2147483648}, 0};  // -100
  s21_decimal res = s21_mul(left, right);
  ck_assert_int_eq(res.value_type, s21_INFINITY);
  ck_assert_uint_eq(res.bits[0], 0);
  ck_assert_uint_eq(res.bits[1], 0);
  ck_assert_uint_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 0);
}
END_TEST

START_TEST(s21_mul_test_17) { //+
  s21_decimal left = {{0, 0, 0, 2147483648}, 0};  // -0
  s21_decimal right = {{0, 0, 0, 0}, 0};
  s21_decimal res = s21_mul(left, right);
  ck_assert_int_eq(res.value_type, 0);
  ck_assert_uint_eq(res.bits[0], 0);
  ck_assert_uint_eq(res.bits[1], 0);
  ck_assert_uint_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 0);
}
END_TEST

START_TEST(s21_mul_test_18) { //+
  s21_decimal left = {{0, 0, 0, 196608}, 0};  // 0.000
  s21_decimal right = {{0, 0, 0, 0}, 0};
  s21_decimal res = s21_mul(left, right);
  ck_assert_int_eq(res.value_type, 0);
  ck_assert_uint_eq(res.bits[0], 0);
  ck_assert_uint_eq(res.bits[1], 0);
  ck_assert_uint_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 196608);
}
END_TEST

START_TEST(s21_mul_test_19) { //+
  s21_decimal left = {{0, 0, 0, 0}, 0};
  s21_decimal right = {{0, 0, 0, 2147483648}, 0};
  s21_decimal res = s21_mul(left, right);
  ck_assert_int_eq(res.value_type, 0);
  ck_assert_uint_eq(res.bits[0], 0);
  ck_assert_uint_eq(res.bits[1], 0);
  ck_assert_uint_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 0);
}
END_TEST

START_TEST(s21_mul_test_31) { //+
  s21_decimal left = {{4294967295, 4294967295, 4294967295, 0},
                    0};  // max_decimal 79228162514264337593543950335
  s21_decimal right = {{2, 0, 0, 0}, 0};
  s21_decimal res = s21_mul(left, right);
  ck_assert_int_eq(res.value_type, 1);
  ck_assert_uint_eq(res.bits[0], 0);
  ck_assert_uint_eq(res.bits[1], 0);
  ck_assert_uint_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 0);
}
END_TEST

START_TEST(s21_mul_test_32) { //+
  s21_decimal left = {{4294967295, 4294967295, 4294967295, 2147483648},
                    0};  // min_decimal -79228162514264337593543950335
  s21_decimal right = {{2, 0, 0, 0}, 0};
  s21_decimal res = s21_mul(left, right);
  ck_assert_int_eq(res.value_type, 2);
  ck_assert_uint_eq(res.bits[0], 0);
  ck_assert_uint_eq(res.bits[1], 0);
  ck_assert_uint_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 0);
}
END_TEST

START_TEST(s21_mul_test_33) { //+
  s21_decimal left = {{0, 0, 0, 0}, 0};
  s21_decimal right = {{0, 0, 0, 2147483648}, 0};
  s21_decimal res = s21_mul(left, right);
  ck_assert_int_eq(res.value_type, 0);
  ck_assert_uint_eq(res.bits[0], 0);
  ck_assert_uint_eq(res.bits[1], 0);
  ck_assert_uint_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 0);
}
END_TEST

START_TEST(s21_mul_test_34) { //+
  s21_decimal left = {{4294967295, 0, 0, 0}, 0};
  s21_decimal right = {{2, 1, 1, 0}, 0};
  s21_decimal res = s21_mul(left, right);
  ck_assert_int_eq(res.value_type, 1);
  ck_assert_uint_eq(res.bits[0], 0);
  ck_assert_uint_eq(res.bits[1], 0);
  ck_assert_uint_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 0);
}
END_TEST

START_TEST(s21_mul_test_35) { //+
  s21_decimal left = {{4294967295, 0, 0, 0}, 0};
  s21_decimal right = {{2, 1, 1, 2147483648}, 0};
  s21_decimal res = s21_mul(left, right);
  ck_assert_int_eq(res.value_type, 2);
  ck_assert_uint_eq(res.bits[0], 0);
  ck_assert_uint_eq(res.bits[1], 0);
  ck_assert_uint_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 0);
}
END_TEST

START_TEST(s21_mul_test_36) { //+
  s21_decimal left = {{121, 0, 0, 0}, 0};
  s21_decimal right = {{33, 0, 0, 0}, 0};
  s21_decimal res = s21_mul(left, right);
  ck_assert_int_eq(res.value_type, 0);
  ck_assert_uint_eq(res.bits[0], 3993);
  ck_assert_uint_eq(res.bits[1], 0);
  ck_assert_uint_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 0);
}
END_TEST

START_TEST(s21_mul_test_37) { //+
  s21_decimal left = {{121, 0, 0, 0}, 0};
  s21_decimal right = {{33, 0, 0, 2147483648}, 0};
  s21_decimal res = s21_mul(left, right);
  ck_assert_int_eq(res.value_type, 0);
  ck_assert_uint_eq(res.bits[0], 3993);
  ck_assert_uint_eq(res.bits[1], 0);
  ck_assert_uint_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 2147483648);
}
END_TEST

START_TEST(s21_mul_test_38) { //+
  s21_decimal left = {{1, 0, 0, 1835008}, 0}; // 28 степень
  s21_decimal right = {{1, 0, 0, 65536}, 0}; // 1 степень
  s21_decimal res = s21_mul(left, right);
  ck_assert_int_eq(res.value_type, 0);
  ck_assert_uint_eq(res.bits[0], 0);
  ck_assert_uint_eq(res.bits[1], 0);
  ck_assert_uint_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 1835008);
}
END_TEST

START_TEST(s21_mul_test_39) { //+
  s21_decimal left = {{4294967295, 0, 0, 1835008}, 0}; // 28
  s21_decimal right = {{1, 1, 1, 1310720}, 0}; // 20
  s21_decimal res = s21_mul(left, right);
  ck_assert_int_eq(res.value_type, 0);
  ck_assert_uint_eq(res.bits[0], 792281625);
  ck_assert_uint_eq(res.bits[1], 0);
  ck_assert_uint_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 1835008);
}
END_TEST

START_TEST(s21_mul_test_40) { //+
  s21_decimal left = {{1000000, 0, 0, 1835008}, 0}; // 28
  s21_decimal right = {{1000000, 0, 0, 786432}, 0}; // 12
  s21_decimal res = s21_mul(left, right);
  ck_assert_int_eq(res.value_type, 0);
  ck_assert_uint_eq(res.bits[0], 1);
  ck_assert_uint_eq(res.bits[1], 0);
  ck_assert_uint_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 1835008);
}
END_TEST

START_TEST(s21_mul_test_41) { //+
  s21_decimal left = {{100000, 0, 0, 1835008}, 0}; // 28
  s21_decimal right = {{1000000, 0, 0, 786432}, 0}; // 12
  s21_decimal res = s21_mul(left, right);
  ck_assert_int_eq(res.value_type, 0);
  ck_assert_uint_eq(res.bits[0], 0);
  ck_assert_uint_eq(res.bits[1], 0);
  ck_assert_uint_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 1835008);
}
END_TEST

START_TEST(s21_mul_test_42) { //+?
  s21_decimal left = {{2000000, 0, 0, 0}, 0};
  s21_decimal right = {{10, 0, 0, 65536}, 0};
  s21_decimal res = s21_mul(left, right);
  ck_assert_int_eq(res.value_type, 0);
  ck_assert_uint_eq(res.bits[0], 20000000);
  ck_assert_uint_eq(res.bits[1], 0);
  ck_assert_uint_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 65536);
}
END_TEST

START_TEST(s21_mul_test_43) { //+
  s21_decimal left = {{2249167232, 28744, 0, 0}, 0};
  s21_decimal right = {{1410218818, 2, 0, 0}, 0};
  s21_decimal res = s21_mul(left, right);
  ck_assert_int_eq(res.value_type, 0);
  ck_assert_uint_eq(res.bits[0], 462160640);
  ck_assert_uint_eq(res.bits[1], 370228528);
  ck_assert_uint_eq(res.bits[2], 66927);
  ck_assert_uint_eq(res.bits[3], 0);
}
END_TEST
