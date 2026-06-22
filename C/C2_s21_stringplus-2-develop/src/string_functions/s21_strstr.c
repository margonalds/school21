#include "../s21_string.h"

//Алгоритм Кнута-Морриса-Пратта
void skip_symb(const char* needle, int M, int* pref) {
  int len = 0;
  int i = 1;
  pref[0] = 0;

  while (i < M) {
    if (needle[i] == needle[len]) {
      len++;
      pref[i] = len;
      i++;
    } else {
      if (len != 0) {
        len = pref[len - 1];
      } else {
        pref[i] = 0;
        i++;
      }
    }
  }
}

//Ищет первое вхождение строки, на которую указывает аргумент А, в строку, на
//которую указывает аргуент В
char* s21_strstr(const char* haystack, const char* needle) {
  int N = 0;
  int M = 0;

  while (haystack[N] != '\0') N++;
  while (needle[M] != '\0') M++;

  if (M == 0) {
    return (char*)haystack;
  }

  if (N < M) {
    return S21_NULL;
  }

  int pref[M];
  skip_symb(needle, M, pref);

  int i = 0;
  int j = 0;
  while (i < N) {
    if (needle[j] == haystack[i]) {
      i++;
      j++;
    }

    if (j == M) {
      return (char*)haystack + i - j;
    } else if (i < N && needle[j] != haystack[i]) {
      if (j != 0) {
        j = pref[j - 1];
      } else {
        i++;
      }
    }
  }
  return S21_NULL;
}
