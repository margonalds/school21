#include "s21_decimal.h"

int get_sign_int(s21_decimal dec) { return (dec.bits[3] >> 31) & 1u; }

int get_sign(s21_decimal dec) { return (dec.bits[3] >> 31) & 1u ? -1 : 1; }

void set_sign_int(s21_decimal* number, int sign) {
  if (sign < 0) {
    number->bits[3] |= (1 << 31);
  } else {
    number->bits[3] &= ~(1 << 31);
  }
}

void set_sign(s21_decimal* number, int sign) {
  if (sign) {
    number->bits[3] |= (1 << 31);
  } else {
    number->bits[3] &= ~(1 << 31);
  }
}

int get_bit_int(int res, int position) {
  return ((res & (1u << (position % 32))) >> (position % 32));
}

int get_bit(s21_decimal dec, int position) {
  return ((dec.bits[position / 32] & (1u << (position % 32))) >>
          (position % 32));
}

void set_bit(s21_decimal* dec, int position, int value) {
  if (!value) {
    dec->bits[position / 32] &= ~(1 << (position % 32));
  } else {
    dec->bits[position / 32] |= (1 << (position % 32));
  }
}

int get_e(s21_decimal dec) { return (dec.bits[3] >> 16) & 511u; }

void set_e(s21_decimal* dec, int val) {
  if (val > 28 || val < 0) return;

  for (int i = 16 + (32 * 3), j = 0; i < 23 + (32 * 3); i++, j++) {
    set_bit(dec, i, get_bit_int(val, j));
  }
}
