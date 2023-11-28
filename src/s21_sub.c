#include "s21_decimal.h"

s21_decimal s21_sub(s21_decimal left, s21_decimal right) {
  s21_decimal result = {{0, 0, 0, 0}, get_value_type(&left, &right, SUB)};
  if (result.value_type == s21_NORMAL_VALUE) {
    // определяем знаки, чтобы понять - сложить нужно числа или вычесть
    int left_sing = get_sign(&left);
    int right_sing = get_sign(&right);
    if ((left_sing == 0 && right_sing == 1) ||  // a - (-b) = a + b
        (left_sing == 1 && right_sing == 0)) {  // -a - b = -a + (-b)
      toggle_sign(&right);
      result = s21_add(left, right);
    } else if (left_sing == 1 && right_sing == 1) {  // -a - (-b) = b - a
      toggle_sign(&left);
      toggle_sign(&right);
      result = s21_sub(right, left);
    } else {  // если оба числа положительные, то вычитаем
      int last_discarded_digit = equlize_scales(&left, &right);  // сначала выравниваем скейлы
      // затем определяем итоговый знак
      // s21_is_greater_or_equal тоже вызвает equlize_scales и если скейлы уже выровнены,
      // то не будет повторно вызван алгорим выравнивания
      int result_sign = s21_is_greater_or_equal(left, right);  // 0 это +, 1 это -

      // вычитаем, устанавливаем скейл и знак "-" (если нужно)
      if (result_sign == 0) {
        sub_bits(&left, &right, &result);
      } else {
        sub_bits(&right, &left, &result);
        set_sign(&result);
      }
      set_scale(&result, get_scale(&left));

      if (last_discarded_digit) {
        s21_decimal saved_result = result;
        int result_last_digit = divide_by_10(&result);
        s21_decimal tail = {{result_last_digit * 10 - last_discarded_digit, 0, 0, 0}, 0};
        multiply_by_10(&result);
        if (multiply_by_10(&result)) {
          result = saved_result;
          bank_rounding(&result, last_discarded_digit, SUB);
        } else {
          if (add_bits(&result, &tail, &result)) {
            result = saved_result;
            bank_rounding(&result, last_discarded_digit, SUB);
          } else {
            set_scale(&result, get_scale(&result) + 1);
          }
        }
      }
    }
  }

  return result;
}
