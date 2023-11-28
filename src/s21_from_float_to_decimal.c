#include "s21_decimal.h"

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int error = 0;

  if (dst == NULL) {
    error = 1;
  } else {
    int sign = float_to_uint(src) & 0x80000000;
    int scale = 0;
    int exp = get_bin_exp(src);
    nullify_bits(dst);

    if (exp == 128) {
      if (!(float_to_uint(src) & 0x7FFFFF)) {
        error = 1;
        dst->value_type = sign ? s21_NEGATIVE_INFINITY : s21_INFINITY;
      } else {
        error = 1;
        dst->value_type = s21_NAN;
      }
    } else if (exp == -127) {
      if (!(float_to_uint(src) & 0x7FFFFF)) {
        dst->value_type = s21_NORMAL_VALUE;
        if (sign) {
          set_sign(dst);
        }
      } else {
        error = 1;
        dst->value_type = s21_NAN;
      }
    } else if (exp > 95) {
      error = 1;
      dst->value_type = sign ? s21_NEGATIVE_INFINITY : s21_INFINITY;
    } else if (exp < -94) {
      error = 1;
      dst->value_type = s21_NORMAL_VALUE;
    } else {
      double tmp = src;

      while (!(int)tmp) {
        tmp *= 10;
        scale++;
      }
      while (count_digits((int)tmp) < 8 && scale < 28) {
        tmp *= 10;
        scale++;
      }
      src = tmp;
      exp = get_bin_exp(src);

      if (scale > 28) {
        error = 1;
        dst->value_type = s21_NORMAL_VALUE;
      } else {
        dst->value_type = s21_NORMAL_VALUE;
        set_bit(dst, exp--);
        for (unsigned int mask = 0x400000; mask; mask >>= 1, exp--) {
          if (float_to_uint(src) & mask) {
            set_bit(dst, exp);
          }
        }

        set_scale(dst, scale);
        if (sign) {
          set_sign(dst);
        }
      }
    }
  }

  return error;
}
