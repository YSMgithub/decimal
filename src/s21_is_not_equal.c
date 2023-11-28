#include "s21_decimal.h"

// 0 - true, 1 - false
int s21_is_not_equal(s21_decimal left, s21_decimal right) {
  return !s21_is_equal(left, right);
}
