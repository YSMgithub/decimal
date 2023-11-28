#include "s21_decimal.h"

s21_decimal s21_add(s21_decimal left, s21_decimal right) {
  s21_decimal result = {{0, 0, 0, 0}, get_value_type(&left, &right, ADD)};
  if (result.value_type == s21_NORMAL_VALUE) {
    int left_sign = get_sign(&left);
    int right_sign = get_sign(&right);
    if (left_sign == 0 && right_sign == 1) {  // a + (-b) = a - b
      toggle_sign(&right);
      result = s21_sub(left, right);
    } else if (left_sign == 1 && right_sign == 0) {  // -a + b = b - a
      toggle_sign(&left);
      result = s21_sub(right, left);
    } else {  // если оба числа одного знака, то складываем их
      if (left_sign == 1) set_sign(&result);  // числа одного знака, поэтому выбрать можно знак любого из них
      int last_discarded_digit = equlize_scales(&left, &right);  // выравниваем скейлы
      // поскольку скейлы чисел были выровнены, то можно взять скейл любого
      int result_scale = get_scale(&left);
      if (result_scale == 0) {
        // Если после выравнивания итоговый скейл равен 0, значит, одно из слагаемых либо оба могут быть
        // близки к максимальному значению. В данном случае недопустимо переполнение мантисс.
        // Складываем, и если при сложении либо округлении после сложения произошло переполнение, то
        // устанавлием value_type и обнуляем все биты результата.
        if (add_bits(&left, &right, &result) || bank_rounding(&result, last_discarded_digit, ADD)) {
          result.value_type = left_sign ? s21_NEGATIVE_INFINITY : s21_INFINITY;
          nullify_bits(&result);
        }
      } else {
        // Если после выравнивания итоговый скейл не равен 0, значит оба слагаемых далеки от максимального
        // значения. В данном случае допустимо переполнение мантисс.
        // Например 7.9228162514264337593543950335 + 7.9228162514264337593543950335 должно быть
        // 15.845632502852867518708790067. У этих чисел в мантиссах все биты 1, но из-за скейла числа в итоге
        // очень маленькие и их сложение допустимо. Но если мантиссы сложить, то будет переполнение.
        // Чтобы этого не произошло, уменьшаем каждое число в 10 раз и складываем отброшенные правые цифры
        int last_digits_sum = divide_by_10(&left) + divide_by_10(&right);
        if ((last_digits_sum % 2 == 0 && last_discarded_digit > 5) ||
            (last_digits_sum % 2 != 0 && last_discarded_digit >= 5)) last_digits_sum++;
        result_scale--;  // понижаем итоговый скейл (т.к. left и right стали короче на 1 порядок)
        add_bits(&left, &right, &result);  // и теперь точно не будет переполнения
        // Поскольку мы отбросили от исходных left И rigth крайние правые цифры, то они не участвовали
        // в сложении. Но их сумма влияет на результат. Поэтому добавим их к результату.
        // Для этого сначала попытаемся увеличить результат в 10 раз
        s21_decimal saved_result = result;
        if (multiply_by_10(&result)) {
          // Если увеличить результат не удалось из-за произошедшего при умножении на 10 переполнения, то
          // восстановим результат (при умножении он испортился) и затем округлим.
          result = saved_result;
          last_discarded_digit = last_digits_sum > 5 ? 6 : last_digits_sum;
          bank_rounding(&result, last_discarded_digit, ADD);
        } else {
          // Если увеличить результат удалось, то повышем итоговый скейл (т.к. результат стал длиннее
          // на 1 разряд) и добавляем к нему сумму отброшенных цифр
          result_scale++;
          s21_decimal tail = {{last_digits_sum, 0, 0, 0}, 0};
          if (add_bits(&result, &tail, &result)) {
            // Если при добавлении к результату суммы отброшенных цифр вновь произошло переполнение, то
            // восстанавливаем исходный результат (еще до умножения на 10) и просто его округляем
            result = saved_result;
            last_discarded_digit = last_digits_sum > 5 ? 6 : last_digits_sum;
            bank_rounding(&result, last_discarded_digit, ADD);
          }
        }
      }
      set_scale(&result, result_scale);  // устанавливаем скейл результата
    }
  }
  return result;
}
