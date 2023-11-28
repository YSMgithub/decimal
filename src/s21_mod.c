#include "s21_decimal.h"

s21_decimal s21_mod(s21_decimal dividend, s21_decimal divisor) {
  s21_decimal mod = {{0, 0, 0, 0}, get_value_type(&dividend, &divisor, MOD)};
  if (mod.value_type == s21_NORMAL_VALUE) {
    // если делитель +-inf либо делимое 0, то делимое - это mod
    if (divisor.value_type == s21_INFINITY ||
        divisor.value_type == s21_NEGATIVE_INFINITY || is_zero(&dividend)) {
      mod = dividend;
    } else {
      int dividend_scale = get_scale(&dividend);
      int divisor_scale = get_scale(&divisor);
      // скейл остатка от деления всегда равен максимальному скейлу исходных чисел
      int mod_scale = dividend_scale > divisor_scale ? dividend_scale : divisor_scale;
      // остаток от деления отрицательный если делимое отрицательное, знак делителя неважен
      // кроме случая, когда остаток равен 0 - он всегда положительный
      int mod_sign = get_sign(&dividend);
      // убираем знаки, чтобы все функции далее работали только с положительными числами
      clear_sign(&dividend);
      clear_sign(&divisor);

      s21_decimal one = {{1, 0, 0, 0}, 0};
      // если делимое меньше делителя, то делимое - это mod
      if (s21_is_less(dividend, divisor) == 0) {
        mod = dividend;
      // если делимое больше делителя и делитель не равен 1, то считаем остаток от деления
      } else if (s21_is_greater(dividend, divisor) == 0 && s21_is_not_equal(divisor, one) == 0) {
        s21_decimal quotient = {{0, 0, 0, 0}, 0};
        div_bits(dividend, divisor, &quotient, &mod);
        set_scale(&mod, mod_scale);
      } else {
        // если же числа равны либо делитель равен 1, то mod будет равен 0. Он задан первой строкой.
        // устанавливаем ему скейл (0.12 % 0.12 = 0.00)
        set_scale(&mod, mod_scale);
      }

      // если результат 0, то у него знак всегда +
      if (!is_zero(&mod) && mod_sign) set_sign(&mod);
    }
  }

  return mod;
}
