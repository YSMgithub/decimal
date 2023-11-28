#include "s21_decimal.h"

s21_decimal s21_round(s21_decimal number) {
  if (number.value_type == s21_NORMAL_VALUE) {
    bank_rounding(&number, decrease_decimal(&number, 0), ADD);
  } else {
    nullify_bits(&number);
  }

  return number;
}
