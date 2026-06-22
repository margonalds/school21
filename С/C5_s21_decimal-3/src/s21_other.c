#include "s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  s21_truncate(value, result);

  if (get_sign_int(value)) {
    s21_decimal intet_dec = *result;
    s21_decimal temp;
    s21_sub(value, intet_dec, &temp);

    if (!is_zero(temp)) {
      s21_decimal one = {{1, 0, 0, 0}};
      s21_sub(*result, one, result);
    }
  }

  return OK;
}

int s21_truncate(s21_decimal value, s21_decimal *result) {
  *result = value;
  int scale = get_e(value);

  for (int i = 0; i < scale; i++) {
    division_by_10(&value);
  }

  *result = value;

  return OK;
}

int s21_round(s21_decimal value, s21_decimal *result) {
  int error = OK;

  if (!result) error = ERROR_OTHER;
  int sign = get_sign(value);
  int scale = get_e(value);

  int division_remainder = 0;

  for (int i = 0; i < scale; i++) {
    division_remainder = division_by_10(&value);
  }

  if (division_remainder >= 5) {
    *result = sum_decimal(value, (s21_decimal){{1, 0, 0, 0}});
  } else {
    *result = value;
  }

  set_sign_int(result, sign);

  return error;
}

int s21_negate(s21_decimal value, s21_decimal *result) {
  int error = OK;

  if (!result) error = ERROR_OTHER;

  copy_dec(result, value);

  if (is_zero(value)) {
    set_sign(result, 0);
  } else {
    if (get_sign(value) == 1) {
      set_sign_int(result, -1);
    } else {
      set_sign_int(result, 1);
    }
  }
  return error;
}
