
#include "s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int error = 0;

  if (dst != NULL) {
    switch (src.value_type) {
      case s21_NORMAL_VALUE:
        *dst = 0.0;

        for (int i = 0; i < 96; i++) {
          if (get_bit(&src, i)) {
            *dst += pow(2.0, i);
          }
        }

        int scale = get_scale(&src);

        while (scale-- > 0) {
          *dst /= 10;
        }

        if (get_sign(&src)) {
          *dst = -*dst;
        }
        break;
      case s21_INFINITY:
        *dst = INFINITY;
        error = 1;
        break;
      case s21_NEGATIVE_INFINITY:
        *dst = -INFINITY;
        error = 1;
        break;
      case s21_NAN:
        *dst = NAN;
        error = 1;
        break;
    }
  } else {
    error = 1;
  }

  return error;
}
