#include "../s21_string.h"

//Вычисляет длину начального сегмента str1, который полностью состоит из
//символов, не входящих в str2.
s21_size_t s21_strcspn(const char *str1, const char *str2) {
  const char *p1 = str1;
  const char *p2;

  while (*p1 != '\0') {
    p2 = str2;
    while (*p2 != '\0') {
      if (*p1 == *p2) {
        return p1 - str1;
      }
      p2++;
    }
    p1++;
  }

  return p1 - str1;
}
