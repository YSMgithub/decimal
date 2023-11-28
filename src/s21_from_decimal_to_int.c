#include "s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int error = 0;

  if (src.value_type == s21_NORMAL_VALUE && dst != NULL) {
    src = s21_truncate(src);
    if (find_first_non_zero_bit(&src) < 31) {
      int sign = get_sign(&src);
      const unsigned int mask = 0x7FFFFFFF;
      *dst = src.bits[LOW] & mask;

      if (sign) {
        *dst = -(*dst);
      }
    }
  } else {
    error = 1;
  }

  return error;
}
