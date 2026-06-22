#include "s21_decimal.h"

void comparison_reverse(int *flag) {
  if (*flag == 1) {
    *flag = 2;
  } else if (*flag == 2) {
    *flag = 1;
  }
}

int comparison_bits(s21_decimal d1, s21_decimal d2) {
  int bit1 = 0;
  int bit2 = 0;
  int flag = 0;
  for (int i = 95; i >= 0 && !flag; --i) {
    bit1 = get_bit(d1, i);
    bit2 = get_bit(d2, i);
    if (bit1 > bit2) {
      flag = 1;
    } else if (bit1 < bit2) {
      flag = 2;
    }
  }
  return flag;
}

int greater_num(int a, int b) {
  int flag = 0;
  if (a > b) {
    flag = 1;
  } else if (a < b) {
    flag = 2;
  } else if (a == b) {
    flag = 0;
  }
  return flag;
}

void normalize_scale_upper(s21_decimal *d, int norm) {
  s21_decimal _norm = {0};
  s21_decimal _res = {0};
  s21_from_float_to_decimal((float)pow(10, norm), &_norm);
  s21_mul(*d, _norm, &_res);
  set_e(&_res, get_e(*d) + norm);
  copy_dec(d, _res);
}

void normalize(s21_decimal *d1, s21_decimal *d2) {
  int norm = get_e(*d1) - get_e(*d2);
  if (norm > 0) {
    normalize_scale_upper(d2, norm);
  } else if (norm < 0) {
    normalize_scale_upper(d1, -norm);
  }
}

int s21_comparison(s21_decimal d1, s21_decimal d2) {
  int flag = 0;
  int scale_dif = (get_e(d1) - get_e(d2));
  normalize(&d1, &d2);
  flag = greater_num(!get_sign_int(d1), !get_sign_int(d2));
  if (flag == 0) {
    if (scale_dif >= 0) {
      flag = comparison_bits(d1, d2);
    } else {
      scale_dif = -scale_dif;
      flag = comparison_bits(d2, d1);
      comparison_reverse(&flag);
    }
    if (get_sign_int(d1) && get_sign_int(d2)) {
      comparison_reverse(&flag);
    }
  } else {
    if (d1.bits[0] == 0 && d1.bits[1] == 0 && d1.bits[2] == 0 &&
        d2.bits[0] == 0 && d2.bits[1] == 0 && d2.bits[2] == 0) {
      flag = 0;
    }
  }
  return flag;
}

int s21_is_less(s21_decimal d1, s21_decimal d2) {
  return (s21_comparison(d1, d2) == 2) ? 1 : 0;
}

int s21_is_less_or_equal(s21_decimal d1, s21_decimal d2) {
  return (s21_comparison(d1, d2) == 2) || (s21_comparison(d1, d2) == 0) ? 1 : 0;
}

int s21_is_greater(s21_decimal d1, s21_decimal d2) {
  return (s21_comparison(d1, d2) == 1) ? 1 : 0;
}

int s21_is_greater_or_equal(s21_decimal d1, s21_decimal d2) {
  return (s21_comparison(d1, d2) == 1) || (s21_comparison(d1, d2) == 0) ? 1 : 0;
}

int s21_is_equal(s21_decimal d1, s21_decimal d2) {
  return (s21_comparison(d1, d2) == 0) ? 1 : 0;
}

int s21_is_not_equal(s21_decimal d1, s21_decimal d2) {
  return (s21_comparison(d1, d2) == 0) ? 0 : 1;
}
