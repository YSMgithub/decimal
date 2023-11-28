#include "s21_decimal.h"

s21_decimal s21_floor(s21_decimal src) {
  if (src.value_type == s21_NORMAL_VALUE) {
    if (is_zero(&src)) {  // +-0.0 округляется до 0
      clear_sign(&src);
      set_scale(&src, 0);
    } else {
      int sign = get_sign(&src);
      s21_decimal tmp = src;
      src = s21_truncate(src);

      if (sign && s21_is_equal(src, tmp)) {
        s21_decimal one = {{1, 0, 0, 0}, 0};
        add_bits(&src, &one, &src);
      }
    }
  } else {
    nullify_bits(&src);
  }

  return src;
}

