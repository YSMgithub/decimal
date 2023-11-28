#include "s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int error = 0;

  if (dst != NULL) {
    nullify_bits(dst);
    dst->value_type = s21_NORMAL_VALUE;

    if (src < 0) {
      set_sign(dst);
      src = -src;
    }

    dst->bits[LOW] = src;
  } else {
    error = 1;
  }

  return error;
}
