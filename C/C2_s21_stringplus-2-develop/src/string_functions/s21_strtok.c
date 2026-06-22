#include "../s21_string.h"

static char *s21_strtok_last = S21_NULL;

char *s21_strtok(char *str, const char *delim) {
  if (str != S21_NULL) {
    s21_strtok_last = str;
  } else {
    if (s21_strtok_last == S21_NULL) {
      return S21_NULL;
    }
    str = s21_strtok_last;
  }

  while (*str && s21_strchr(delim, *str)) {
    str++;
  }

  if (*str == '\0') {
    s21_strtok_last = S21_NULL;
    return S21_NULL;
  }
  char *token_start = str;

  while (*str && !s21_strchr(delim, *str)) {
    str++;
  }

  if (*str == '\0') {
    s21_strtok_last = S21_NULL;
  } else {
    *str = '\0';
    s21_strtok_last = str + 1;
  }
  return token_start;
}