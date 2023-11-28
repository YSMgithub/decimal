#include "s21_decimal.h"

// 0 - true, 1 - false
int s21_is_equal(s21_decimal left, s21_decimal right) {
  int compare_result = 0;
  if (left.value_type == s21_NORMAL_VALUE && right.value_type == s21_NORMAL_VALUE) {
    equlize_scales(&left, &right);
    compare_result = compare_normal_decimals(&left, &right);
  } else {
    compare_result = compare_unnormal_decimals(&left, &right);
  }

  return compare_result == 0 ? 0 : 1;
}
