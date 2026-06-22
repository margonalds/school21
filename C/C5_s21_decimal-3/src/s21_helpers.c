#include "s21_decimal.h"

void copy_dec(s21_decimal *dec, s21_decimal src) {
  for (int i = 0; i < 4; ++i) {
    dec->bits[i] = src.bits[i];
  }
}

void null_decimal(s21_decimal *num) {
  num->bits[0] = 0;
  num->bits[1] = 0;
  num->bits[2] = 0;
  num->bits[3] = 0;
}

void neg_bite_to_pos(s21_decimal *dec, int pos) {
  dec->bits[pos / 32] *= -1;
  if (dec->bits[pos / 32] == 1) dec->bits[pos / 32] -= 1;
}

int division_by_10(s21_decimal *dec) {
  s21_decimal q = sum_decimal(shift_bits(*dec, 1), shift_bits(*dec, 2));
  q = sum_decimal(q, shift_bits(q, 4));
  q = sum_decimal(q, shift_bits(q, 8));
  q = sum_decimal(q, shift_bits(q, 16));
  q = sum_decimal(q, shift_bits(q, 32));
  q = sum_decimal(q, shift_bits(q, 64));
  q = shift_bits(q, 3);
  s21_decimal r = subtraction_decimal(
      *dec, shift_bits(sum_decimal(shift_bits(q, -2), q), -1));

  s21_decimal res = {{1, 0, 0, 0}};
  if (r.bits[0] > 9) {
    res = sum_decimal(q, res);
  } else {
    res = q;
  }

  if (get_sign_int(*dec)) {
    set_sign(&res, 1);
  }

  *dec = res;

  return r.bits[0];
}

s21_decimal init_dec() {
  s21_decimal ret = {{0, 0, 0, 0}};
  return ret;
};

s21_decimal sum_decimal(s21_decimal de1, s21_decimal de2) {
  s21_decimal answer = {{0, 0, 0, 0}};

  int dop = 0;
  for (size_t i = 0; i < 96; i++) {
    int bi1 = get_bit(de1, i);
    int bi2 = get_bit(de2, i);

    int finl_bit = bi1 + bi2 + dop;
    if (finl_bit > 1) {
      if (finl_bit == 3) {
        set_bit(&answer, i, 1);
      }
      dop = 1;

    } else {
      if (finl_bit == 1) {
        set_bit(&answer, i, 1);
      }
      dop = 0;
    }
  }
  return answer;
}

s21_decimal shift_bits(s21_decimal dec, int shif) {
  s21_decimal answer = {{0, 0, 0, 0}};

  if (shif > 0) {
    for (int i = 0; i < 96 - shif; i++) {
      if (get_bit(dec, i + shif)) {
        set_bit(&answer, i, 1);
      }
    }
  } else {
    for (int i = 95; i > -1 + (shif * -1); i--) {
      if (get_bit(dec, i + shif)) {
        set_bit(&answer, i, 1);
      }
    }
  }

  return answer;
}

s21_decimal subtraction_decimal(s21_decimal de1, s21_decimal de2) {
  s21_decimal answer = {{1, 0, 0, 0}};

  for (int i = 0; i < 96; i++) {
    set_bit(&de2, i, (get_bit(de2, i) - 1) * -1);
  }

  de2 = sum_decimal(de2, answer);
  answer = sum_decimal(de1, de2);

  return answer;
}

void zero_decimal(s21_decimal *val) {
  val->bits[0] = val->bits[1] = val->bits[2] = val->bits[3] = 0;
}

int is_zero(s21_decimal dec) {
  int is_zero = 1;
  for (int bite = 0; bite < 96 && is_zero != 0; bite++) {
    is_zero = get_bit(dec, bite) != 0 ? 0 : is_zero;
  }
  return is_zero;
}

void import_to_big_decimal(s21_decimal value_1, s21_big_decimal *value_2) {
  value_2->bits[0] = value_1.bits[0];
  value_2->bits[1] = value_1.bits[1];
  value_2->bits[2] = value_1.bits[2];
}

int get_bit_big(s21_big_decimal val, int index) {
  int mask = 1u << (index % 32);
  return (val.bits[index / 32] & mask) != 0;
}

void zero_big_decimal(s21_big_decimal *val) {
  val->bits[0] = val->bits[1] = val->bits[2] = val->bits[3] = val->bits[4] =
      val->bits[5] = val->bits[6] = val->bits[7] = 0;
}

void set_bit_big(s21_big_decimal *val, int index, int bit) {
  int mask = 1u << (index % 32);
  if (bit == 0)
    val->bits[index / 32] = val->bits[index / 32] & ~mask;
  else
    val->bits[index / 32] = val->bits[index / 32] | mask;
}

void set_e_big(s21_big_decimal *val, int n) {
  s21_big_decimal ten = {{10, 0, 0, 0, 0, 0, 0, 0}}, tmp = {0};
  for (int i = 0; i < n; i++) {
    mul_big_decimal(*val, ten, &tmp);
    *val = tmp;
    zero_big_decimal(&tmp);
  }
}

void normalization(s21_big_decimal *value_1, s21_big_decimal *value_2,
                   int diff) {
  if (diff > 0) {
    set_e_big(value_2, diff);
  } else if (diff < 0) {
    set_e_big(value_1, -diff);
  }
}

int post_normalization(s21_big_decimal *result, int scale) {
  int dop = 0;
  while ((result->bits[3] || result->bits[4] || result->bits[5] ||
          result->bits[6] || result->bits[7]) &&
         scale > 0) {
    if (scale == 1 && result->bits[3]) dop = 1;
    decreace_scale_big_decimal(result, 1);
    scale--;
  }
  if (dop && scale == 0 && result->bits[3] == 0 && get_bit_big(*result, 0))
    set_bit_big(result, 0, 0);
  if ((result->bits[3] || result->bits[4] || result->bits[5] ||
       result->bits[6] || result->bits[7]))
    scale = -1;
  return scale;
}

int shift_big_dec_left(s21_big_decimal *val, int num) {
  int error = 0;
  int buffer[8] = {0};
  for (int k = 0; k < num; k++) {
    for (int i = 0; i < 7; i++) {
      buffer[i] = get_bit_big(*val, (i + 1) * 32 - 1);
    }
    for (int i = 7; i > 0 && !error; i--) {
      if (get_bit_big(*val, 255)) error = 1;
      val->bits[i] <<= 1;
      set_bit_big(val, i * 32, buffer[i - 1]);
    }
    val->bits[0] <<= 1;
  }
  return error;
}

int mul_big_decimal(s21_big_decimal value_1, s21_big_decimal value_2,
                    s21_big_decimal *result) {
  int error = 0, count = 0;
  for (int i = 0; i < 256 && !error; i++) {
    if (get_bit_big(value_2, i)) {
      error = shift_big_dec_left(&value_1, i - count);
      add_big_decimal(value_1, *result, result);
      count = i;
    }
  }
  return error;
}

void decreace_scale_big_decimal(s21_big_decimal *val, int n) {
  s21_big_decimal ten = {{10, 0, 0, 0, 0, 0, 0, 0}}, tmp = {0};
  for (int i = 0; i < n; i++) {
    div_big_decimal(*val, ten, &tmp);
    *val = tmp;
    zero_big_decimal(&tmp);
  }
}

int div_big_decimal(s21_big_decimal value_1, s21_big_decimal value_2,
                    s21_big_decimal *result) {
  int b_1 = 0, b_2 = 0, bit_2 = 0, scale = 0, diff = 0, save_scale = 0;
  s21_big_decimal tmp = {0};
  find_highest_bit_big_decimal(value_1, value_2, &b_1, &b_2);
  bit_2 = b_2;
  for (int i = 0; i < 96 && is_big_decimal_not_empty(value_1);) {
    if (i > 0) {
      shift_big_dec_left(&value_2, 1);
      increase_scale_big_decimal(result, 1);
      increase_scale_big_decimal(&value_1, 1);
      save_scale++;
    }
    scale = equation_bits_big_decimal(&value_1, &value_2);
    save_scale += scale;
    b_1 = b_2 = 0;
    find_highest_bit_big_decimal(value_1, value_2, &b_1, &b_2);
    diff = b_2 - bit_2;
    if (diff < 0) diff = 0;
    for (; diff >= 0 && is_big_decimal_not_empty(value_1);) {
      if (is_greater_big_decimal(value_2, value_1)) {
        set_bit_big(&tmp, 0, 0);
      } else {
        sub_big_decimal(value_1, value_2, &value_1);
        set_bit_big(&tmp, 0, 1);
      }
      i++;
      diff--;
      if (diff >= 0) shift_big_dec_right(&value_2, 1);
      shift_big_dec_left(&tmp, 1);
    }
    if (diff >= 0) shift_big_dec_left(&tmp, diff + 1);
    shift_big_dec_right(&tmp, 1);
    add_big_decimal(*result, tmp, result);
    zero_big_decimal(&tmp);
  }
  return save_scale;
}

void find_highest_bit_big_decimal(s21_big_decimal v1, s21_big_decimal v2,
                                  int *bit_1, int *bit_2) {
  for (int i = 255; i >= 0 && (!(*bit_1) || !(*bit_2)); i--) {
    if (*bit_1 == 0 && get_bit_big(v1, i)) *bit_1 = i;
    if (*bit_2 == 0 && get_bit_big(v2, i)) *bit_2 = i;
  }
}

int is_big_decimal_not_empty(s21_big_decimal val) {
  return val.bits[0] + val.bits[1] + val.bits[2] + val.bits[3] + val.bits[4] +
         val.bits[5] + val.bits[6] + val.bits[7];
}

void increase_scale_big_decimal(s21_big_decimal *val, int n) {
  s21_big_decimal ten = {{10, 0, 0, 0, 0, 0, 0, 0}}, tmp = {0};
  for (int i = 0; i < n; i++) {
    mul_big_decimal(*val, ten, &tmp);
    *val = tmp;
    zero_big_decimal(&tmp);
  }
}

int equation_bits_big_decimal(s21_big_decimal *value_1,
                              s21_big_decimal *value_2) {
  int scale = 0;
  while (is_greater_big_decimal(*value_2, *value_1)) {
    increase_scale_big_decimal(value_1, 1);
    scale++;
  }
  while (is_greater_or_equal_big_decimal(*value_1, *value_2)) {
    shift_big_dec_left(value_2, 1);
  }
  shift_big_dec_right(value_2, 1);
  return scale;
}

int is_greater_big_decimal(s21_big_decimal value_1, s21_big_decimal value_2) {
  int result = 0, out = 0;
  for (int i = 7; i >= 0 && !result && !out; i--) {
    if (value_1.bits[i] || value_2.bits[i]) {
      if (value_1.bits[i] > value_2.bits[i]) {
        result = 1;
      }
      if (value_1.bits[i] != value_2.bits[i]) out = 1;
    }
  }
  return result;
}

void sub_big_decimal(s21_big_decimal value_1, s21_big_decimal value_2,
                     s21_big_decimal *result) {
  int tmp = 0, res = 0;
  for (int i = 0; i < 256; i++) {
    res = get_bit_big(value_1, i) - get_bit_big(value_2, i) - tmp;
    tmp = res < 0;
    res = abs(res);
    set_bit_big(result, i, res % 2);
  }
}

void shift_big_dec_right(s21_big_decimal *val, int num) {
  int buffer[7] = {0};
  for (int k = 0; k < num; k++) {
    for (int i = 0; i < 7; i++) {
      buffer[i] = get_bit_big(*val, (i + 1) * 32);
    }
    for (int i = 0; i < 7; i++) {
      val->bits[i] >>= 1;
      set_bit_big(val, (i + 1) * 32 - 1, buffer[i]);
    }
    val->bits[7] >>= 1;
  }
}

int is_greater_or_equal_big_decimal(s21_big_decimal value_1,
                                    s21_big_decimal value_2) {
  int result = 0, out = 0;
  for (int i = 7; i >= 0 && !out && !result; i--) {
    if (value_1.bits[i] != 0 || value_2.bits[i] != 0) {
      if (value_1.bits[i] >= value_2.bits[i]) {
        result = 1;
      }
      out = 1;
    }
  }
  return result;
}

void import_to_small_decimal(s21_decimal *value_1, s21_big_decimal value_2) {
  value_1->bits[0] = value_2.bits[0];
  value_1->bits[1] = value_2.bits[1];
  value_1->bits[2] = value_2.bits[2];
}