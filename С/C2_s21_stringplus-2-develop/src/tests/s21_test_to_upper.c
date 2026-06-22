#include <check.h>

#include "../s21_string.h"

START_TEST(to_upper_test) {
  char s1[] = "rIsE reY123\0";
  char *test01 = s21_to_upper(s1);
  ck_assert_str_eq(test01, "RISE REY123");
  free(test01);

  char s2[] = "i am all The SithS\n\0";
  char *test02 = s21_to_upper(s2);
  ck_assert_str_eq(test02, "I AM ALL THE SITHS\n");
  free(test02);

  char s3[] = "AND I AM ALL THE JEDI\n\0";
  char *test03 = s21_to_upper(s3);
  ck_assert_str_eq(test03, "AND I AM ALL THE JEDI\n");
  free(test03);

  char s4[] = " \n\0";
  char *test04 = s21_to_upper(s4);
  ck_assert_str_eq(test04, " \n");
  free(test04);

  char s5[] = "TRYAMtryamtryatryatrya trya TRYAM\0";
  char *test05 = s21_to_upper(s5);
  ck_assert_str_eq(test05, "TRYAMTRYAMTRYATRYATRYA TRYA TRYAM");
  free(test05);
}
END_TEST

Suite *s21_to_upper_suite(void) {
  Suite *suite = suite_create("s21_to_upper");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, to_upper_test);
  suite_add_tcase(suite, tc_core);

  return suite;
}

int main(void) {
  Suite *suite = s21_to_upper_suite();
  SRunner *runner = srunner_create(suite);

  srunner_run_all(runner, CK_NORMAL);
  int number_failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}