#ifndef STRING_H
#define STRING_H

#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define S21_NULL ((void *)0)
#define s21_size_t unsigned long

#define SPRINTF_MAX_WIDTH 15999

#define is_spec(ch)                                                           \
  ((ch) == 'c' || (ch) == 'd' || (ch) == 'i' || (ch) == 'f' || (ch) == 's' || \
   (ch) == 'u' || (ch) == '%' || (ch) == 'g' || (ch) == 'G' || (ch) == 'e' || \
   (ch) == 'E' || (ch) == 'x' || (ch) == 'X' || (ch) == 'o' || (ch) == 'n' || \
   (ch) == 'p')
#define is_digit(ch) (ch == 'd' || ch == 'f' || ch == 'u')
#define is_integer(ch) (ch == 'd' || ch == 'u')

typedef struct {
  bool _rightAlign;   // "-""
  bool _sign;         // "+"
  bool _space;        // " "
  bool _alternative;  // "#"
  bool _zeros;        // "0"
  int _width;         // "ширина"
  bool _varWidth;     // "*" - ширина через переменную
  int _accuracy;      // ".точность"
  bool _varAccuracy;  // ".*" - точность через переменную
  char _len;          // h,l,L - длина типа
  char _type;         // тип
} Specifiers;

/*------------PART 1---------------*/

int s21_memcmp(const void *str1, const void *str2, s21_size_t n);
void *s21_memset(void *str, int c, s21_size_t n);
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);
char *s21_strncpy(char *dest, const char *src, s21_size_t n);
char *s21_strerror(int errnum);
s21_size_t s21_strlen(const char *str);
char *s21_strrchr(const char *str, int c);
char *s21_strtok(char *str, const char *delim);
char *s21_strcat(char *dest, const char *src);
char *s21_strncat(char *dest, const char *src, s21_size_t n);
char *s21_strchr(const char *str, int c);
char *s21_strstr(const char *haystack, const char *needle);
void *s21_memchr(const void *str, int c, size_t n);
void *s21_memcpy(void *dest, const void *src, size_t n);
s21_size_t s21_strcspn(const char *str1, const char *str2);
char *s21_strpbrk(const char *str1, const char *str2);
void skip_symb(const char *needle, int M, int *pref);

/*------------PART 2---------------*/
int s21_sprintf(char *buffer, char *format, ...);
int s21_sprintf_parser(char *format, Specifiers *spec);
int s21_string_to_int(int *length, char *str, int pos);
int s21_types_parser(char c, Specifiers *spec);
int s21_specifier_proccess(char *str, va_list *option, Specifiers spec);

char *s21_string_reverse(char *str);

char *s21_sprintf_width(char *str, Specifiers spec);
char *s21_sprintf_sign(char *str, Specifiers spec);
char *s21_sprintf_accuracy(char *str, Specifiers spec);
char *s21_sprintf_d(char *str, Specifiers spec, va_list *option);
char *s21_sprintf_u(char *str, Specifiers spec, va_list *option);
char *s21_sprintf_f(char *str, Specifiers spec, va_list *option);
char *s21_sprintf_c(char *str, Specifiers spec, va_list *option);
char *s21_sprintf_s(char *str, Specifiers spec, va_list *option);
char *s21_du_to_string(char *str, long long arg);
char *s21_Lf_to_string(char *str, long double arg, Specifiers spec);
char *s21_wchar_to_string(char *str, wchar_t *wstr, s21_size_t len);
char *s21_sprintf_perc(char *str, Specifiers spec);

/*------------PART 5---------------*/
void *s21_to_upper(const char *str);
void *s21_to_lower(const char *str);
void *s21_insert(const char *src, const char *str, s21_size_t start_index);
// void *s21_trim(const char *src, const char *trim_chars);

#endif
