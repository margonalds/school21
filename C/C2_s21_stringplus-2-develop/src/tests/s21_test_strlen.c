#include <check.h>
#include <string.h>

#include "../s21_string.h"

START_TEST(test_s21_strlen_basic) {
  char *str = "Hello, World!";
  ck_assert_uint_eq(s21_strlen(str), strlen(str));
}
END_TEST

START_TEST(test_s21_strlen_empty) {
  char *str = "";
  ck_assert_uint_eq(s21_strlen(str), strlen(str));
}
END_TEST

START_TEST(test_s21_strlen_long) {
  char *str =
      "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nullam non "
      "urna vel lacus convallis aliquet.";
  ck_assert_uint_eq(s21_strlen(str), strlen(str));
}
END_TEST

START_TEST(test_s21_strlen_one_char) {
  char *str = "A";
  ck_assert_uint_eq(s21_strlen(str), strlen(str));
}
END_TEST

START_TEST(test_s21_strlen_special_chars) {
  char *str = "\t\n\r\v\f";
  ck_assert_uint_eq(s21_strlen(str), strlen(str));
}
END_TEST

Suite *s21_strlen_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_strlen");

  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_strlen_basic);
  tcase_add_test(tc_core, test_s21_strlen_empty);
  tcase_add_test(tc_core, test_s21_strlen_long);
  tcase_add_test(tc_core, test_s21_strlen_one_char);
  tcase_add_test(tc_core, test_s21_strlen_special_chars);
  suite_add_tcase(s, tc_core);

  return s;
}

int main(void) {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = s21_strlen_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? 0 : 1;
}