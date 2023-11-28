#ifndef SRC_S21_DECIMAL_H_
#define SRC_S21_DECIMAL_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define ADD 0
#define SUB 1
#define MUL 2
#define DIV 3
#define MOD 4
#define MAX_SCALE 28
#define MAX_DIGITS_COUNT 29

typedef enum { s21_NORMAL_VALUE = 0, s21_INFINITY = 1, s21_NEGATIVE_INFINITY = 2, s21_NAN = 3 } value_type_t;

typedef struct {
  unsigned int bits[4];
  value_type_t value_type;
} s21_decimal;

typedef struct {
  unsigned long int bits[6];
  int sign;
  int degree;
} adv_decimal;

enum { LOW, MID, HIGH, SCALE };

// arithmetics
s21_decimal s21_add(s21_decimal left, s21_decimal right);
s21_decimal s21_sub(s21_decimal left, s21_decimal right);
s21_decimal s21_mul(s21_decimal left, s21_decimal right);
s21_decimal s21_div(s21_decimal dividend, s21_decimal divisor);
s21_decimal s21_mod(s21_decimal left, s21_decimal right);

// comparsion
int s21_is_less(s21_decimal left, s21_decimal right);
int s21_is_less_or_equal(s21_decimal left, s21_decimal right);
int s21_is_greater(s21_decimal left, s21_decimal right);
int s21_is_greater_or_equal(s21_decimal left, s21_decimal right);
int s21_is_equal(s21_decimal left, s21_decimal right);
int s21_is_not_equal(s21_decimal left, s21_decimal right);

// converters
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_int_to_decimal(int src, s21_decimal *dst);

// another
s21_decimal s21_round(s21_decimal number);
s21_decimal s21_negate(s21_decimal src);
s21_decimal s21_truncate(s21_decimal src);
s21_decimal s21_floor(s21_decimal src);

// utility
int get_bit(s21_decimal *src, int i);
void set_bit(s21_decimal *src, int i);
void clear_bit(s21_decimal *src, int i);

int get_sign(s21_decimal *src);
void toggle_sign(s21_decimal *src);
void set_sign(s21_decimal *src);
void clear_sign(s21_decimal *src);

int get_scale(s21_decimal *src);
void set_scale(s21_decimal *src, unsigned int scale);

int find_first_non_zero_bit(s21_decimal *src);
int get_bin_exp(float src);
int count_digits(int src);
unsigned int float_to_uint(float src);
void nullify_bits(s21_decimal *dst);

void print_uint(unsigned int n);
void print_decimal(s21_decimal *src);
void print_scale(unsigned int n);

int add_bits(s21_decimal *left, s21_decimal *right, s21_decimal *result);
void sub_bits(s21_decimal *left, s21_decimal *right, s21_decimal *result);
int mul_bits(s21_decimal left, s21_decimal right, s21_decimal *result);
int div_bits(s21_decimal dividend, s21_decimal divisor, s21_decimal *quotient, s21_decimal *mod);
int compare_bits(s21_decimal *left, s21_decimal *right);

int get_value_type(s21_decimal *left, s21_decimal *right, int operation);
int equlize_scales(s21_decimal *left, s21_decimal *right);

int increase_decimal(s21_decimal *number, int scale);
int decrease_decimal(s21_decimal *number, int scale);

int multiply_by_10(s21_decimal *number);
int divide_by_10(s21_decimal *number);

int bank_rounding(s21_decimal *number, int last_discarded_digit, int operation);

int compare_normal_decimals(s21_decimal *left, s21_decimal *right);
int compare_unnormal_decimals(s21_decimal *left, s21_decimal *right);

int is_zero(s21_decimal *number);
int divide_mod(s21_decimal *dividend, s21_decimal *divisor, s21_decimal *quotient, int *qoutient_scale);


int shift_left_one_bit(s21_decimal *number);
void shift_right(s21_decimal *number, int bits_count);

adv_decimal create_adecimal(s21_decimal dec);
s21_decimal convert_to_decimal(adv_decimal src);
adv_decimal div10(adv_decimal dec);
s21_decimal adv_mul(adv_decimal src1, adv_decimal src2);

int append_next_quotient_digit(s21_decimal *dividend, s21_decimal divisor, s21_decimal *quotient);
void drop_next_dividend_digit(s21_decimal initial_dividend, s21_decimal *dividend, int *position);
void round_quotient(s21_decimal *dividend, s21_decimal *divisor, s21_decimal *quotient,
                    int dicarded_quotient_digit);
int find_first_dividend(s21_decimal *dividend, s21_decimal divisor, int *dividend_digits_count);
int count_digits_in_decimal(s21_decimal number);

#endif  // SRC_S21_DECIMAL_H_
