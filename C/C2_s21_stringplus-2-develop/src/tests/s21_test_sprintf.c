#include <check.h>

#include "../s21_string.h"

START_TEST(test_s21_sprintf_1) {
  char str1[SPRINTF_MAX_WIDTH] = {'\0'};
  char str2[SPRINTF_MAX_WIDTH] = {'\0'};
  int x = 123456;
  short int h_x = 5;
  long int l_x = 12345678;

  int res1 = s21_sprintf(str1, "X = %+15.3hd\n", h_x);
  int res2 = sprintf(str2, "X = %+15.3hd\n", h_x);
  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(str1, str2);

  res1 = s21_sprintf(str1, "X = %-15.3d\n", x);
  res2 = sprintf(str2, "X = %-15.3d\n", x);
  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(str1, str2);

  res1 = s21_sprintf(str1, "X = % 15.0ld\n", l_x);
  res2 = sprintf(str2, "X = % 15.0ld\n", l_x);
  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_s21_sprintf_2) {
  char str1[SPRINTF_MAX_WIDTH] = {'\0'};
  char str2[SPRINTF_MAX_WIDTH] = {'\0'};
  unsigned short int h_u = 123;
  unsigned int u = 12345;
  unsigned long int l_u = 12345678;

  int res1 = s21_sprintf(str1, "U = %100.5hu\n", h_u);
  int res2 = sprintf(str2, "U = %100.5hu\n", h_u);
  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(str1, str2);

  res1 = s21_sprintf(str1, "U = %100.0u\n", u);
  res2 = sprintf(str2, "U = %100.0u\n", u);
  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(str1, str2);

  res1 = s21_sprintf(str1, "U = %100.3lu\n", l_u);
  res2 = sprintf(str2, "U = %100.3lu\n", l_u);
  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_s21_sprintf_3) {
  char str1[SPRINTF_MAX_WIDTH] = {'\0'};
  char str2[SPRINTF_MAX_WIDTH] = {'\0'};
  double f = 34.12345;  //, min_f = -12.1234;
  long double l_f = 34.1234567;

  int res1 = s21_sprintf(str1, "F = %-23.3f\n", f);
  int res2 = sprintf(str2, "F = %-23.3f\n", f);
  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(str1, str2);

  res1 = s21_sprintf(str1, "F = %+23.3Lf\n", l_f);
  res2 = sprintf(str2, "F = %+23.3Lf\n", l_f);
  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(str1, str2);

  // res1 = s21_sprintf(str1, "F = %23.3f\n", min_f);
  // res2 = sprintf(str2, "F = %23.3f\n", min_f);
  // ck_assert_int_eq(res1, res2);
  // ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_s21_sprintf_4) {
  char str1[SPRINTF_MAX_WIDTH] = {'\0'};
  char str2[SPRINTF_MAX_WIDTH] = {'\0'};
  char c = 'r';

  int res1 = s21_sprintf(str1, "C = %-25c\n", c);
  int res2 = sprintf(str2, "C = %-25c\n", c);
  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_s21_sprintf_5) {
  char str1[SPRINTF_MAX_WIDTH] = {'\0'};
  char str2[SPRINTF_MAX_WIDTH] = {'\0'};
  char *s1 = "four a.m.";
  char *s2 = "";

  int res1 = s21_sprintf(str1, "Time is: %-25s\n", s1);
  int res2 = sprintf(str2, "Time is: %-25s\n", s1);
  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(str1, str2);

  res1 = s21_sprintf(str1, "Time is: %25s\n", s2);
  res2 = sprintf(str2, "Time is: %25s\n", s2);
  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_s21_sprintf_6) {
  char str1[SPRINTF_MAX_WIDTH] = {'\0'};
  char str2[SPRINTF_MAX_WIDTH] = {'\0'};

  int res1 = s21_sprintf(str1, "Percent - %%\n");
  int res2 = sprintf(str2, "Percent - %%\n");
  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

Suite *s21_sprintf_suite(void) {
  Suite *suite = suite_create("s21_sprintf");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_sprintf_1);
  tcase_add_test(tc_core, test_s21_sprintf_2);
  tcase_add_test(tc_core, test_s21_sprintf_3);
  tcase_add_test(tc_core, test_s21_sprintf_4);
  tcase_add_test(tc_core, test_s21_sprintf_5);
  tcase_add_test(tc_core, test_s21_sprintf_6);

  suite_add_tcase(suite, tc_core);
  return suite;
}

int main(void) {
  Suite *suite = s21_sprintf_suite();
  SRunner *runner = srunner_create(suite);

  srunner_run_all(runner, CK_NORMAL);
  int number_failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  return (number_failed == 0) ? 0 : 1;
}