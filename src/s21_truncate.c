#include "s21_decimal.h"

s21_decimal s21_truncate(s21_decimal src) {
  if (src.value_type == s21_NORMAL_VALUE) {
    decrease_decimal(&src, 0);
  } else {
    nullify_bits(&src);
  }

  return src;
}
