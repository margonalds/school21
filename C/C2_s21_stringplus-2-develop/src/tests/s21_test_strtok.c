#include <check.h>
#include <string.h>

#include "../s21_string.h"

START_TEST(test_s21_strtok_basic) {
  char str[] = "Hello, World! Tokenize me";
  char *token;

  token = s21_strtok(str, " ,!");
  ck_assert_str_eq(token, "Hello");

  token = s21_strtok(S21_NULL, " ,!");
  ck_assert_str_eq(token, "World");

  token = s21_strtok(S21_NULL, " ,!");
  ck_assert_str_eq(token, "Tokenize");

  token = s21_strtok(S21_NULL, " ,!");
  ck_assert_str_eq(token, "me");

  token = s21_strtok(S21_NULL, " ,!");
  ck_assert_ptr_eq(token, S21_NULL);
}
END_TEST

START_TEST(test_s21_strtok_no_delimiters) {
  char str[] = "JustOneToken";
  char *token;

  token = s21_strtok(str, " ,!");
  ck_assert_str_eq(token, "JustOneToken");

  token = s21_strtok(S21_NULL, " ,!");
  ck_assert_ptr_eq(token, S21_NULL);
}
END_TEST

START_TEST(test_s21_strtok_multiple_delimiters) {
  char str[] = "Token1,,Token2,,,Token3";
  char *token;

  token = s21_strtok(str, ",");
  ck_assert_str_eq(token, "Token1");

  token = s21_strtok(S21_NULL, ",");
  ck_assert_str_eq(token, "Token2");

  token = s21_strtok(S21_NULL, ",");
  ck_assert_str_eq(token, "Token3");

  token = s21_strtok(S21_NULL, ",");
  ck_assert_ptr_eq(token, S21_NULL);
}
END_TEST

START_TEST(test_s21_strtok_empty_string) {
  char str[] = "";
  char *token;

  token = s21_strtok(str, ",");
  ck_assert_ptr_eq(token, S21_NULL);
}
END_TEST

START_TEST(test_s21_strtok_consecutive_delimiters) {
  char str[] = ",,,Token,,,";
  char *token;

  token = s21_strtok(str, ",");
  ck_assert_str_eq(token, "Token");

  token = s21_strtok(S21_NULL, ",");
  ck_assert_ptr_eq(token, S21_NULL);
}
END_TEST

Suite *s21_strtok_suite(void) {
  Suite *suite = suite_create("s21_strtok");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_strtok_basic);
  tcase_add_test(tc_core, test_s21_strtok_no_delimiters);
  tcase_add_test(tc_core, test_s21_strtok_multiple_delimiters);
  tcase_add_test(tc_core, test_s21_strtok_empty_string);
  tcase_add_test(tc_core, test_s21_strtok_consecutive_delimiters);

  suite_add_tcase(suite, tc_core);
  return suite;
}

int main(void) {
  Suite *suite = s21_strtok_suite();
  SRunner *runner = srunner_create(suite);

  srunner_run_all(runner, CK_NORMAL);
  int number_failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  return (number_failed == 0) ? 0 : 1;
}
