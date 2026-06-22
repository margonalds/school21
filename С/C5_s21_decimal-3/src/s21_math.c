#include "s21_decimal.h"

void add_big_decimal(s21_big_decimal value_1, s21_big_decimal value_2,
                     s21_big_decimal *result) {
  int res = 0, ovf = 0;
  for (int i = 0; i < 256; i++) {
    res = get_bit_big(value_1, i) + get_bit_big(value_2, i) + ovf;
    ovf = res / 2;
    set_bit_big(result, i, res % 2);
  }
}

int sub_for_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0, scale = 0, sign_res = 0;
  zero_decimal(result);

  if (get_sign_int(value_1) && get_sign_int(value_2)) {
    s21_decimal temporary1 = value_1;
    value_1 = value_2;
    value_2 = temporary1;
    set_sign(&value_1, 0);
    set_sign(&value_2, 0);
  }
  if (get_sign_int(value_1) != get_sign_int(value_2)) {
    get_sign_int(value_1) ? sign_res = 1 : 1;
    set_sign(&value_1, 0);
    set_sign(&value_2, 0);
    error = s21_add(value_1, value_2, result);
  } else {
    s21_big_decimal v1 = {0}, v2 = {0}, r = {0};
    import_to_big_decimal(value_1, &v1);
    import_to_big_decimal(value_2, &v2);

    int diff = get_e(value_1) - get_e(value_2);
    diff > 0 ? set_e(&value_2, get_e(value_2) + diff)
             : set_e(&value_1, get_e(value_1) - diff);
    normalization(&v1, &v2, diff);
    if (is_greater_big_decimal(v1, v2)) {
      s21_big_decimal temporary2 = v1;
      v1 = v2;
      v2 = temporary2;
      set_sign(result, 1);
    }
    sub_big_decimal(v2, v1, &r);
    scale = post_normalization(&r, get_e(value_1));
    if (scale >= 0) {
      import_to_small_decimal(result, r);
      set_e(result, scale);
    } else {
      error = 1;
    }
  }
  if (sign_res == 1) {
    set_sign(result, 1);
  }

  if (error == 1 && get_sign_int(*result)) error = 2;
  if (error) zero_decimal(result);
  return error;
}

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0, get = 0, sign_res = 0;
  *result = init_dec();
  if (get_sign_int(value_1) && get_sign_int(value_2)) {
    sign_res = 1;
  }
  if (get_sign_int(value_1) != get_sign_int(value_2)) {
    int sign = 0;
    sign = get_sign_int(value_1);
    set_sign(&value_1, 1);
    set_sign(&value_2, 1);
    error = sign ? sub_for_add(value_2, value_1, result)
                 : sub_for_add(value_1, value_2, result);
  } else {
    s21_big_decimal v1 = {0}, v2 = {0}, r = {0};
    int scale = 0;
    import_to_big_decimal(value_1, &v1);
    import_to_big_decimal(value_2, &v2);
    int diff = get_e(value_1) - get_e(value_2);
    if (diff > 0) {
      get = get_e(value_1);
      set_e(&value_2, get);
    } else {
      get = get_e(value_2);
      set_e(&value_1, get);
    }
    normalization(&v1, &v2, diff);
    add_big_decimal(v1, v2, &r);
    scale = post_normalization(&r, get_e(value_1));
    if (scale >= 0) {
      import_to_small_decimal(result, r);
      set_e(result, scale);
    } else {
      error = 1;
    }
  }
  if (sign_res == 1) {
    set_sign(result, 1);
  }
  if (error == 1 && get_sign_int(*result)) error = 2;
  if (error) zero_decimal(result);
  return error;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0, scale = 0, sign_res = 0;
  zero_decimal(result);

  if (get_sign_int(value_1) && get_sign_int(value_2)) {
    s21_decimal temporary1 = value_1;
    value_1 = value_2;
    value_2 = temporary1;
    set_sign(&value_1, 0);
    set_sign(&value_2, 0);
  }
  if (get_sign_int(value_1) != get_sign_int(value_2)) {
    get_sign_int(value_1) ? sign_res = 1 : 1;
    set_sign(&value_1, 0);
    set_sign(&value_2, 0);
    error = s21_add(value_1, value_2, result);
  } else {
    s21_big_decimal v1 = {0}, v2 = {0}, r = {0};
    import_to_big_decimal(value_1, &v1);
    import_to_big_decimal(value_2, &v2);

    int diff = get_e(value_1) - get_e(value_2);
    diff > 0 ? set_e(&value_2, get_e(value_2) + diff)
             : set_e(&value_1, get_e(value_1) - diff);
    normalization(&v1, &v2, diff);
    if (is_greater_big_decimal(v2, v1)) {
      s21_big_decimal temporary2 = v1;
      v1 = v2;
      v2 = temporary2;
      set_sign(result, 1);
    }
    sub_big_decimal(v1, v2, &r);
    scale = post_normalization(&r, get_e(value_1));
    if (scale >= 0) {
      import_to_small_decimal(result, r);
      set_e(result, scale);
    } else {
      error = 1;
    }
  }
  if (sign_res == 1) {
    set_sign(result, 1);
  }

  if (error == 1 && get_sign_int(*result)) error = 2;
  if (error) zero_decimal(result);
  return error;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0;
  *result = init_dec();
  int sig = get_sign_int(value_2) ^ get_sign_int(value_1);
  if (!is_zero(value_2)) {
    int scale = 0, res_scale = 0;
    s21_big_decimal v1 = {0}, v2 = {0}, r = {0};
    import_to_big_decimal(value_1, &v1);
    import_to_big_decimal(value_2, &v2);
    if (get_sign_int(value_1) != get_sign_int(value_2)) set_sign(result, 1);
    scale = div_big_decimal(v1, v2, &r);
    set_e(&value_1, get_e(value_1) + scale);
    res_scale = get_e(value_1) - get_e(value_2);
    if (res_scale > 0) {
      res_scale = post_normalization(&r, res_scale);
    } else if (res_scale < 0) {
      increase_scale_big_decimal(&r, abs(res_scale));
      res_scale = post_normalization(&r, 0);
    }
    if (res_scale >= 0) {
      int t = result->bits[3];
      import_to_small_decimal(result, r);
      result->bits[3] = t;
      set_e(result, res_scale);
    } else {
      error = 1;
    }
  } else {
    error = 3;
  }
  if (error == 1 && get_sign_int(*result)) error = 2;
  if (error) zero_decimal(result);
  set_sign(result, sig);
  return error;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0, scale = 0;
  *result = init_dec();
  s21_big_decimal v1 = {0}, v2 = {0}, r = {0};
  import_to_big_decimal(value_1, &v1);
  import_to_big_decimal(value_2, &v2);
  int sig = get_sign_int(value_2) ^ get_sign_int(value_1);
  scale = get_e(value_1) + get_e(value_2);
  error = mul_big_decimal(v1, v2, &r);
  scale = post_normalization(&r, scale);
  if (scale >= 0) {
    set_e(result, scale);
    int t = result->bits[3];
    import_to_small_decimal(result, r);
    result->bits[3] = t;
  } else {
    error = 1;
  }
  if (error == 1 && get_sign_int(*result)) error = 2;
  if (error) zero_decimal(result);
  set_sign(result, sig);
  return error;
}