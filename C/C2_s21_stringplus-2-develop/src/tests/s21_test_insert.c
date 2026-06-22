#include <check.h>
#include <string.h>

#include "../s21_string.h"

START_TEST(insert_test) {
  char *s1 = "Tut mogla bit vasha reclama";
  char *s2 = "reclama rastet ";
  char *s3 = "bystro";
  char *res1 = s21_insert(s1, "reclama", 4);
  char *res2 = s21_insert(s2, s3, 8);
  char *res3 = s21_insert(s1, s3, 4);

  ck_assert_str_eq(res1, "Tut reclamamogla bit vasha reclama");
  ck_assert_str_eq(res2, "reclama bystrorastet ");
  ck_assert_str_eq(res3, "Tut bystromogla bit vasha reclama");

  free(res1);
  free(res2);
  free(res3);
}
END_TEST

Suite *s21_insert_suite(void) {
  Suite *suite = suite_create("s21_insert");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, insert_test);
  suite_add_tcase(suite, tc_core);

  return suite;
}

int main(void) {
  Suite *suite = s21_insert_suite();
  SRunner *runner = srunner_create(suite);

  srunner_run_all(runner, CK_NORMAL);
  int number_failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}