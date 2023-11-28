#include "s21_decimal.h"

s21_decimal s21_mul(s21_decimal left, s21_decimal right) {
  s21_decimal result = {{0, 0, 0, 0}, get_value_type(&left, &right, 2)};
  if (result.value_type == s21_NORMAL_VALUE) {
    adv_decimal src1 = create_adecimal(left);
    adv_decimal src2 = create_adecimal(right);
    result = adv_mul(src1, src2);
  }
  return result;
}

adv_decimal create_adecimal(s21_decimal dec) {  // конвертация в расширенный тип
  adv_decimal result;
  result.bits[5] = 0;
  result.bits[4] = 0;
  result.bits[3] = 0;
  result.bits[2] = dec.bits[2];
  result.bits[1] = dec.bits[1];
  result.bits[0] = dec.bits[0];

  result.sign = dec.bits[3] >> 31;
  result.degree = dec.bits[3] << 1 >> 17;
  return result;
}

s21_decimal adv_mul(adv_decimal src1, adv_decimal src2) {
  adv_decimal result = {{0, 0, 0, 0, 0, 0}, 0, 0};
  int k = 0;
  for (int k2 = 0; k2 < 3; k2++) {
    for (int k1 = 0; k1 < 3 ; k1++) {
      result.bits[k] += (unsigned long int)src1.bits[k1] * (unsigned long int)src2.bits[k2];
      k++;
    }
    k -= 2;
    unsigned long int overflow = 0;
    for (int i = 0; i < 6; i++) {
      result.bits[i] += overflow;
      overflow = result.bits[i] >> 32;
      result.bits[i] = result.bits[i] - (overflow << 32);
    }
  }
  result.sign = (src1.sign + src2.sign) % 2;
  result.degree = src1.degree + src2.degree;
  while (result.degree > 28) {
    result = div10(result);
  }
  while (result.bits[3] != 0 && result.degree > 0) {
    result = div10(result);
  }

  return convert_to_decimal(result);
}

s21_decimal convert_to_decimal(adv_decimal src) {
  s21_decimal result = {{0, 0, 0, 0}, 0};
  if (src.bits[3] == 0 && src.bits[4] == 0 && src.bits[5] == 0) {
    result.bits[3] = 0;
    result.bits[2] = src.bits[2];
    result.bits[1] = src.bits[1];
    result.bits[0] = src.bits[0];
    if (src.bits[0] == 0 && src.bits[1] == 0 && src.bits[2] == 0 && src.sign == 1) src.sign = 0;
    result.bits[3] = (src.sign << 31) + (src.degree << 16);
  } else {
    if (src.sign == 0) result.value_type = 1;
    if (src.sign == 1) result.value_type = 2;
  }
  return result;
}

adv_decimal div10(adv_decimal dec) {
  adv_decimal result = {{0, 0, 0, 0, 0, 0}, dec.sign, dec.degree - 1};
  unsigned long int overflow = 0;
  for (int i = 5; i >= 0; i--) {
    result.bits[i] = (dec.bits[i] + overflow) / 10;
    overflow = (dec.bits[i] % 10) << 32;
    result.bits[i] = result.bits[i] << 32 >> 32;
  }
  return result;
}
