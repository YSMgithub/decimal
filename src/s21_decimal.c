#include "s21_decimal.h"

int get_bit(s21_decimal *src, int i) {
  const unsigned int mask = 1u << (i % 32);
  return (src->bits[i / 32] & mask) ? 1 : 0;
}

void set_bit(s21_decimal *src, int i) {
  const unsigned int mask = 1u << (i % 32);
  src->bits[i / 32] |= mask;
}

void clear_bit(s21_decimal *src, int i) {
  const unsigned int mask = ~(1u << (i % 32));
  src->bits[i / 32] &= mask;
}

int get_sign(s21_decimal *src) {
  const unsigned int mask = 0x80000000;
  return (src->bits[SCALE] & mask) ? 1 : 0;
}

void toggle_sign(s21_decimal *src) {
  const unsigned int mask = 0x80000000;
  src->bits[SCALE] ^= mask;
}

void set_sign(s21_decimal *src) {
  const unsigned int mask = 0x80000000;
  src->bits[SCALE] |= mask;
}

void clear_sign(s21_decimal *src) {
  const unsigned int mask = ~(0x80000000);
  src->bits[SCALE] &= mask;
}

int get_scale(s21_decimal *src) {
  const unsigned int mask = 0xFF0000;
  return (src->bits[SCALE] & mask) >> 16;
}

// scale должен быть числом от 0 до 28
void set_scale(s21_decimal *src, unsigned int scale) {
  const unsigned int mask = ~(0xFF0000);
  src->bits[SCALE] &= mask;
  scale = scale << 16;
  src->bits[SCALE] |= scale;
}

void print_uint(unsigned int n) {
  for (unsigned int mask = 0x80000000; mask; mask >>= 1) {
    printf("%d", !!(n & mask));
  }
}

void print_scale(unsigned int n) {
  unsigned int mask = 0x80000000;
  printf("%d ", !!(n & mask));
  mask >>= 8;
  for (int i = 0; i < 8 && mask; i++, mask >>= 1) {
    printf("%d", !!(n & mask));
  }
}

int find_first_non_zero_bit(s21_decimal *src) {
  int result = -1;

  for (int i = 95; i >= 0; i--) {
    if (get_bit(src, i)) {
      result = i;
      break;
    }
  }

  return result;
}

void print_decimal(s21_decimal *src) {
  printf("LOW >>   ");
  print_uint(src->bits[LOW]);
  printf("\nMID >>   ");
  print_uint(src->bits[MID]);
  printf("\nHIGH >>  ");
  print_uint(src->bits[HIGH]);
  printf("\nSCALE >> ");
  print_scale(src->bits[SCALE]);
  printf("\n");
  printf("VALUE_TYPE >> %d\n", src->value_type);
}

/**
 * Вернет 1, если при сложении произошло переполнение
 */
int add_bits(s21_decimal *left, s21_decimal *right, s21_decimal *result) {
  int tmp = 0;
  for (int i = 0, sum = 0; i <= 95; i++) {
    sum = get_bit(left, i) + get_bit(right, i) + tmp;
    switch (sum) {
      case 0:
        clear_bit(result, i);
        break;
      case 1:
        set_bit(result, i);
        tmp = 0;
        break;
      case 2:
        clear_bit(result, i);
        tmp = 1;
        break;
      case 3:
        set_bit(result, i);
        tmp = 1;
        break;
    }
  }

  return tmp ? 1 : 0;
}

// Важно передавать в функцию такие left и right, что left >= right
// Например, если нужно сделать 4 - 10, то в функцию надо передать 10 - 4,
// a знак "-" результату должен будет присвоить вызвавший эту функцию код
void sub_bits(s21_decimal *left, s21_decimal *right, s21_decimal *result) {
  // a - b = a + (~b + 1)
  s21_decimal one = {{1, 0, 0, 0}, 0};
  s21_decimal negtive_right = {{~right->bits[0], ~right->bits[1], ~right->bits[2], 0}, 0};
  // Gри сложениях может возникать переполнение, но мы его игнорируем - все
  // улетающие в переполнение 1 не нужны, важны лишь первые 96 битов.
  add_bits(&negtive_right, &one, &negtive_right);
  add_bits(left, &negtive_right, result);
}

/**
 * Выравнивает скейлы чисел и возвращает последнюю отброшенную цифру (от 0 до 9)
 * числа с большим изначальным скейлом.
 * Если скейлы изначально равны, то функция возвращает 0.
 */
int equlize_scales(s21_decimal *left, s21_decimal *right) {
  int last_discarded_digit = 0;
  int left_scale = get_scale(left);
  int right_scale = get_scale(right);

  /* Если скейлы не равны, то увеличиваем число с меньшим скейлом (умножая на 10 столько раз, на сколько
  его скейл меньше скейла второго числа). Если в процессе умножения на 10 из-за переполнения невозможно
  совершить необходимое количество умножений, то уменьшаем второе число (делением на 10) до того скейла,
  до которого смогли поднять первое число.
  */
  if (left_scale > right_scale) {
    int increases_count = increase_decimal(right, left_scale);
    if (increases_count != left_scale - right_scale) {
      left_scale = right_scale + increases_count;
      last_discarded_digit = decrease_decimal(left, left_scale);
    }
  } else if (left_scale < right_scale) {
    int increases_count = increase_decimal(left, right_scale);
    if (increases_count != right_scale - left_scale) {
      right_scale = left_scale + increases_count;
      last_discarded_digit = decrease_decimal(right, right_scale);
    }
  }

  return last_discarded_digit;
}

int get_value_type(s21_decimal *left, s21_decimal *right, int operation) {
  // общий случай - устанавливает максимально возможный тип из 0, 1, 2, 3
  int type = left->value_type >= right->value_type ? left->value_type : right->value_type;
  // далее проверяем особые случаи в зависимости от вида арифметической операции
  if (operation == ADD) {  // сложение
    if ((left->value_type == s21_INFINITY && right->value_type == s21_NEGATIVE_INFINITY) ||
        (left->value_type == s21_NEGATIVE_INFINITY && right->value_type == s21_INFINITY)) {
      type = s21_NAN;  // inf + (-inf) = NaN; -inf + inf = NaN
    }
  } else if (operation == SUB) {  // вычитание
    if ((left->value_type == s21_INFINITY && right->value_type == s21_INFINITY) ||
        (left->value_type == s21_NEGATIVE_INFINITY && right->value_type == s21_NEGATIVE_INFINITY)) {
      type = s21_NAN;  // inf - inf = NaN; -inf - (-inf) = NaN
    } else if (type == s21_NEGATIVE_INFINITY && right->value_type == s21_NEGATIVE_INFINITY) {
      type = s21_INFINITY;  // любое число или inf - (-inf) = любое число или inf + inf = inf
    } else if (type == s21_INFINITY && right->value_type == s21_INFINITY) {
      type = s21_NEGATIVE_INFINITY;  // любое число - inf = -inf
    }
  } else if (operation == MUL) {  // умножение
    if ((type == s21_INFINITY || type == s21_NEGATIVE_INFINITY) && (is_zero(left) || is_zero(right))) {
      type = s21_NAN;  // +-inf * (+-0) = NaN
    } else if (left->value_type == s21_NEGATIVE_INFINITY && right->value_type == s21_NEGATIVE_INFINITY) {
      type = s21_INFINITY;  // -inf * (-inf) = inf
    // value_type проверять не нужно, потому что если он != 0 , то знак будет "+" (bits[3] == 0)
    } else if (type == s21_INFINITY && (get_sign(left) || get_sign(right))) {
      type = s21_NEGATIVE_INFINITY;  // inf * (-decimal) = -inf
    } else if (type == s21_NEGATIVE_INFINITY && (get_sign(left) || get_sign(right))) {
      type = s21_INFINITY;  // -inf * (-decimal) = inf
    }
  } else if (operation == DIV) {  // деление
    if ((left->value_type == s21_INFINITY || left->value_type == s21_NEGATIVE_INFINITY) &&
        (right->value_type == s21_INFINITY || right->value_type == s21_NEGATIVE_INFINITY)) {
      type = s21_NAN;  // +-inf / +-inf = NaN
    } else if (left->value_type == s21_INFINITY && get_sign(right)) {
      type = s21_NEGATIVE_INFINITY;  // inf / (-decimal) = -inf, при делении на -0 ответ тоже -inf
    } else if (left->value_type == s21_NEGATIVE_INFINITY && get_sign(right)) {
      type = s21_INFINITY;  // -inf / (-decimal) = inf, при делении на -0 ответ тоже inf
    } else if (left->value_type == s21_NORMAL_VALUE &&
              (right->value_type == s21_INFINITY || right->value_type == s21_NEGATIVE_INFINITY)) {
      type = s21_NORMAL_VALUE;  // +-decimal / +-inf = decimal
    } else if (type == s21_NORMAL_VALUE && is_zero(left) && is_zero(right)) {
      type = s21_NAN;  // +-0 / +-0 = NaN
    } else if (type == s21_NORMAL_VALUE && is_zero(right)) {
      type = (get_sign(left) != get_sign(right)) ? s21_NEGATIVE_INFINITY : s21_INFINITY;
    }
  } else if (operation == MOD) {  // остаток от деления
    if (left->value_type == s21_INFINITY || left->value_type == s21_NEGATIVE_INFINITY || is_zero(right)) {
      type = s21_NAN;
    } else if ((right->value_type == s21_INFINITY || right->value_type == s21_NEGATIVE_INFINITY) &&
               left->value_type == s21_NORMAL_VALUE) {
      type = s21_NORMAL_VALUE;
    }
  }

  return type;
}

/**
 * 1 - true, 0 - false
 */
int is_zero(s21_decimal *number) {
  return (number->value_type || number->bits[0] || number->bits[1] || number->bits[2]) ? 0 : 1;
}

int increase_decimal(s21_decimal *number, int scale) {
  int increases_count = 0;
  int delta = scale - get_scale(number);
  s21_decimal saved_number = *number;
  while (delta > 0 && multiply_by_10(number) == 0) {
    saved_number = *number;
    increases_count++;
    delta--;
  }

  *number = saved_number;
  set_scale(number, get_scale(number) + increases_count);
  return increases_count;
}

/**
 * Отбрасывает от number справа столько цифр, насколько скейл number > scale
 * и возвращает последнюю отброшенную цифру.
 * При этом последняя отброшенная цифра будет увеличена на 1,
 * если она равна 5 и в исходном числе правее этой цифры была хоть одна ненулевая цифра
 */
int decrease_decimal(s21_decimal *number, int scale) {
  int last_discarded_digit = 0;
  int delta = get_scale(number) - scale;
  if (delta > 0) {
    int has_non_zero_tail = 0;
    while (delta > 1) {
      last_discarded_digit = divide_by_10(number);
      if (has_non_zero_tail == 0 && last_discarded_digit > 0) {
        has_non_zero_tail = 1;
      }
      delta--;
    }
    last_discarded_digit = divide_by_10(number);
    if (last_discarded_digit == 5 && has_non_zero_tail == 1) {
      last_discarded_digit++;
    }
  }

  set_scale(number, scale);
  return last_discarded_digit;
}

/**
 * Увеличивает число в 10 раз, возвращает 1 в случае переполнения
 */
int multiply_by_10(s21_decimal *number) {
  // алгоритм
  // A*10 = A<<1 + A<<3
  int overflowed = 0;
  // устанавливаем в каждое слагаемое изначальное значение number
  s21_decimal term_1 = *number;
  s21_decimal term_2 = *number;
  if (shift_left_one_bit(&term_1)) {  // сдвигаем влево на 1 бит первое слагаемое
    overflowed = 1;
  } else {  // если сдвиг первого слагаемое не привел к переполнению
    for (int i = 0; i < 3; i++) {  // то сдвигаем влево на 3 бита второе слагаемое
      if (shift_left_one_bit(&term_2)) {
        overflowed = 1;
        break;
      }
    }
  }
  // если сдвиги не превели к переполнению, то складываем слагаемые
  if (overflowed == 0) {  // если при сложении произойдет переполнение, то в overflowed запишем 1
    overflowed = add_bits(&term_1, &term_2, number);
  }

  return overflowed;
}

/**
 * Возвращает 1, если сдвиг приведет к переполнению
 */
int shift_left_one_bit(s21_decimal *number) {
  int overflowed = 0;
  if (get_bit(number, 95)) {  // смотрим 95 бит (самый старший), если там 1, то переполение
    overflowed = 1;
  } else {
    // иначе сохраняем старшие биты младшего и среднего инта
    int bit_31 = get_bit(number, 31);  // старший бит LOW
    int bit_63 = get_bit(number, 63);  // старший бит MID
    // сдвигаем все инты на 1 бит влево
    number->bits[0] = number->bits[0] << 1;
    number->bits[1] = number->bits[1] << 1;
    number->bits[2] = number->bits[2] << 1;
    // и если сохраненные биты были равны 1, то устанавливаем их в самые младшие
    // биты среднего и старшего инта
    if (bit_31) {
      set_bit(number, 32);  // нулевой бит MID
    }
    if (bit_63) {
      set_bit(number, 64);  // нулевой бит HIGH
    }
  }

  return overflowed;
}

/**
 * Уменьшает число в 10 раз и возвращает остаток от деления.
 * Например, 201 / 10: number станет 20 и функция вернет 1;
 * 4 / 10: number станет 0 и функция вернет 4.
 */
int divide_by_10(s21_decimal *number) {
  // Сначала находим результат деления number на 10
  // алгоритм:
  // s = n >> 1 + n >> 2
  // s = s + s >> 4
  // s = s + s >> 8
  // s = s + s >> 16
  // s = s + s >> 32
  // s = s + s >> 64
  // s >> 3
  s21_decimal term1 = *number;
  s21_decimal term2 = *number;
  s21_decimal sum = {{0, 0, 0, 0}, 0};
  shift_right(&term1, 1);
  shift_right(&term2, 2);
  add_bits(&term1, &term2, &sum);
  for (int i = 4; i <= 64; i *= 2) {
    term1 = sum;
    shift_right(&term1, i);
    add_bits(&sum, &term1, &sum);
  }
  shift_right(&sum, 3);
  // Теперь в переменной sum лежит результат деления number на 10

  // Деление происходит с погрешностью. например, 250 / 10 = 24 и чем больше number, тем больше погрешность.
  // Нивелируем ее, алгоритм:
  // e = n - s * 10
  // s = s + (e > 9)
  term1 = sum;
  multiply_by_10(&term1);            // s*10
  sub_bits(number, &term1, &term2);  // e = n - s
  if (term2.bits[0] > 9) {
    s21_decimal one = {{1, 0, 0, 0}, 0};
    add_bits(&sum, &one, &sum);
  }

  // Теперь найдем цифру, которая будет отброшена при делении number на 10
  // Например, 243 / 10 = 24. Чтобы найти остаток, нужно 243 - 24*10 = 3
  term1 = sum;
  multiply_by_10(&term1);
  sub_bits(number, &term1, &term2);

  // После всех вычислений поместим результат деления number на 10 в number и вернем отброшенную цифру
  number->bits[0] = sum.bits[0];
  number->bits[1] = sum.bits[1];
  number->bits[2] = sum.bits[2];
  return term2.bits[0];
}

void shift_right(s21_decimal *number, int bits_count) {
  for (int i = 0; i < bits_count; i++) {
    int bit_64 = get_bit(number, 64);  // нулевой бит HIGH
    int bit_32 = get_bit(number, 32);  // нулевой бит MID
    number->bits[0] = number->bits[0] >> 1;
    number->bits[1] = number->bits[1] >> 1;
    number->bits[2] = number->bits[2] >> 1;
    if (bit_64) {
      set_bit(number, 63);  // старший бит MID
    }
    if (bit_32) {
      set_bit(number, 31);  // старший бит LOW
    }
  }
}

/**
 * Возвращает 1, если произошло переполнение при округлении
 */
int bank_rounding(s21_decimal *number, int last_discarded_digit, int operation) {
  int overflowed = 0;
  int most_lower_bit = get_bit(number, 0);
  if ((most_lower_bit == 1 && last_discarded_digit >= 5) ||
      (most_lower_bit == 0 && last_discarded_digit > 5)) {
    s21_decimal one = {{1, 0, 0, 0}, 0};
    if (operation == ADD) {  // сложение
      overflowed = add_bits(number, &one, number);
    } else if (operation == SUB) {  // вычитание
      sub_bits(number, &one, number);
    }
  }

  // Если number -0, то меняем знак, чтобы ответ был 0
  if (is_zero(number) && get_sign(number) == 1) {
    toggle_sign(number);
  }

  return overflowed;
}

/**
 * Вернет 0 - если равны, 1 если левый больше, -1 если левый меньше
 */
int compare_normal_decimals(s21_decimal *left, s21_decimal *right) {
  if (is_zero(left) && is_zero(right)) {  // особый случай: 0(-0) равен 0(-0)
    return 0;
  }

  int result = 0;  // изначально считаем, что числа равны
  // Смотрим на знаки (+ или -) и делаем вывод о том, что больше/меньше
  int left_sign = get_sign(left);
  int right_sign = get_sign(right);
  if (left_sign > right_sign) {  // левое -, правое +
    result = -1;
  } else if (left_sign < right_sign) {  // левое +, правое -
    result = 1;
  } else {
    // Если же числа одного знака, то сравниваем биты этих чисел.
    // Пока считаем, что оба числа положительные
    // Сравниваем поочереди от самого старшего бита до самого младшего
    result = compare_bits(left, right);
    // Если цикл отработает без брейков, т.е. биты попарно равны, значит числа
    // равны (result останется равным 0).
    // Если оба числа были отрицательные, то результат будет противополжный
    // (большее станет меньшим, меньшее бОльшим)
    if (get_sign(left) && get_sign(right)) result *= -1;
  }

  return result;
}

/**
 * Вернет 0 - если равны, 1 если левый больше, -1 если левый меньше
 */
int compare_bits(s21_decimal *left, s21_decimal *right) {
  int result = 0;
  for (int i = 95, left_bit, right_bit; i >= 0; i--) {
    left_bit = get_bit(left, i);
    right_bit = get_bit(right, i);
    if (left_bit > right_bit) {  // если бит левого 1, а правого 0, то левое число больше
      result = 1;
      break;
    }
    if (left_bit < right_bit) {  // если бит левого 0, а правого 1, то левое число меньше
      result = -1;
      break;
    }
  }

  return result;
}

/**
 * Вернет 0 - если равны, 1 если левый больше, -1 если левый меньше, 2 если есть NaN
 */
int compare_unnormal_decimals(s21_decimal *left, s21_decimal *right) {
  int result = 0;
  if (left->value_type == s21_NAN || right->value_type == s21_NAN) {
    result = 2;
  } else if ((left->value_type == s21_INFINITY && right->value_type != s21_INFINITY) ||
             (left->value_type != s21_NEGATIVE_INFINITY && right->value_type == s21_NEGATIVE_INFINITY)) {
    result = 1;
  } else if ((left->value_type != s21_INFINITY && right->value_type == s21_INFINITY) ||
             (left->value_type == s21_NEGATIVE_INFINITY && right->value_type != s21_NEGATIVE_INFINITY)) {
    result = -1;
  }

  return result;
}

int get_bin_exp(float src) {
  const unsigned int mask = 0x7F800000;
  return ((*((unsigned int *)&src) & mask) >> 23) - 127;
}

int count_digits(int src) {
  int count = 0;

  do {
    src /= 10;
    count++;
  } while (src != 0);

  return count;
}

unsigned int float_to_uint(float src) { return *((unsigned int *)&src); }

void nullify_bits(s21_decimal *dst) {
  for (int i = 0; i < 4; i++) {
    dst->bits[i] = 0;
  }
}

// Перемножает мантиссы чисел. Возвращает 1 в случае переполнения. Зануляет скейл mod'a
int mul_bits(s21_decimal left, s21_decimal right, s21_decimal *result) {
  int overflowed = 0;
  int right_digits_count = count_digits_in_decimal(right);
  s21_decimal factor = {{0, 0, 0, 0}, 0};
  s21_decimal intermediate_result = {{0, 0, 0, 0}, 0};
  *result = intermediate_result;
  while (right_digits_count > 0 && overflowed == 0) {
    factor.bits[LOW] = divide_by_10(&right);
    while (factor.bits[LOW] > 0) {
      if (add_bits(&intermediate_result, &left, &intermediate_result)) {
        // overflowed = 1;
        break;
      }
      factor.bits[LOW]--;
    }

    overflowed = add_bits(result, &intermediate_result, result);
    nullify_bits(&intermediate_result);

    if (overflowed == 0/* && right_digits_count > 0*/) overflowed = multiply_by_10(&left);

    right_digits_count--;
  }

  return overflowed;
}
