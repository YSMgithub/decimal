#include "s21_decimal.h"

s21_decimal s21_div(s21_decimal dividend, s21_decimal divisor) {
  // эта строка также покрывает случай, когда делимое 0, а делитель число (+-)
  // или делимое число, а делитель +-inf
  // value_type будет установлен как 0, все битс 0
  s21_decimal result = {{0, 0, 0, 0}, get_value_type(&dividend, &divisor, DIV)};
  // делимое не 0 по модулю и делитель не +-inf
  if (result.value_type == s21_NORMAL_VALUE &&
                           !is_zero(&dividend) && divisor.value_type == s21_NORMAL_VALUE) {
  // убираем знаки, чтобы все функции далее работали только с положительными числами
    int dividend_sign = get_sign(&dividend);
    int divisor_sign = get_sign(&divisor);
    clear_sign(&dividend);
    clear_sign(&divisor);

    s21_decimal truncated_dividend = s21_truncate(dividend);
    if (s21_is_equal(dividend, truncated_dividend) == 0) {
      set_scale(&dividend, 0);
      dividend = truncated_dividend;
    }

    s21_decimal truncated_divisor = s21_truncate(divisor);
    if (s21_is_equal(divisor, truncated_divisor) == 0) {
      set_scale(&divisor, 0);
      divisor = truncated_divisor;
    }

    s21_decimal one = {{1, 0, 0, 0}, 0};
    if (s21_is_equal(divisor, one) == 0) {  // если делитель по модулю равен 1
      result = dividend;
    } else if (s21_is_equal(dividend, divisor) == 0) {
      result = one;
    } else {
      s21_decimal mod = {{0, 0, 0, 0}, 0};
      if (div_bits(dividend, divisor, &result, &mod)) {
        nullify_bits(&result);
        result.value_type = (dividend_sign != divisor_sign) ? s21_NEGATIVE_INFINITY : s21_INFINITY;
      }
    }

    if (result.value_type == s21_NORMAL_VALUE && dividend_sign != divisor_sign) set_sign(&result);
    if (is_zero(&result)) nullify_bits(&result);
  }

  return result;
}

// Поделит числа по модулю и найдет остаток от деления.
// Вернет 1 в случае переполнения. Скейл частного будет установлен.
int div_bits(s21_decimal dividend, s21_decimal divisor, s21_decimal *quotient, s21_decimal *mod) {
  int overflowed = 0;
  int divident_scale = get_scale(&dividend);
  int divisor_scale = get_scale(&divisor);
  s21_decimal initial_dividend = dividend;
  int quotient_digits_count = 0;
  int quotient_scale = divident_scale;
  int initial_dividend_digits_count = count_digits_in_decimal(initial_dividend);
  int scales_delta = divident_scale - divisor_scale;  // для mod
  int interger_part_length = initial_dividend_digits_count - scales_delta;  // для mod

  if (find_first_dividend(&dividend, divisor, &initial_dividend_digits_count)) {
    int dividend_divided_digits_count = count_digits_in_decimal(dividend);  // для mod
    append_next_quotient_digit(&dividend, divisor, quotient);
    quotient_digits_count++;

    // если условие выполнено, то целая часть dividend поделена
    // если условие сейчас не будет выполнено, то будем проверять его ниже в цикле
    if (dividend_divided_digits_count >= interger_part_length && scales_delta >= 0) {
      *mod = dividend;
      int position_from_right = count_digits_in_decimal(initial_dividend) - dividend_divided_digits_count;

      while (position_from_right > 0) {
        drop_next_dividend_digit(initial_dividend, mod, &position_from_right);
      }
    }

    while (initial_dividend_digits_count) {
      drop_next_dividend_digit(initial_dividend, &dividend, &initial_dividend_digits_count);
      append_next_quotient_digit(&dividend, divisor, quotient);
      quotient_digits_count++;
      dividend_divided_digits_count++;

      if (is_zero(mod) && scales_delta >= 0 && dividend_divided_digits_count >= interger_part_length) {
        *mod = dividend;
        int position_from_right = count_digits_in_decimal(initial_dividend) - dividend_divided_digits_count;

        while (position_from_right > 0) {
          drop_next_dividend_digit(initial_dividend, mod, &position_from_right);
        }
      }
    }
  }

  if (!is_zero(&dividend)) {
    while (quotient_digits_count < MAX_DIGITS_COUNT && !is_zero(&dividend)) {
      s21_decimal saved_dividend = dividend;
      if (multiply_by_10(&dividend)) {
        dividend = saved_dividend;
        divide_by_10(&divisor);
      }

      scales_delta++;

      if (append_next_quotient_digit(&dividend, divisor, quotient)) {
        round_quotient(&dividend, &divisor, quotient, -1);
        break;
      }

      if (scales_delta == 0 && is_zero(mod)) *mod = dividend;

      quotient_scale++;
      if (!is_zero(quotient)) quotient_digits_count++;
    }
  }

  quotient_scale -= divisor_scale;
  int dicarded_digit = -1;
  while (quotient_scale > MAX_SCALE) {
    dicarded_digit = divide_by_10(quotient);
    quotient_scale--;
  }

  int need_rounding = (quotient_digits_count == MAX_DIGITS_COUNT && !is_zero(&dividend));
  if (need_rounding) round_quotient(&dividend, &divisor, quotient, dicarded_digit);

  while (quotient_scale < 0) {  // умножать на 10 нужно только если скейл частного < 0
    if (multiply_by_10(quotient)) {
      overflowed = 1;
      break;
    }

    quotient_scale++;
  }

  set_scale(quotient, quotient_scale);
  return overflowed;
}

int count_digits_in_decimal(s21_decimal number) {
  int amount = 0;
  if (is_zero(&number)) {
    amount = 1;
  } else {
    do {
      divide_by_10(&number);
      amount++;
    } while (!is_zero(&number));
  }

  return amount;
}

// Вернет 1 в случае переполнения
int append_next_quotient_digit(s21_decimal *dividend, s21_decimal divisor, s21_decimal *quotient) {
  int overflowed = 0;
  s21_decimal saved_dividend = *dividend;
  s21_decimal next_quotient_digit = {{0, 0, 0, 0}, 0};
  while (compare_bits(dividend, &divisor) >= 0) {
    next_quotient_digit.bits[0]++;
    sub_bits(dividend, &divisor, dividend);
  }

  s21_decimal saved_quotient = *quotient;
  if (multiply_by_10(quotient)) {
    *quotient = saved_quotient;
    *dividend = saved_dividend;
    overflowed = 1;
  } else {
    add_bits(quotient, &next_quotient_digit, quotient);
  }

  return overflowed;
}

void drop_next_dividend_digit(s21_decimal initial_dividend, s21_decimal *dividend, int *position) {
  s21_decimal digit = {{0, 0, 0, 0}, 0};
  for (int i = 0; i < *position; i++) {
    digit.bits[LOW] = divide_by_10(&initial_dividend);
  }

  multiply_by_10(dividend);
  add_bits(dividend, &digit, dividend);
  (*position)--;
}

void round_quotient(s21_decimal *dividend, s21_decimal *divisor, s21_decimal *quotient,
                    int dicarded_quotient_digit) {
  int next_quotient_digit = 0;
  multiply_by_10(dividend);
  while (compare_bits(dividend, divisor) >= 0) {
    next_quotient_digit++;
    sub_bits(dividend, divisor, dividend);
  }

  if (dicarded_quotient_digit > -1) {
    bank_rounding(quotient, dicarded_quotient_digit, ADD);
  } else {
    bank_rounding(quotient, next_quotient_digit, ADD);
  }
}

// 0 - не найден, 1 и т.д. - найден
int find_first_dividend(s21_decimal *dividend, s21_decimal divisor, int *dividend_digits_count) {
  int success = 0;
  s21_decimal original_dividend = *dividend;
  do {
    (*dividend_digits_count)--;
    for (int i = 0; i < *dividend_digits_count; i++) {
      divide_by_10(dividend);
    }

    if (compare_bits(dividend, &divisor) >= 0) {
      success = 1;
      break;
    }

    *dividend = original_dividend;
  } while (*dividend_digits_count);

  return success;
}
