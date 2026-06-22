#include <check.h>

#include "../s21_decimal.h"

// Тесты лдя s21_float_to_decimal

START_TEST(test_positive_float_conversion) {
  s21_decimal dec;
  float src = 123.456;
  int result = s21_from_float_to_decimal(src, &dec);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_negative_float_conversion) {
  s21_decimal dec;
  float src = -123.456;
  int result = s21_from_float_to_decimal(src, &dec);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_small_float_conversion) {
  s21_decimal dec;
  float src = 1e-30;
  int result = s21_from_float_to_decimal(src, &dec);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_zero_float_conversion) {
  s21_decimal dec;
  float src = 0.0;
  int result = s21_from_float_to_decimal(src, &dec);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_high_precision_float_conversion) {
  s21_decimal dec;
  float src = 123.456789;
  int result = s21_from_float_to_decimal(src, &dec);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_nan_float_conversion) {
  s21_decimal dec;
  float src = NAN;
  int result = s21_from_float_to_decimal(src, &dec);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_infinity_float_conversion) {
  s21_decimal dec;
  float src = INFINITY;
  int result = s21_from_float_to_decimal(src, &dec);
  ck_assert_int_eq(result, 1);
}
END_TEST

// Тесты для s21_decimal_to_float

START_TEST(test_decimal_to_float_conversion) {
  s21_decimal dec = {{123456789, 0, 0, 0}};
  float result;
  int res = s21_from_decimal_to_float(dec, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_float_eq_tol(result, 123456789.0, 1e-6);
}
END_TEST

START_TEST(test_decimal_to_float_negative) {
  s21_decimal dec = {{123456789, 0, 0, 0x80000000}};
  float result;
  int res = s21_from_decimal_to_float(dec, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_float_eq_tol(result, -123456789.0, 1e-6);
}
END_TEST

START_TEST(test_decimal_to_float_zero) {
  s21_decimal dec = {{0, 0, 0, 0}};
  float result;
  int res = s21_from_decimal_to_float(dec, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_float_eq(result, 0.0);
}
END_TEST

START_TEST(test_decimal_to_float_with_decimal_places) {
  s21_decimal dec = {{123456789, 0, 0, 0x00050000}};
  float result;
  int res = s21_from_decimal_to_float(dec, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_float_eq_tol(result, 1234.56789, 1e-6);
}
END_TEST

START_TEST(test_decimal_to_float_large) {
  s21_decimal dec = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  float result;
  int res = s21_from_decimal_to_float(dec, &result);
  ck_assert_int_eq(res, 0);
  ck_assert(result > 7.922816e28);
}
END_TEST

// Тесты для s21_floor

START_TEST(test_floor_positive) {
  s21_decimal value = {{123456789, 0, 0, 0x00100000}};
  s21_decimal result;
  int res = s21_floor(value, &result);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(test_floor_negative) {
  s21_decimal value = {{123456789, 0, 0, 0x80100000}};
  s21_decimal result;
  int res = s21_floor(value, &result);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(test_floor_positive_with_fraction) {
  s21_decimal value = {{123456789, 0, 0, 0x00050000}};
  s21_decimal result;
  int res = s21_floor(value, &result);
  ck_assert_int_eq(res, 0);
  s21_decimal expected = {{1234, 0, 0, 0}};
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_floor_negative_with_fraction) {
  s21_decimal value = {{123456789, 0, 0, 0x80050000}};
  s21_decimal result;
  int res = s21_floor(value, &result);
  ck_assert_int_eq(res, 0);
  s21_decimal expected = {{1235, 0, 0, 0x80000000}};
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_floor_zero) {
  s21_decimal value = {{0, 0, 0, 0}};
  s21_decimal result;
  int res = s21_floor(value, &result);
  ck_assert_int_eq(res, 0);
  s21_decimal expected = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

// Тесты для s21_truncate

START_TEST(test_truncate_positive_with_fraction) {
  s21_decimal value = {{123456789, 0, 0, 0x00050000}};
  s21_decimal result;
  s21_decimal expected = {{1234, 0, 0, 0}};
  int res = s21_truncate(value, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_truncate_negative_with_fraction) {
  s21_decimal value = {{123456789, 0, 0, 0x80050000}};
  s21_decimal result;
  s21_decimal expected = {{1234, 0, 0, 0x80000000}};
  int res = s21_truncate(value, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_truncate_positive) {
  s21_decimal value = {{1234, 0, 0, 0x00000000}};
  s21_decimal result;
  s21_decimal expected = {{1234, 0, 0, 0}};
  int res = s21_truncate(value, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_truncate_negative) {
  s21_decimal value = {{1234, 0, 0, 0x80000000}};
  s21_decimal result;
  s21_decimal expected = {{1234, 0, 0, 0x80000000}};
  int res = s21_truncate(value, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_truncate_zero) {
  s21_decimal value = {{0, 0, 0, 0}};
  s21_decimal result;
  s21_decimal expected = {{0, 0, 0, 0}};
  int res = s21_truncate(value, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

// Тесты для s21_int_to_decimal

START_TEST(test_int_to_decimal_positive) {
  s21_decimal dec;
  int src = 12345;
  int result = s21_from_int_to_decimal(src, &dec);

  ck_assert_int_eq(result, OK);
  ck_assert_uint_eq(dec.bits[0], 12345);
  ck_assert_uint_eq(dec.bits[3] >> 31, 0);
}
END_TEST

START_TEST(test_int_to_decimal_negative) {
  int src = -42;
  s21_decimal dst;

  int result = s21_from_int_to_decimal(src, &dst);

  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(dst.bits[3] & (1 << 31), (1 << 31));
  ck_assert_int_eq(dst.bits[0], 42);
}
END_TEST

START_TEST(test_int_to_decimal_zero) {
  s21_decimal dec;
  int src = 0;
  int result = s21_from_int_to_decimal(src, &dec);

  ck_assert_int_eq(result, OK);
  ck_assert_uint_eq(dec.bits[0], 0);
}
END_TEST

START_TEST(test_int_to_decimal_max_int) {
  s21_decimal dec;
  int src = INT_MAX;
  int result = s21_from_int_to_decimal(src, &dec);

  ck_assert_int_eq(result, OK);
  ck_assert_uint_eq(dec.bits[0], INT_MAX);
}
END_TEST

START_TEST(test_int_to_decimal_negative2) {
  int src = -6789;
  s21_decimal dst;

  int result = s21_from_int_to_decimal(src, &dst);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(dst.bits[3] & (1u << 31), (1u << 31));
  ck_assert_uint_eq(dst.bits[0], 6789);
  ck_assert_uint_eq(dst.bits[1], 0);
  ck_assert_uint_eq(dst.bits[2], 0);
}
END_TEST

START_TEST(test_int_to_decimal_null_pointer) {
  int src = 42;
  int result = s21_from_int_to_decimal(src, NULL);

  ck_assert_int_ne(result, 0);
}
END_TEST

// Тесты для s21_from_decimal_to_int

START_TEST(test_decimal_to_int_positive) {
  s21_decimal dec;
  int dst;
  dec.bits[0] = 12345;
  dec.bits[1] = 0;
  dec.bits[2] = 0;
  dec.bits[3] = 0;

  int result = s21_from_decimal_to_int(dec, &dst);

  ck_assert_int_eq(result, OK);
  ck_assert_int_eq(dst, 12345);
}
END_TEST

START_TEST(test_decimal_to_int_negative) {
  s21_decimal dec;
  int dst;
  dec.bits[0] = 54321;
  dec.bits[1] = 0;
  dec.bits[2] = 0;
  dec.bits[3] = (1 << 31);

  int result = s21_from_decimal_to_int(dec, &dst);

  ck_assert_int_eq(result, OK);
  ck_assert_int_eq(dst, -54321);
}
END_TEST

START_TEST(test_decimal_to_int_zero) {
  s21_decimal dec;
  int dst;
  dec.bits[0] = 0;
  dec.bits[1] = 0;
  dec.bits[2] = 0;
  dec.bits[3] = 0;

  int result = s21_from_decimal_to_int(dec, &dst);

  ck_assert_int_eq(result, OK);
  ck_assert_int_eq(dst, 0);
}
END_TEST

START_TEST(test_decimal_to_int_overflow) {
  s21_decimal dec;
  int dst;
  dec.bits[0] = UINT_MAX;
  dec.bits[1] = 1;
  dec.bits[2] = 0;
  dec.bits[3] = 0;

  int result = s21_from_decimal_to_int(dec, &dst);

  ck_assert_int_eq(result, ERROR_CONVERTORS);
}
END_TEST

START_TEST(test_decimal_to_int_null_pointer) {
  s21_decimal dec;
  dec.bits[0] = 12345;
  dec.bits[3] = 0;

  int result = s21_from_decimal_to_int(dec, NULL);

  ck_assert_int_eq(result, ERROR_CONVERTORS);
}
END_TEST

START_TEST(test_decimal_to_int_max_decimal) {
  s21_decimal dec;
  int dst;

  dec.bits[0] = UINT_MAX;
  dec.bits[1] = UINT_MAX;
  dec.bits[2] = UINT_MAX;
  dec.bits[3] = 0;

  int result = s21_from_decimal_to_int(dec, &dst);

  ck_assert_int_eq(result, ERROR_CONVERTORS);
}
END_TEST

START_TEST(test_s21_round_zero) {
  s21_decimal value = {{0, 0, 0, 0}};
  s21_decimal result;
  ck_assert_int_eq(s21_round(value, &result), 0);
  ck_assert_int_eq(result.bits[0], 0);
}
END_TEST

START_TEST(test_s21_round_positive_no_fraction) {
  s21_decimal value = {{123, 0, 0, 0}};
  s21_decimal result;
  ck_assert_int_eq(s21_round(value, &result), 0);
  ck_assert_int_eq(result.bits[0], 123);
}
END_TEST

START_TEST(test_s21_round_positive_with_fraction_less_than_half) {
  s21_decimal value = {{1234, 0, 0, 1 << 16}};
  s21_decimal result;
  ck_assert_int_eq(s21_round(value, &result), 0);
  ck_assert_int_eq(result.bits[0], 123);
}
END_TEST

START_TEST(test_s21_round_positive_with_fraction_more_than_half) {
  s21_decimal value = {{1267, 0, 0, 1 << 16}};
  s21_decimal result;
  ck_assert_int_eq(s21_round(value, &result), 0);
  ck_assert_int_eq(result.bits[0], 127);
}
END_TEST

START_TEST(test_s21_round_negative_with_fraction_more_than_half) {
  s21_decimal value = {{1567, 0, 0, (1 << 31) | (1 << 16)}};
  s21_decimal result;
  ck_assert_int_eq(s21_round(value, &result), 0);
  ck_assert_int_eq(result.bits[0], 157);
  ck_assert_int_eq(get_sign(result), -1);
}
END_TEST

START_TEST(test_s21_round_large_number) {
  s21_decimal value = {{987654321, 0, 0, 2 << 16}};
  s21_decimal result;
  ck_assert_int_eq(s21_round(value, &result), 0);
  ck_assert_int_eq(result.bits[0], 9876543);
}
END_TEST

START_TEST(test_s21_negate_zero) {
  s21_decimal value = {{0, 0, 0, 0}};
  s21_decimal result;
  ck_assert_int_eq(s21_negate(value, &result), 0);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(get_sign(result), 1);
}
END_TEST

START_TEST(test_s21_negate_positive) {
  s21_decimal value = {{12345, 0, 0, 0}};
  s21_decimal result;
  ck_assert_int_eq(s21_negate(value, &result), 0);
  ck_assert_int_eq(result.bits[0], 12345);
  ck_assert_int_eq(get_sign(result), -1);
}
END_TEST

START_TEST(test_s21_negate_negative) {
  s21_decimal value = {{12345, 0, 0, 1 << 31}};
  s21_decimal result;
  ck_assert_int_eq(s21_negate(value, &result), 0);
  ck_assert_int_eq(result.bits[0], 12345);
  ck_assert_int_eq(get_sign(result), 1);
}
END_TEST

START_TEST(test_s21_negate_large_positive) {
  s21_decimal value = {{987654321, 123456789, 0, 0}};
  s21_decimal result;
  ck_assert_int_eq(s21_negate(value, &result), 0);
  ck_assert_int_eq(result.bits[0], 987654321);
  ck_assert_int_eq(result.bits[1], 123456789);
  ck_assert_int_eq(get_sign(result), -1);
}
END_TEST

START_TEST(test_s21_negate_large_negative) {
  s21_decimal value = {{987654321, 123456789, 0, 1 << 31}};
  s21_decimal result;
  ck_assert_int_eq(s21_negate(value, &result), 0);
  ck_assert_int_eq(result.bits[0], 987654321);
  ck_assert_int_eq(result.bits[1], 123456789);
  ck_assert_int_eq(get_sign(result), 1);
}
END_TEST

START_TEST(test_s21_negate_fractional_value) {
  s21_decimal value = {{123456, 0, 0, 1 << 16}};
  s21_decimal result;
  ck_assert_int_eq(s21_negate(value, &result), 0);
  ck_assert_int_eq(result.bits[0], 123456);
  ck_assert_int_eq(get_sign(result), -1);
}
END_TEST

// Тесты для s21_add

START_TEST(test_add_two_positive_numbers) {
  s21_decimal value_1 = {{1234, 0, 0, 0}};
  s21_decimal value_2 = {{5678, 0, 0, 0}};
  s21_decimal result;
  s21_decimal expected = {{6912, 0, 0, 0}};
  int res = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_add_positive_and_negative_numbers) {
  s21_decimal value_1 = {{5678, 0, 0, 0}};
  s21_decimal value_2 = {{1234, 0, 0, 0x80000000}};
  s21_decimal result;
  s21_decimal expected = {{4444, 0, 0, 0}};
  int res = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_add_two_negative_numbers) {
  s21_decimal value_1 = {{1234, 0, 0, 0x80000000}};
  s21_decimal value_2 = {{5678, 0, 0, 0x80000000}};
  s21_decimal result;
  s21_decimal expected = {{6912, 0, 0, 0x80000000}};
  int res = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_add_with_zero) {
  s21_decimal value_1 = {{1234, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  s21_decimal result;
  s21_decimal expected = {{1234, 0, 0, 0}};
  int res = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_add_with_overflow) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{1, 0, 0, 0}};
  s21_decimal result;
  int res = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(test_add_different_exponents) {
  s21_decimal value_1 = {{12340000, 0, 0, 0x00050000}};
  s21_decimal value_2 = {{5678, 0, 0, 0}};
  s21_decimal result;
  s21_decimal expected = {{580140000, 0, 0, 0x00050000}};
  int res = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_add_same_exponents) {
  s21_decimal value_1 = {{12345678, 0, 0, 0x00050000}};
  s21_decimal value_2 = {{87654321, 0, 0, 0x00050000}};
  s21_decimal result;
  s21_decimal expected = {{99999999, 0, 0, 0x00050000}};
  int res = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_add_result_with_fraction) {
  s21_decimal value_1 = {{50000000, 0, 0, 0x00050000}};
  s21_decimal value_2 = {{33333333, 0, 0, 0x00050000}};
  s21_decimal result;
  s21_decimal expected = {{83333333, 0, 0, 0x00050000}};
  int res = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

// Тесты для s21_sub

START_TEST(test_sub_two_positive_numbers) {
  s21_decimal value_1 = {{5678, 0, 0, 0}};
  s21_decimal value_2 = {{1234, 0, 0, 0}};
  s21_decimal result;
  s21_decimal expected = {{4444, 0, 0, 0}};
  int res = s21_sub(value_1, value_2, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_sub_negative_from_positive) {
  s21_decimal value_1 = {{5678, 0, 0, 0}};
  s21_decimal value_2 = {{1234, 0, 0, 0x80000000}};
  s21_decimal result;
  s21_decimal expected = {{6912, 0, 0, 0}};
  int res = s21_sub(value_1, value_2, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_sub_positive_from_negative) {
  s21_decimal value_1 = {{1234, 0, 0, 0x80000000}};
  s21_decimal value_2 = {{5678, 0, 0, 0}};
  s21_decimal result;
  s21_decimal expected = {{6912, 0, 0, 0x80000000}};
  int res = s21_sub(value_1, value_2, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_sub_two_negative_numbers) {
  s21_decimal value_1 = {{5678, 0, 0, 0x80000000}};
  s21_decimal value_2 = {{1234, 0, 0, 0x80000000}};
  s21_decimal result;
  s21_decimal expected = {{4444, 0, 0, 0x80000000}};
  int res = s21_sub(value_1, value_2, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_sub_with_zero) {
  s21_decimal value_1 = {{1234, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  s21_decimal result;
  s21_decimal expected = {{1234, 0, 0, 0}};
  int res = s21_sub(value_1, value_2, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_sub_same_exponents) {
  s21_decimal value_1 = {{12345678, 0, 0, 0x00050000}};  // 1234.5678
  s21_decimal value_2 = {{87654321, 0, 0, 0x00050000}};  // 8765.4321
  s21_decimal result;
  s21_decimal expected = {{75308643, 0, 0, 0x80050000}};  // -7530.8643
  int res = s21_sub(value_1, value_2, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_sub_different_exponents) {
  s21_decimal value_1 = {{12340000, 0, 0, 0x00050000}};  // 123.40000
  s21_decimal value_2 = {{5678, 0, 0, 0}};               // 5678
  s21_decimal result;
  s21_decimal expected = {{555460000, 0, 0, 0x80050000}};  // -4444.0000
  int res = s21_sub(value_1, value_2, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_sub_result_with_fraction) {
  s21_decimal value_1 = {{50000000, 0, 0, 0x00050000}};  // 5.0000 (exp = 5)
  s21_decimal value_2 = {{33333333, 0, 0, 0x00050000}};  // 3.3333
  s21_decimal result;
  s21_decimal expected = {{16666667, 0, 0, 0x00050000}};  // 1.6667
  int res = s21_sub(value_1, value_2, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_sub_with_negative_and_different_exponents) {
  s21_decimal value_1 = {{12340000, 0, 0, 0x00050000}};  // 1234.0000
  s21_decimal value_2 = {{56780000, 0, 0, 0x80050000}};  // -5678.0000
  s21_decimal result;
  s21_decimal expected = {{69120000, 0, 0, 0x00050000}};  // 6912.0000
  int res = s21_sub(value_1, value_2, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

// Тесты для s21_mul

START_TEST(test_mul_two_positive_numbers) {
  s21_decimal value_1 = {{1234, 0, 0, 0}};
  s21_decimal value_2 = {{5678, 0, 0, 0}};
  s21_decimal result;
  s21_decimal expected = {{7006652, 0, 0, 0}};
  int res = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_mul_negative_and_positive_numbers) {
  s21_decimal value_1 = {{1234, 0, 0, 0x80000000}};
  s21_decimal value_2 = {{5678, 0, 0, 0}};
  s21_decimal result;
  s21_decimal expected = {{7006652, 0, 0, 0x80000000}};
  int res = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_mul_two_negative_numbers) {
  s21_decimal value_1 = {{1234, 0, 0, 0x80000000}};
  s21_decimal value_2 = {{5678, 0, 0, 0x80000000}};
  s21_decimal result;
  s21_decimal expected = {{7006652, 0, 0, 0}};
  int res = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_mul_with_zero) {
  s21_decimal value_1 = {{1234, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  s21_decimal result;
  s21_decimal expected = {{0, 0, 0, 0}};
  int res = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_mul_with_overflow) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{2, 0, 0, 0}};
  s21_decimal result;
  int res = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(test_mul_same_exponents) {
  s21_decimal value_1 = {{12345678, 0, 0, 0x00050000}};  // 123.45678 (exp = 5)
  s21_decimal value_2 = {
      {10000000, 0, 0, 0x00050000}};  // 1.00000 (exp = 5) // 100
  s21_decimal result;
  s21_decimal expected = {{0b10000101100001000101101100000000,
                           0b00000000000000000111000001001000, 0x0,
                           0x000A0000}};  // 123.4567800000 (exp = 10)

  int res = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_mul_different_exponents) {
  s21_decimal value_1 = {{12340000, 0, 0, 0x00050000}};  // 123.40000 (exp = 5)
  s21_decimal value_2 = {{5678, 0, 0, 0}};               // 5678 (exp = 0)
  s21_decimal result;
  s21_decimal expected = {{0b01010000010010100011111111000000, 0b10000, 0x0,
                           0x00050000}};  // 7006652.0000 (exp = 5)
  int res = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

// Тесты для s21_div

START_TEST(test_div_two_positive_numbers) {
  s21_decimal value_1 = {{7006652, 0, 0, 0}};
  s21_decimal value_2 = {{5678, 0, 0, 0}};
  s21_decimal result;
  s21_decimal expected = {{1234, 0, 0, 0}};
  int res = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_div_negative_and_positive_numbers) {
  s21_decimal value_1 = {{7006652, 0, 0, 0x80000000}};
  s21_decimal value_2 = {{5678, 0, 0, 0}};
  s21_decimal result;
  s21_decimal expected = {{1234, 0, 0, 0x80000000}};
  int res = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_div_two_negative_numbers) {
  s21_decimal value_1 = {{7006652, 0, 0, 0x80000000}};
  s21_decimal value_2 = {{5678, 0, 0, 0x80000000}};
  s21_decimal result;
  s21_decimal expected = {{1234, 0, 0, 0}};
  int res = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_div_by_zero) {
  s21_decimal value_1 = {{1234, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  s21_decimal result;
  int res = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(res, 3);
}
END_TEST

START_TEST(test_div_by_one) {
  s21_decimal value_1 = {{1234, 0, 0, 0}};
  s21_decimal value_2 = {{1, 0, 0, 0}};
  s21_decimal result;
  s21_decimal expected = {{1234, 0, 0, 0}};
  int res = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_div_same_exponents) {
  s21_decimal value_1 = {{12345678, 0, 0, 0x00050000}};  // 123.45678 (exp = 5)
  s21_decimal value_2 = {{10000000, 0, 0, 0x00050000}};  // 100.00000 (exp = 5)
  s21_decimal result;
  s21_decimal expected = {{12345678, 0, 0, 0x00070000}};  // 1.2345678 (exp = 0)
  int res = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_div_large_exponents) {
  s21_decimal value_1 = {{0b00010000011110100100000000000000, 0b101101011110011,
                          0, 0x000A0000}};  // 10000.000000 (exp = 10)
  s21_decimal value_2 = {{2, 0, 0, 0}};     // 2 (exp = 0)
  s21_decimal result;
  s21_decimal expected = {{0b10001000001111010010000000000000, 0b10110101111001,
                           0, 0x000A0000}};  // 5000.000000 (exp = 10)
  int res = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

// Тесты для s21_is_less

START_TEST(test_is_less_two_positive_numbers) {
  s21_decimal value_1 = {{1234, 0, 0, 0}};
  s21_decimal value_2 = {{5678, 0, 0, 0}};
  int res = s21_is_less(value_1, value_2);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(test_is_less_negative_and_positive_numbers) {
  s21_decimal value_1 = {{1234, 0, 0, 0x80000000}};
  s21_decimal value_2 = {{5678, 0, 0, 0}};
  int res = s21_is_less(value_1, value_2);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(test_is_less_two_negative_numbers) {
  s21_decimal value_1 = {{1234, 0, 0, 0x80000000}};
  s21_decimal value_2 = {{5678, 0, 0, 0x80000000}};
  int res = s21_is_less(value_2, value_1);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(test_is_less_number_and_zero) {
  s21_decimal value_1 = {{1234, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  int res = s21_is_less(value_2, value_1);
  ck_assert_int_eq(res, 1);
  res = s21_is_less(value_1, value_2);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(test_is_less_equal_numbers) {
  s21_decimal value_1 = {{1234, 0, 0, 0}};
  s21_decimal value_2 = {{1234, 0, 0, 0}};
  int res = s21_is_less(value_1, value_2);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(test_is_less_with_fractional_numbers) {
  s21_decimal value_1 = {{12345678, 0, 0, 0x00050000}};
  s21_decimal value_2 = {{12340000, 0, 0, 0x00050000}};
  int res = s21_is_less(value_2, value_1);
  ck_assert_int_eq(res, 1);
}
END_TEST

// Тесты для s21_is_less_or_equal

START_TEST(test_is_less_or_equal_two_positive_numbers) {
  s21_decimal value_1 = {{1234, 0, 0, 0}};
  s21_decimal value_2 = {{5678, 0, 0, 0}};
  int res = s21_is_less_or_equal(value_1, value_2);
  ck_assert_int_eq(res, 1);
  res = s21_is_less_or_equal(value_2, value_1);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(test_is_less_or_equal_negative_and_positive_numbers) {
  s21_decimal value_1 = {{1234, 0, 0, 0x80000000}};
  s21_decimal value_2 = {{5678, 0, 0, 0}};
  int res = s21_is_less_or_equal(value_1, value_2);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(test_is_less_or_equal_two_negative_numbers) {
  s21_decimal value_1 = {{1234, 0, 0, 0x80000000}};
  s21_decimal value_2 = {{5678, 0, 0, 0x80000000}};
  int res = s21_is_less_or_equal(value_2, value_1);
  ck_assert_int_eq(res, 1);
  res = s21_is_less_or_equal(value_1, value_2);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(test_is_less_or_equal_number_and_zero) {
  s21_decimal value_1 = {{1234, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  int res = s21_is_less_or_equal(value_2, value_1);
  ck_assert_int_eq(res, 1);
  res = s21_is_less_or_equal(value_1, value_2);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(test_is_less_or_equal_equal_numbers) {
  s21_decimal value_1 = {{1234, 0, 0, 0}};
  s21_decimal value_2 = {{1234, 0, 0, 0}};
  int res = s21_is_less_or_equal(value_1, value_2);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(test_is_less_or_equal_with_fractional_numbers) {
  s21_decimal value_1 = {{12345678, 0, 0, 0x00050000}};
  s21_decimal value_2 = {{12340000, 0, 0, 0x00050000}};
  int res = s21_is_less_or_equal(value_2, value_1);
  ck_assert_int_eq(res, 1);
  res = s21_is_less_or_equal(value_1, value_2);
  ck_assert_int_eq(res, 0);
}
END_TEST

// Тесты для s21_is_greater

START_TEST(test_is_greater_two_positive_numbers) {
  s21_decimal value_1 = {{5678, 0, 0, 0}};
  s21_decimal value_2 = {{1234, 0, 0, 0}};
  int res = s21_is_greater(value_1, value_2);
  ck_assert_int_eq(res, 1);
  res = s21_is_greater(value_2, value_1);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(test_is_greater_positive_and_negative_numbers) {
  s21_decimal value_1 = {{5678, 0, 0, 0}};
  s21_decimal value_2 = {{1234, 0, 0, 0x80000000}};
  int res = s21_is_greater(value_1, value_2);
  ck_assert_int_eq(res, 1);
  res = s21_is_greater(value_2, value_1);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(test_is_greater_two_negative_numbers) {
  s21_decimal value_1 = {{1234, 0, 0, 0x80000000}};
  s21_decimal value_2 = {{5678, 0, 0, 0x80000000}};
  int res = s21_is_greater(value_1, value_2);
  ck_assert_int_eq(res, 1);
  res = s21_is_greater(value_2, value_1);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(test_is_greater_number_and_zero) {
  s21_decimal value_1 = {{1234, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  int res = s21_is_greater(value_1, value_2);
  ck_assert_int_eq(res, 1);
  res = s21_is_greater(value_2, value_1);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(test_is_greater_equal_numbers) {
  s21_decimal value_1 = {{1234, 0, 0, 0}};
  s21_decimal value_2 = {{1234, 0, 0, 0}};
  int res = s21_is_greater(value_1, value_2);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(test_is_greater_with_fractional_numbers) {
  s21_decimal value_1 = {{12345678, 0, 0, 0x00050000}};
  s21_decimal value_2 = {{12340000, 0, 0, 0x00050000}};
  int res = s21_is_greater(value_1, value_2);
  ck_assert_int_eq(res, 1);
  res = s21_is_greater(value_2, value_1);
  ck_assert_int_eq(res, 0);
}
END_TEST

// Тесты для s21_is_greater_or_equal

START_TEST(test_is_greater_or_equal_two_positive_numbers) {
  s21_decimal value_1 = {{5678, 0, 0, 0}};
  s21_decimal value_2 = {{1234, 0, 0, 0}};
  int res = s21_is_greater_or_equal(value_1, value_2);
  ck_assert_int_eq(res, 1);
  res = s21_is_greater_or_equal(value_2, value_1);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(test_is_greater_or_equal_positive_and_negative_numbers) {
  s21_decimal value_1 = {{5678, 0, 0, 0}};
  s21_decimal value_2 = {{1234, 0, 0, 0x80000000}};
  int res = s21_is_greater_or_equal(value_1, value_2);
  ck_assert_int_eq(res, 1);
  res = s21_is_greater_or_equal(value_2, value_1);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(test_is_greater_or_equal_two_negative_numbers) {
  s21_decimal value_1 = {{1234, 0, 0, 0x80000000}};
  s21_decimal value_2 = {{5678, 0, 0, 0x80000000}};
  int res = s21_is_greater_or_equal(value_1, value_2);
  ck_assert_int_eq(res, 1);
  res = s21_is_greater_or_equal(value_2, value_1);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(test_is_greater_or_equal_number_and_zero) {
  s21_decimal value_1 = {{1234, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  int res = s21_is_greater_or_equal(value_1, value_2);
  ck_assert_int_eq(res, 1);
  res = s21_is_greater_or_equal(value_2, value_1);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(test_is_greater_or_equal_equal_numbers) {
  s21_decimal value_1 = {{1234, 0, 0, 0}};
  s21_decimal value_2 = {{1234, 0, 0, 0}};
  int res = s21_is_greater_or_equal(value_1, value_2);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(test_is_greater_or_equal_with_fractional_numbers) {
  s21_decimal value_1 = {{12345678, 0, 0, 0x00050000}};
  s21_decimal value_2 = {{12340000, 0, 0, 0x00050000}};
  int res = s21_is_greater_or_equal(value_1, value_2);
  ck_assert_int_eq(res, 1);
  res = s21_is_greater_or_equal(value_2, value_1);
  ck_assert_int_eq(res, 0);
}
END_TEST

// Тесты для s21_is_equal

START_TEST(test_is_equal_two_positive_numbers) {
  s21_decimal value_1 = {{1234, 0, 0, 0}};
  s21_decimal value_2 = {{1234, 0, 0, 0}};
  int res = s21_is_equal(value_1, value_2);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(test_is_equal_two_negative_numbers) {
  s21_decimal value_1 = {{1234, 0, 0, 0x80000000}};
  s21_decimal value_2 = {{1234, 0, 0, 0x80000000}};
  int res = s21_is_equal(value_1, value_2);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(test_is_equal_positive_and_negative_numbers) {
  s21_decimal value_1 = {{1234, 0, 0, 0}};
  s21_decimal value_2 = {{1234, 0, 0, 0x80000000}};
  int res = s21_is_equal(value_1, value_2);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(test_is_equal_number_and_zero) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{1234, 0, 0, 0}};
  int res = s21_is_equal(value_2, value_1);
  ck_assert_int_eq(res, 0);
  res = s21_is_equal(value_1, value_1);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(test_is_equal_two_fractional_numbers) {
  s21_decimal value_1 = {{12345678, 0, 0, 0x00050000}};
  s21_decimal value_2 = {{12345678, 0, 0, 0x00050000}};
  int res = s21_is_equal(value_1, value_2);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(test_is_equal_different_fractional_numbers) {
  s21_decimal value_1 = {{12345678, 0, 0, 0x00050000}};
  s21_decimal value_2 = {{12340000, 0, 0, 0x00050000}};
  int res = s21_is_equal(value_1, value_2);
  ck_assert_int_eq(res, 0);
}
END_TEST

// Тесты для s21_is_not_equal

START_TEST(test_is_not_equal_two_positive_numbers) {
  s21_decimal value_1 = {{1234, 0, 0, 0}};
  s21_decimal value_2 = {{1234, 0, 0, 0}};
  int res = s21_is_not_equal(value_1, value_2);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(test_is_not_equal_two_negative_numbers) {
  s21_decimal value_1 = {{1234, 0, 0, 0x80000000}};
  s21_decimal value_2 = {{1234, 0, 0, 0x80000000}};
  int res = s21_is_not_equal(value_1, value_2);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(test_is_not_equal_positive_and_negative_numbers) {
  s21_decimal value_1 = {{1234, 0, 0, 0}};
  s21_decimal value_2 = {{1234, 0, 0, 0x80000000}};
  int res = s21_is_not_equal(value_1, value_2);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(test_is_not_equal_number_and_zero) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{1234, 0, 0, 0}};
  int res = s21_is_not_equal(value_2, value_1);
  ck_assert_int_eq(res, 1);
  res = s21_is_not_equal(value_1, value_1);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(test_is_not_equal_two_fractional_numbers) {
  s21_decimal value_1 = {{12345678, 0, 0, 0x00050000}};
  s21_decimal value_2 = {{12345678, 0, 0, 0x00050000}};
  int res = s21_is_not_equal(value_1, value_2);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(test_is_not_equal_different_fractional_numbers) {
  s21_decimal value_1 = {{12345678, 0, 0, 0x00050000}};
  s21_decimal value_2 = {{12340000, 0, 0, 0x00050000}};
  int res = s21_is_not_equal(value_1, value_2);
  ck_assert_int_eq(res, 1);
}
END_TEST

Suite *decimal_operations_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_decimal_operations");
  tc_core = tcase_create("Core");

  // Тесты для s21_float_to_decimal

  tcase_add_test(tc_core, test_positive_float_conversion);
  tcase_add_test(tc_core, test_negative_float_conversion);
  tcase_add_test(tc_core, test_small_float_conversion);
  tcase_add_test(tc_core, test_zero_float_conversion);
  tcase_add_test(tc_core, test_high_precision_float_conversion);
  tcase_add_test(tc_core, test_nan_float_conversion);
  tcase_add_test(tc_core, test_infinity_float_conversion);

  // Тесты для s21_decimal_to_float

  tcase_add_test(tc_core, test_decimal_to_float_conversion);
  tcase_add_test(tc_core, test_decimal_to_float_negative);
  tcase_add_test(tc_core, test_decimal_to_float_zero);
  tcase_add_test(tc_core, test_decimal_to_float_large);
  tcase_add_test(tc_core, test_decimal_to_float_with_decimal_places);

  // Тесты для s21_floor

  tcase_add_test(tc_core, test_floor_positive);
  tcase_add_test(tc_core, test_floor_negative);
  tcase_add_test(tc_core, test_floor_positive_with_fraction);
  tcase_add_test(tc_core, test_floor_negative_with_fraction);
  tcase_add_test(tc_core, test_floor_zero);

  // Тесты для s21_truncate

  tcase_add_test(tc_core, test_truncate_negative);
  tcase_add_test(tc_core, test_truncate_positive);
  tcase_add_test(tc_core, test_truncate_positive_with_fraction);
  tcase_add_test(tc_core, test_truncate_negative_with_fraction);
  tcase_add_test(tc_core, test_truncate_zero);

  // Тесты для s21_round
  tcase_add_test(tc_core, test_s21_round_zero);
  tcase_add_test(tc_core, test_s21_round_positive_no_fraction);
  tcase_add_test(tc_core, test_s21_round_positive_with_fraction_less_than_half);
  tcase_add_test(tc_core, test_s21_round_positive_with_fraction_more_than_half);
  tcase_add_test(tc_core, test_s21_round_negative_with_fraction_more_than_half);
  tcase_add_test(tc_core, test_s21_round_large_number);

  // Тесты для s21_negate
  tcase_add_test(tc_core, test_s21_negate_zero);
  tcase_add_test(tc_core, test_s21_negate_positive);
  tcase_add_test(tc_core, test_s21_negate_negative);
  tcase_add_test(tc_core, test_s21_negate_large_positive);
  tcase_add_test(tc_core, test_s21_negate_large_negative);
  tcase_add_test(tc_core, test_s21_negate_fractional_value);

  // Тесты для s21_from_int_to_decimal
  tcase_add_test(tc_core, test_int_to_decimal_positive);
  tcase_add_test(tc_core, test_int_to_decimal_negative);
  tcase_add_test(tc_core, test_int_to_decimal_zero);
  tcase_add_test(tc_core, test_int_to_decimal_max_int);
  tcase_add_test(tc_core, test_int_to_decimal_negative2);
  tcase_add_test(tc_core, test_int_to_decimal_null_pointer);

  // Тесты для s21_from_decimal_to_int
  tcase_add_test(tc_core, test_decimal_to_int_positive);
  tcase_add_test(tc_core, test_decimal_to_int_negative);
  tcase_add_test(tc_core, test_decimal_to_int_zero);
  tcase_add_test(tc_core, test_decimal_to_int_overflow);
  tcase_add_test(tc_core, test_decimal_to_int_null_pointer);
  tcase_add_test(tc_core, test_decimal_to_int_max_decimal);

  // Тесты для s21_add
  tcase_add_test(tc_core, test_add_two_positive_numbers);
  tcase_add_test(tc_core, test_add_positive_and_negative_numbers);
  tcase_add_test(tc_core, test_add_two_negative_numbers);
  tcase_add_test(tc_core, test_add_with_overflow);
  tcase_add_test(tc_core, test_add_with_zero);
  tcase_add_test(tc_core, test_add_result_with_fraction);
  tcase_add_test(tc_core, test_add_same_exponents);
  tcase_add_test(tc_core, test_add_different_exponents);

  // Тесты для s21_sub
  tcase_add_test(tc_core, test_sub_two_positive_numbers);
  tcase_add_test(tc_core, test_sub_negative_from_positive);
  tcase_add_test(tc_core, test_sub_positive_from_negative);
  tcase_add_test(tc_core, test_sub_with_zero);
  tcase_add_test(tc_core, test_sub_two_negative_numbers);
  tcase_add_test(tc_core, test_sub_with_negative_and_different_exponents);
  tcase_add_test(tc_core, test_sub_result_with_fraction);
  tcase_add_test(tc_core, test_sub_different_exponents);
  tcase_add_test(tc_core, test_sub_same_exponents);

  // Тесты лоя s21_mul
  tcase_add_test(tc_core, test_mul_with_overflow);
  tcase_add_test(tc_core, test_mul_with_zero);
  tcase_add_test(tc_core, test_mul_two_negative_numbers);
  tcase_add_test(tc_core, test_mul_negative_and_positive_numbers);
  tcase_add_test(tc_core, test_mul_two_positive_numbers);
  tcase_add_test(tc_core, test_mul_different_exponents);
  tcase_add_test(tc_core, test_mul_same_exponents);

  // Тесты для s21_div
  tcase_add_test(tc_core, test_div_two_positive_numbers);
  tcase_add_test(tc_core, test_div_negative_and_positive_numbers);
  tcase_add_test(tc_core, test_div_two_negative_numbers);
  tcase_add_test(tc_core, test_div_by_zero);
  tcase_add_test(tc_core, test_div_by_one);
  tcase_add_test(tc_core, test_div_large_exponents);
  tcase_add_test(tc_core, test_div_same_exponents);

  // Тесты для s21_is_less
  tcase_add_test(tc_core, test_is_less_with_fractional_numbers);
  tcase_add_test(tc_core, test_is_less_equal_numbers);
  tcase_add_test(tc_core, test_is_less_number_and_zero);
  tcase_add_test(tc_core, test_is_less_two_negative_numbers);
  tcase_add_test(tc_core, test_is_less_negative_and_positive_numbers);
  tcase_add_test(tc_core, test_is_less_two_positive_numbers);

  // Тесты для s21_is_less_or_equal
  tcase_add_test(tc_core, test_is_less_or_equal_with_fractional_numbers);
  tcase_add_test(tc_core, test_is_less_or_equal_equal_numbers);
  tcase_add_test(tc_core, test_is_less_or_equal_number_and_zero);
  tcase_add_test(tc_core, test_is_less_or_equal_two_negative_numbers);
  tcase_add_test(tc_core, test_is_less_or_equal_negative_and_positive_numbers);
  tcase_add_test(tc_core, test_is_less_or_equal_two_positive_numbers);

  // Тесты для s21_is_greater
  tcase_add_test(tc_core, test_is_greater_with_fractional_numbers);
  tcase_add_test(tc_core, test_is_greater_equal_numbers);
  tcase_add_test(tc_core, test_is_greater_number_and_zero);
  tcase_add_test(tc_core, test_is_greater_two_negative_numbers);
  tcase_add_test(tc_core, test_is_greater_positive_and_negative_numbers);
  tcase_add_test(tc_core, test_is_greater_two_positive_numbers);

  // Тесты для s21_is_greater_or_equal
  tcase_add_test(tc_core, test_is_greater_or_equal_with_fractional_numbers);
  tcase_add_test(tc_core, test_is_greater_or_equal_equal_numbers);
  tcase_add_test(tc_core, test_is_greater_or_equal_number_and_zero);
  tcase_add_test(tc_core, test_is_greater_or_equal_two_negative_numbers);
  tcase_add_test(tc_core,
                 test_is_greater_or_equal_positive_and_negative_numbers);
  tcase_add_test(tc_core, test_is_greater_or_equal_two_positive_numbers);

  // Тесты для s21_is_equal
  tcase_add_test(tc_core, test_is_equal_different_fractional_numbers);
  tcase_add_test(tc_core, test_is_equal_two_fractional_numbers);
  tcase_add_test(tc_core, test_is_equal_number_and_zero);
  tcase_add_test(tc_core, test_is_equal_positive_and_negative_numbers);
  tcase_add_test(tc_core, test_is_equal_two_negative_numbers);
  tcase_add_test(tc_core, test_is_equal_two_positive_numbers);

  // Тесты для s21_is_not_equal
  tcase_add_test(tc_core, test_is_not_equal_different_fractional_numbers);
  tcase_add_test(tc_core, test_is_not_equal_two_fractional_numbers);
  tcase_add_test(tc_core, test_is_not_equal_number_and_zero);
  tcase_add_test(tc_core, test_is_not_equal_positive_and_negative_numbers);
  tcase_add_test(tc_core, test_is_not_equal_two_negative_numbers);
  tcase_add_test(tc_core, test_is_not_equal_two_positive_numbers);

  suite_add_tcase(s, tc_core);

  return s;
}

int main(void) {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = decimal_operations_suite();
  sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
