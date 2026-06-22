#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 0
#define ERROR_CONVERTORS 1
#define ERROR_OTHER 1
#define NUMBER_INF 1
#define NUMBER_NEG_INF 2
#define DIV_BY_ZERO 3
#define ERROR_CONVERT 4

typedef struct {
  int bits[4];
} s21_decimal;

typedef struct {
  unsigned bits[8];
} s21_big_decimal;

// Math
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

// Compare
int s21_is_less(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_equal(s21_decimal a, s21_decimal b);
int s21_is_not_equal(s21_decimal a, s21_decimal b);

// Convertor
int s21_from_int_to_decimal(int src, s21_decimal *val);
int s21_from_decimal_to_int(s21_decimal src, int *val);
int s21_from_float_to_decimal(float src, s21_decimal *val);
int s21_from_decimal_to_float(s21_decimal src, float *val);

// Other
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

// Utils
int get_sign_int(s21_decimal dec);
int get_sign(s21_decimal dec);
void set_sign(s21_decimal *number, int sign);
void set_sign_int(s21_decimal *number, int sign);
int get_bit_int(int res, int position);
int get_bit(s21_decimal dec, int position);
void set_bit(s21_decimal *dec, int position, int value);
int get_e(s21_decimal);
void set_e(s21_decimal *dec, int scale);
int get_highets_pos_before_e(s21_decimal dec);

// Helpers
void copy_dec(s21_decimal *dec, s21_decimal src);
void null_decimal(s21_decimal *num);
int division_by_10(s21_decimal *dec);
s21_decimal init_dec();
s21_decimal sum_decimal(s21_decimal de1, s21_decimal de2);
s21_decimal shift_bits(s21_decimal dec, int shif);
s21_decimal subtraction_decimal(s21_decimal de1, s21_decimal de2);
int is_zero(s21_decimal dec);
void neg_bite_to_pos(s21_decimal *dec, int pos);
void import_to_big_decimal(s21_decimal value_1, s21_big_decimal *value_2);
int get_bit_big(s21_big_decimal val, int index);
void set_bit_big(s21_big_decimal *val, int index, int bit);
void normalization(s21_big_decimal *value_1, s21_big_decimal *value_2,
                   int diff);
void set_e_big(s21_big_decimal *val, int n);
int shift_big_dec_left(s21_big_decimal *val, int num);
int mul_big_decimal(s21_big_decimal value_1, s21_big_decimal value_2,
                    s21_big_decimal *result);
void add_big_decimal(s21_big_decimal value_1, s21_big_decimal value_2,
                     s21_big_decimal *result);
int post_normalization(s21_big_decimal *result, int scale);
void zero_big_decimal(s21_big_decimal *val);
void decreace_scale_big_decimal(s21_big_decimal *val, int n);
int div_big_decimal(s21_big_decimal value_1, s21_big_decimal value_2,
                    s21_big_decimal *result);
int is_big_decimal_not_empty(s21_big_decimal val);
void find_highest_bit_big_decimal(s21_big_decimal v1, s21_big_decimal v2,
                                  int *bit_1, int *bit_2);
void increase_scale_big_decimal(s21_big_decimal *val, int n);
int equation_bits_big_decimal(s21_big_decimal *value_1,
                              s21_big_decimal *value_2);
int is_greater_big_decimal(s21_big_decimal value_1, s21_big_decimal value_2);
void sub_big_decimal(s21_big_decimal value_1, s21_big_decimal value_2,
                     s21_big_decimal *result);
void shift_big_dec_right(s21_big_decimal *val, int num);
int is_greater_or_equal_big_decimal(s21_big_decimal value_1,
                                    s21_big_decimal value_2);
void import_to_small_decimal(s21_decimal *value_1, s21_big_decimal value_2);
void zero_decimal(s21_decimal *val);