#include "s21_decimal.h"

s21_decimal s21_negate(s21_decimal src) {
  switch (src.value_type) {
    case s21_INFINITY:
      nullify_bits(&src);
      src.value_type = s21_NEGATIVE_INFINITY;
      break;
    case s21_NEGATIVE_INFINITY:
      nullify_bits(&src);
      src.value_type = s21_INFINITY;
      break;
    case s21_NORMAL_VALUE:
      toggle_sign(&src);
      break;
    case s21_NAN:
      nullify_bits(&src);
      break;
  }

  return src;
}
