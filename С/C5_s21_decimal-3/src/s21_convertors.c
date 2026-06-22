#include "s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int error = OK;

  if (dst == NULL) {
    error = ERROR_CONVERTORS;
  } else {
    null_decimal(dst);

    if (src < 0) {
      set_sign(dst, 1);
      src *= -1;
    }

    for (size_t i = 0; i < 31; i++) {
      if (src & (1 << i)) {
        set_bit(dst, i, 1);
      }
    }
  }

  return error;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int error = OK;

  if (dst == NULL) {
    error = ERROR_CONVERTORS;
  } else {
    long long result = (long long)src.bits[0];
    int exponent = get_e(src);

    if (exponent > 0) {
      for (int i = 0; i < exponent; i++) {
        result /= 10;
      }
    }

    if (src.bits[1] != 0 || src.bits[2] != 0 || result > INT_MAX) {
      error = ERROR_CONVERTORS;
    } else {
      if (get_sign(src) == -1) {
        result = -result;
      }

      if (result < INT_MIN || result > INT_MAX) {
        error = ERROR_CONVERTORS;
      } else {
        *dst = (int)result;
      }
    }
  }
  return error;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int error = OK;
  int exponent = 0;
  unsigned long long int_value = 0;

  if (dst == NULL) {
    return ERROR_CONVERTORS;
  }

  for (int i = 0; i < 4; i++) {
    dst->bits[i] = 0;
  }

  if (src == 0.0f) {
    dst->bits[0] = 0;
    dst->bits[1] = 0;
    dst->bits[2] = 0;
    dst->bits[3] = 0;
    error = OK;
  } else if (isinf(src) || isnan(src) || fabs(src) < 1e-28 ||
             fabs(src) > 7.9228162514264337593543950335e28) {
    error = ERROR_CONVERTORS;
  }

  if (error == OK && src != 0.0f) {
    if (src < 0) {
      dst->bits[3] |= 0x80000000;
      src = -src;
    }
    while (src > 1e7 && exponent < 28) {
      src /= 10;
      exponent++;
    }

    int_value = (unsigned long long)(src * pow(10, 7));

    dst->bits[0] = int_value & 0xFFFFFFFF;
    dst->bits[1] = (int_value >> 32) & 0xFFFFFFFF;

    dst->bits[3] |= (exponent << 16);
  }

  return error;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  *dst = 0.0;
  int error = OK;

  bool negative = (src.bits[3] & 0x80000000) != 0;

  int scale = (src.bits[3] >> 16) & 0xFF;

  if (scale < 0 || scale > 28) {
    error = ERROR_CONVERTORS;
  } else {
    unsigned long long low_bits = (unsigned long long)src.bits[0] |
                                  ((unsigned long long)src.bits[1] << 32);
    unsigned int high_bits = src.bits[2];

    long double value =
        (long double)low_bits + (long double)high_bits * pow(2.0, 64);

    value /= powl(10.0, scale);

    if (negative) {
      value = -value;
    }

    if (fabsl(value) > FLT_MAX) {
      return ERROR_CONVERTORS;
    } else if (fabsl(value) < FLT_MIN && value != 0.0f) {
      return ERROR_CONVERTORS;
    }

    *dst = (float)value;
  }

  return error;
}
