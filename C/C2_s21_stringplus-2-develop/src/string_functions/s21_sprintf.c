#include "../s21_string.h"

int s21_sprintf(char *buffer, char *format, ...) {
  if (buffer[0]) s21_memset(buffer, '\0', sizeof(char) * s21_strlen(buffer));
  int sym_num = 0;
  bool is_format = 0, space_posible = 0;
  char spec_buffer[500] = {'\0'};
  char str[16000] = {'\0'};
  va_list option;
  va_start(option, format);
  while (format[sym_num] != '\0') {
    if (format[sym_num] == '%' && is_format == 0) {
      is_format = 1;
      space_posible = 1;
      ++sym_num;
      continue;
    }
    if ((is_format && format[sym_num] != ' ') ||
        (format[sym_num] == ' ' && space_posible == 1)) {
      s21_strncat(spec_buffer, &format[sym_num], 1);
      space_posible = 0;
    }
    if (is_format && is_spec(format[sym_num])) {
      Specifiers sprintf_spec = {0};
      sprintf_spec._accuracy = sprintf_spec._width = -1;
      s21_sprintf_parser(spec_buffer, &sprintf_spec);
      s21_specifier_proccess(str, &option, sprintf_spec);
      s21_size_t strLength = s21_strlen(str);
      s21_strncat(buffer, str, strLength);
      s21_memset(str, '\0', sizeof(char) * 16000);
      s21_memset(spec_buffer, '\0', sizeof(char) * 500);
      is_format = 0;
      ++sym_num;
      continue;
    }
    if (is_format == 0) s21_strncat(buffer, &format[sym_num], 1);
    ++sym_num;
  }

  va_end(option);
  return s21_strlen(buffer);
}

int s21_sprintf_parser(char *format, Specifiers *spec) {
  bool result = 0;
  int numLength = 0, count = 0;
  while (format[count] != '\0') {
    //Флаги
    if (format[count] == '-') spec->_rightAlign = 1;
    if (format[count] == '+') spec->_sign = 1;
    if (format[count] == ' ') spec->_space = 1;
    //Ширина
    if (format[count] >= 48 && format[count] <= 57) {
      spec->_width = s21_string_to_int(&numLength, format, count);
      count += numLength;
      continue;
    }
    //Точность
    numLength = 0;
    if (format[count] == '.') {
      spec->_accuracy = s21_string_to_int(&numLength, format, ++count);
      count += numLength;
      continue;
    }
    //Длина типа
    if ((format[count] == 'h') || (format[count] == 'l') ||
        (format[count] == 'L')) {
      spec->_len = format[count];
      ++count;
      continue;
    }
    //Типы
    spec->_type = format[count];
    ++count;
  }
  return result;
}

int s21_specifier_proccess(char *str, va_list *option, Specifiers spec) {
  switch (spec._type) {
    case 'f':
      s21_sprintf_f(str, spec, option);
      break;
    case 'd':
      s21_sprintf_d(str, spec, option);
      break;
    case 'u':
      s21_sprintf_u(str, spec, option);
      break;
    case 'c':
      s21_sprintf_c(str, spec, option);
      break;
    case 's':
      s21_sprintf_s(str, spec, option);
      break;
    case '%':
      *str = '%';
      break;
  }
  return 0;
}

char *s21_string_reverse(char *str) {
  char buf;
  s21_size_t len = s21_strlen(str);
  for (int i = 0; i < (int)len / 2; ++i) {
    buf = str[i];
    str[i] = str[len - i - 1];
    str[len - i - 1] = buf;
  }
  return str;
}

char *s21_strcat(char *dest, const char *src) {
  char *d = dest;

  while (*d != '\0') {
    d++;
  }
  while (*src != '\0') {
    *d++ = *src++;
  }

  *d = '\0';
  return dest;
}

char *s21_sprintf_width(char *str, Specifiers spec) {
  s21_size_t strLen = s21_strlen(str);
  char buffer[SPRINTF_MAX_WIDTH] = {'\0'};
  if (spec._width <= SPRINTF_MAX_WIDTH && spec._width > (int)strLen) {
    if (spec._rightAlign == 0) {
      for (int i = 0; i < spec._width; ++i) {
        (i < (spec._width - (int)strLen))
            ? (buffer[i] = ' ')
            : (buffer[i] = str[i - (spec._width - strLen)]);
      }
    } else {
      for (int i = 0; i < spec._width; ++i) {
        (i < (int)strLen) ? (buffer[i] = str[i]) : (buffer[i] = ' ');
      }
    }
    s21_memcpy(str, buffer, s21_strlen(buffer) + 1);
  }
  return str;
}

char *s21_sprintf_sign(char *str, Specifiers spec) {
  char buffer[SPRINTF_MAX_WIDTH] = {'\0'};
  if (is_digit(spec._type) == 1) {
    if (spec._sign == 1)
      (str[0] == '-') ? (buffer[0] = '-') : (buffer[0] = '+');
    if (spec._space == 1)
      (str[0] == '-') ? (buffer[0] = '-') : (buffer[0] = ' ');
    s21_strncat(buffer, str, s21_strlen(str));
    s21_memcpy(str, buffer, s21_strlen(buffer) + 1);
  }  // else if(spec._sign == 1 || spec._space == 1)
  return str;
}

char *s21_sprintf_accuracy(char *str, Specifiers spec) {
  s21_size_t len = s21_strlen(str);
  char buffer[SPRINTF_MAX_WIDTH] = {'\0'};
  if (is_digit(spec._type) == 1 && is_integer(spec._type) == 1) {
    if ((int)len < spec._accuracy) {
      s21_memset(buffer, '0', sizeof(char) * (spec._accuracy - len));
      s21_strncat(buffer, str, len);
      s21_memcpy(str, buffer, s21_strlen(buffer) + 1);
    }
    if (spec._accuracy == 0 && str[0] == '0' && len == 1)
      s21_memset(str, '\0', sizeof(char) * SPRINTF_MAX_WIDTH);
  }
  return str;
}

char *s21_sprintf_d(char *str, Specifiers spec, va_list *option) {
  // TODO Ошибка при записи long int в hd
  short int h_arg = 0;
  long int l_arg = 0;
  int arg = 0;
  switch (spec._len) {
    case 'h':
      h_arg = (short int)va_arg(*option, int);
      s21_du_to_string(str, h_arg);
      break;
    case 'l':
      l_arg = (long int)va_arg(*option, long int);
      s21_du_to_string(str, l_arg);
      break;
    default:
      arg = va_arg(*option, int);
      s21_du_to_string(str, arg);
      break;
  }
  s21_sprintf_accuracy(str, spec);
  s21_sprintf_sign(str, spec);
  s21_sprintf_width(str, spec);
  return str;
}

char *s21_sprintf_u(char *str, Specifiers spec, va_list *option) {
  unsigned short int h_arg = 0;
  unsigned long int l_arg = 0;
  unsigned int arg = 0;
  switch (spec._len) {
    case 'h':
      h_arg = (unsigned short int)va_arg(*option, unsigned int);
      s21_du_to_string(str, h_arg);
      break;
    case 'l':
      l_arg = (unsigned long int)va_arg(*option, unsigned long int);
      s21_du_to_string(str, l_arg);
      break;
    default:
      arg = (unsigned int)va_arg(*option, unsigned int);
      s21_du_to_string(str, arg);
      break;
  }
  s21_sprintf_accuracy(str, spec);
  s21_sprintf_width(str, spec);
  return str;
}

char *s21_sprintf_f(char *str, Specifiers spec, va_list *option) {
  double f_arg;
  long double Lf_arg;
  if (spec._len == 'L') {
    Lf_arg = (long double)va_arg(*option, long double);
    s21_Lf_to_string(str, Lf_arg, spec);
  } else {
    f_arg = (double)va_arg(*option, double);
    s21_Lf_to_string(str, f_arg, spec);
  }
  s21_sprintf_sign(str, spec);
  s21_sprintf_width(str, spec);
  return str;
}

char *s21_sprintf_c(char *str, Specifiers spec, va_list *option) {
  wchar_t wchar;
  wchar_t wstr[5] = {'\0'};
  switch (spec._len) {
    case 'l':
      wchar = va_arg(*option, wchar_t);
      wstr[0] = wchar;
      s21_wchar_to_string(str, wstr, 0);
      break;
    default:
      *str = va_arg(*option, int);
      break;
  }
  s21_sprintf_width(str, spec);
  return str;
}

char *s21_sprintf_s(char *str, Specifiers spec, va_list *option) {
  wchar_t *wstr = S21_NULL;
  char *p = S21_NULL;
  if (spec._len == 'l') {
    wstr = va_arg(*option, wchar_t *);
    if (!wstr) {
      if (spec._accuracy == -1)
        s21_strcat(str, "(null)");
      else
        s21_strncat(str, "\0", 1);
    } else {
      s21_wchar_to_string(str, wstr,
                          (spec._accuracy > -1) ? (spec._accuracy) : (0));
    }
  } else {
    p = va_arg(*option, char *);
    if (!p) {
      if (spec._accuracy == -1)
        s21_strcat(str, "(null)");
      else
        s21_strncat(str, "\0", 1);
    } else {
      if (spec._accuracy > -1)
        s21_strncat(str, p, spec._accuracy);
      else
        s21_strncat(str, p, s21_strlen(p));
    }
  }
  s21_sprintf_width(str, spec);
  return 0;
}

int s21_string_to_int(int *length, char *str, int pos) {
  char buffer[100];
  s21_memset(buffer, 0, sizeof(char) * 100);
  int count = 0;
  int result = 0;
  while (str[pos] != '\0' && str[pos] >= 48 && str[pos] <= 57) {
    buffer[count++] = str[pos++];
  }
  *length = count;
  --count;
  for (int i = 0; i < *length; ++i) {
    result += (int)(buffer[i] - 48) * pow(10, count);
    --count;
  }
  return result;
}

char *s21_du_to_string(char *str, long long arg) {
  int count = 0;
  while (arg > 0) {
    str[count++] = (char)((arg % 10) + 48);
    arg /= 10;
  }
  s21_string_reverse(str);
  return str;
}

char *s21_Lf_to_string(char *str, long double arg, Specifiers spec) {
  long long int rounded_arg, i_part;
  long double f_part;
  int accuracy = (spec._accuracy > -1) ? (spec._accuracy) : (6);

  i_part = (int)arg;
  f_part = arg - i_part;
  s21_du_to_string(str, i_part);
  str[s21_strlen(str)] = '.';
  f_part *= pow(10, accuracy + 1);
  rounded_arg = (long long int)f_part;
  rounded_arg =
      (rounded_arg % 10 < 5) ? (rounded_arg / 10) : (rounded_arg / 10 + 1);

  char buffer[100] = {'\0'};
  s21_du_to_string(buffer, rounded_arg);
  s21_strncat(str, buffer, s21_strlen(buffer));
  return str;
}

char *s21_wchar_to_string(char *str, wchar_t *wstr, s21_size_t len) {
  char *sptr = str;
  int count = len;
  while (*wstr != '\0' && (count-- > 0 || len == 0)) {
    *(sptr++) = (char)*(wstr++);
  }
  return str;
}
