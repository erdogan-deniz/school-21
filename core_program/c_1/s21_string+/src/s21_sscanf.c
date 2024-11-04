#include "s21_string.h"

typedef struct {
  int form;
  int supr;
  int width;
  int length;
  long int n;
  char buff;
  int eof;
  int err;
} flags;

int caseInt(va_list args, flags *fl, char **strc, int sys);
int caseUns(va_list args, flags *fl, char **strc, int sys);
int caseFlo(va_list args, flags *fl, char **strc);
int casePtr(va_list args, flags *fl, char **strc);
int caseCha(va_list args, flags *fl, char **strc);
int caseStr(va_list args, flags *fl, char **strc);
void spaceTrim(char **strc, flags *fl);
void casePer(char **strc, flags *fl, const char *format);
int flagsInv(char **strc, flags *fl, const char *format);
void caseN(va_list args, flags *fl);
void caseNonFormat(char **strc, flags *fl, const char *format);
int checkBreak(va_list args, flags *fl, char **strc, const char *format);
int switchFormat(va_list args, flags *fl, char **strc, const char *format);
void numericBuff(char **strc, flags *fl);
long s21_strtol(char *str, char **strend, int sys);
unsigned long s21_strtoul(char *str, char **strend, int sys);
long double s21_strtold(char *str, char **strend);
float s21_strtof(char *str, char **strend);
double s21_strtod(char *str, char **strend);

int s21_sscanf(const char *str, const char *format, ...) {
  int res = 0;
  flags fl = {0, 0, 0, 0, 0, '\0', 0, 0};
  char *strc = malloc((s21_strlen(str) + 1) * sizeof(char));
  if (!strc) exit(0);
  strc = s21_strcpy(strc, str);
  spaceTrim(&strc, &fl);
  if (!*strc) fl.eof = 1;
  strc = s21_strcpy(strc - fl.n, str);
  fl.n = 0;
  va_list args;
  va_start(args, format);
  for (; *format; format++) {
    if (flagsInv(&strc, &fl, format)) continue;
    if (fl.form) {
      if ((int)*format > 47 && (int)*format < 58) {
        fl.width = fl.width * 10 + (int)*format - 48;
        continue;
      }
      res += switchFormat(args, &fl, &strc, format);
    } else {
      caseNonFormat(&strc, &fl, format);
    }
    if (checkBreak(args, &fl, &strc, format)) {
      if (!res && fl.eof) res = -1;
      break;
    }
  }
  free(strc - fl.n);
  va_end(args);
  return res;
}

int caseInt(va_list args, flags *fl, char **strc, int sys) {
  int res = 0;
  char *strend;
  numericBuff(strc, fl);
  if (s21_strtol(*strc, s21_NULL, sys) ||
      *(*strc + s21_strspn(*strc, "\n\t \f\x0B\r+-")) == '0') {
    if (!fl->supr) {
      res++;
      if (fl->length == 1)
        *(short int *)va_arg(args, void *) = s21_strtol(*strc, &strend, sys);
      else if (fl->length == 2)
        *(long int *)va_arg(args, void *) = s21_strtol(*strc, &strend, sys);
      else
        *(int *)va_arg(args, void *) = s21_strtol(*strc, &strend, sys);
    } else {
      s21_strtol(*strc, &strend, sys);
    }
    fl->n += strend - *strc;
    *strc = strend;
  } else {
    fl->err = 1;
  }
  fl->form = 0;
  return res;
}

int caseUns(va_list args, flags *fl, char **strc, int sys) {
  int res = 0;
  char *strend;
  numericBuff(strc, fl);
  if (s21_strtoul(*strc, s21_NULL, sys) ||
      *(*strc + s21_strspn(*strc, "\n\t \f\x0B\r+")) == '0') {
    if (!fl->supr) {
      if (s21_strtoul(*strc, s21_NULL, sys) || **strc == '0') res++;
      if (fl->length == 1)
        *(short unsigned *)va_arg(args, void *) =
            s21_strtoul(*strc, &strend, sys);
      else if (fl->length == 2)
        *(long unsigned *)va_arg(args, void *) =
            s21_strtoul(*strc, &strend, sys);
      else
        *(unsigned *)va_arg(args, void *) = s21_strtoul(*strc, &strend, sys);
    } else {
      s21_strtoul(*strc, &strend, sys);
    }
    fl->n += strend - *strc;
    *strc = strend;
  } else {
    fl->err = 1;
  }
  fl->form = 0;
  return res;
}

int caseFlo(va_list args, flags *fl, char **strc) {
  int res = 0;
  char *strend;
  numericBuff(strc, fl);
  if (fabs(s21_strtod(*strc, s21_NULL)) >= 1e-100 ||
      isnan(s21_strtod(*strc, s21_NULL)) ||
      *(*strc + s21_strspn(*strc, "\n\t \f\x0B\r+-")) == '0') {
    if (!fl->supr) {
      res++;
      if (fl->length == 3)
        *(long double *)va_arg(args, void *) = s21_strtold(*strc, &strend);
      else if (fl->length == 2)
        *(double *)va_arg(args, void *) = s21_strtod(*strc, &strend);
      else
        *(float *)va_arg(args, void *) = s21_strtof(*strc, &strend);
    } else {
      s21_strtof(*strc, &strend);
    }
    fl->n += strend - *strc;
    *strc = strend;
  } else {
    fl->err = 1;
  }
  fl->form = 0;
  return res;
}

int casePtr(va_list args, flags *fl, char **strc) {
  int res = 0;
  char *strend;
  if (s21_strtoul(*strc, s21_NULL, 16) ||
      *(*strc + s21_strspn(*strc, "\n\t \f\x0B\r+-")) == '0') {
    numericBuff(strc, fl);
    if (!fl->supr) {
      if (s21_strtoul(*strc, s21_NULL, 16) || **strc == '0') res++;
      *(void **)va_arg(args, void **) = (void *)s21_strtoul(*strc, &strend, 16);
    } else {
      s21_strtoul(*strc, &strend, 16);
    }
    fl->n += strend - *strc;
    *strc = strend;
  } else {
    fl->err = 1;
  }
  fl->form = 0;
  return res;
}

int caseCha(va_list args, flags *fl, char **strc) {
  int res = 0;
  if (!fl->width) fl->width = 2;
  if (!fl->supr) {
    res++;
    if (fl->length == 2)
      mbtowc((wchar_t *)va_arg(args, wchar_t *), *strc, fl->width);
    else
      *(char *)va_arg(args, char *) = **strc;
  }
  if (**strc < 0 && fl->length == 2) {
    (*strc)++;
    fl->n++;
  }
  (*strc)++;
  fl->n++;
  fl->form = 0;
  return res;
}

int caseStr(va_list args, flags *fl, char **strc) {
  int res = 0;
  char *s = malloc(sizeof(char));
  if (!s) exit(0);
  spaceTrim(strc, fl);
  int i = 0;
  for (; **strc && **strc != ' ' && **strc != '\n' && **strc != '\t' &&
         **strc != '\r' && **strc != '\x0B' && **strc != '\f' &&
         (fl->width == 0 || i < fl->width);
       i++, (*strc)++) {
    s[i] = **strc;
    s = realloc(s, (i + 2) * sizeof(char));
    if (!s) exit(0);
  }
  s[i] = '\0';
  int k = s21_strlen(s) + 1;
  va_list s_list;
  va_copy(s_list, args);
  for (int j = 0; j < k; j++) {
    if (!fl->supr) {
      if (!fl->length) *((char *)va_arg(s_list, char *) + j) = s[j];
      if (j + 1 < k) {
        va_end(s_list);
        va_copy(s_list, args);
      }
    }
  }
  va_end(args);
  va_copy(args, s_list);
  if (fl->length == 2 && !fl->supr)
    mbstowcs((wchar_t *)va_arg(args, wchar_t *), s, k);
  free(s);
  if (!fl->supr) res++;
  fl->n += k - 1;
  fl->form = 0;
  va_end(s_list);
  return res;
}

void spaceTrim(char **strc, flags *fl) {
  while (**strc == ' ' || **strc == '\n' || **strc == '\t' || **strc == '\r' ||
         **strc == '\x0B' || **strc == '\f') {
    (*strc)++;
    fl->n++;
  }
}

void casePer(char **strc, flags *fl, const char *format) {
  spaceTrim(strc, fl);
  if (*format == **strc) {
    fl->n++;
    (*strc)++;
  } else {
    fl->err = 1;
  }
  fl->form = 0;
}

int flagsInv(char **strc, flags *fl, const char *format) {
  int res = 0;
  if (*format == '%' && !fl->form) {
    res++;
    fl->form = 1;
    fl->supr = 0;
    fl->length = 0;
    if (fl->buff) {
      *(*strc + s21_strlen(*strc)) = fl->buff;
      fl->buff = '\0';
    }
    fl->width = 0;
  }
  return res;
}

void caseN(va_list args, flags *fl) {
  if (!fl->supr) {
    if (fl->length == 1)
      *(short int *)va_arg(args, void *) = fl->n;
    else if (fl->length == 2)
      *(long int *)va_arg(args, void *) = fl->n;
    else
      *(int *)va_arg(args, void *) = fl->n;
  }
  fl->form = 0;
}

void caseNonFormat(char **strc, flags *fl, const char *format) {
  if (*format == ' ' || *format == '\t' || *format == '\n' || *format == '\r' ||
      *format == '\x0B') {
    while (*format == **strc) {
      (*strc)++;
      fl->n++;
    }
  } else if (**strc == *format) {
    (*strc)++;
    fl->n++;
  } else {
    fl->err = 1;
  }
}

int checkBreak(va_list args, flags *fl, char **strc, const char *format) {
  int res = 0;
  va_list backup;
  va_copy(backup, args);
  if ((!**strc && !fl->buff &&
       (s21_strstr(format, "%n") != s21_strchr(format, '%') ||
        !s21_strstr(format, "%n"))) ||
      !va_arg(backup, void *) || fl->err) {
    res = 1;
  }
  va_end(backup);
  return res;
}

int switchFormat(va_list args, flags *fl, char **strc, const char *format) {
  int res = 0;
  switch (*format) {
    case 'x':
    case 'X':
      res += caseUns(args, fl, strc, 16);
      break;
    case 'p':
      res += casePtr(args, fl, strc);
      break;
    case 'e':
    case 'E':
    case 'f':
    case 'g':
    case 'G':
      res += caseFlo(args, fl, strc);
      break;
    case 'c':
      res += caseCha(args, fl, strc);
      break;
    case 'd':
      res += caseInt(args, fl, strc, 10);
      break;
    case 'i':
      res += caseInt(args, fl, strc, 0);
      break;
    case 'o':
      res += caseUns(args, fl, strc, 8);
      break;
    case 's': {
      res += caseStr(args, fl, strc);
      break;
    }
    case 'u':
      res += caseUns(args, fl, strc, 10);
      break;
    case 'n':
      caseN(args, fl);
      break;
    case '%':
      casePer(strc, fl, format);
      break;
    case '*':
      fl->supr = 1;
      break;
    case 'h':
      fl->length = 1;
      break;
    case 'l':
      fl->length = 2;
      break;
    case 'L':
      fl->length = 3;
      break;
  }
  return res;
}

void numericBuff(char **strc, flags *fl) {
  spaceTrim(strc, fl);
  if (fl->width && !fl->buff && fl->width < (int)s21_strlen(*strc)) {
    fl->buff = *(*strc + fl->width);
    *(*strc + fl->width) = '\0';
  }
}

long s21_strtol(char *str, char **strend, int sys) {
  char *start = str;
  long int res = 0;
  int minus = 1;
  while (*str == ' ' || *str == '\n' || *str == '\t' || *str == '\r' ||
         *str == '\x0B' || *str == '\f')
    str++;
  if (*str == '+') str++;
  if (*str == '-') {
    minus = -1;
    str++;
  }
  if (sys == 0 && *str == '0' && *(str + 1) == 'x')
    sys = 16;
  else if (sys == 0 && *str == '0')
    sys = 8;
  else if (sys == 0)
    sys = 10;
  if (sys == 16 && *str == '0' && *(str + 1) == 'x') str += 2;
  if (sys == 10) {
    for (; *str > 47 && *str < 58; str++, res *= 10) res += *str - 48;
    res /= 10;
  } else if (sys == 8) {
    for (; *str > 47 && *str < 56; str++, res *= 8) res += *str - 48;
    res /= 8;
  } else if (sys == 16) {
    for (; (*str > 47 && *str < 58) || (*str > 64 && *str < 71) ||
           (*str > 96 && *str < 103);
         str++, res *= 16) {
      if (*str > 47 && *str < 58)
        res += *str - 48;
      else if ((*str > 64 && *str < 71))
        res += +*str - 55;
      else
        res += +*str - 87;
    }
    res /= 16;
  }
  if (strend) *strend = start + (str - start);
  return minus * res;
}

unsigned long s21_strtoul(char *str, char **strend, int sys) {
  return s21_strtol(str, strend, sys);
}

float s21_strtof(char *str, char **strend) {
  char *start = str;
  float a, decplace, b;
  int sign = 1;
  while (*str == ' ' || *str == '\n' || *str == '\t' || *str == '\r' ||
         *str == '\x0B' || *str == '\f')
    ++str;
  if (*str == '+') ++str;
  if (*str == '-') {
    sign = -1;
    ++str;
  }
  for (a = 0; *str && isdigit(*str); ++str) a = a * 10 + (*str - '0');
  if (*str == '.') ++str;
  for (decplace = 1.; *str && isdigit(*str); ++str, decplace *= 10.)
    a = a * 10. + (*str - '0');
  if (*str == 'e' || *str == 'E') {
    int bsign = 1;
    if (a <= 1e-6) a = 1;
    ++str;
    if (*str == '-') {
      bsign = -1;
      ++str;
    }
    if (*str == '+') ++str;
    for (b = 0; *str && isdigit(*str); ++str) b = b * 10 + (*str - '0');
    b *= bsign;
  } else {
    b = 0;
  }
  if ((*str == 'n' || *str == 'N') && (str[1] == 'a' || str[1] == 'A') &&
      (str[2] == 'n' || str[2] == 'N')) {
    str += 3;
    a = NAN * sign;
  }
  if ((*str == 'i' || *str == 'I') && (str[1] == 'n' || str[1] == 'N') &&
      (str[2] == 'f' || str[2] == 'F')) {
    str += 3;
    a = INFINITY * sign;
  }
  if (strend) *strend = start + (str - start);
  return (isnan(a) || isinf(a)) ? a : (a * sign / decplace) * powl(10, b);
}

double s21_strtod(char *str, char **strend) {
  char *start = str;
  double a, decplace, b;
  int sign = 1;
  while (*str == ' ' || *str == '\n' || *str == '\t' || *str == '\r' ||
         *str == '\x0B' || *str == '\f')
    ++str;
  if (*str == '+') ++str;
  if (*str == '-') {
    sign = -1;
    ++str;
  }
  for (a = 0; *str && isdigit(*str); ++str) a = a * 10 + (*str - '0');
  if (*str == '.') ++str;
  for (decplace = 1.; *str && isdigit(*str); ++str, decplace *= 10.)
    a = a * 10. + (*str - '0');
  if (*str == 'e' || *str == 'E') {
    int bsign = 1;
    if (a <= 1e-6) a = 1;
    ++str;
    if (*str == '-') {
      bsign = -1;
      ++str;
    }
    if (*str == '+') ++str;
    for (b = 0; *str && isdigit(*str); ++str) b = b * 10 + (*str - '0');
    b *= bsign;
  } else {
    b = 0;
  }
  if ((*str == 'n' || *str == 'N') && (str[1] == 'a' || str[1] == 'A') &&
      (str[2] == 'n' || str[2] == 'N')) {
    str += 3;
    a = NAN * sign;
  }
  if ((*str == 'i' || *str == 'I') && (str[1] == 'n' || str[1] == 'N') &&
      (str[2] == 'f' || str[2] == 'F')) {
    str += 3;
    a = INFINITY * sign;
  }
  if (strend) *strend = start + (str - start);
  return (isnan(a) || isinf(a)) ? a : (a * sign / decplace) * powl(10, b);
}

long double s21_strtold(char *str, char **strend) {
  char *start = str;
  long double a, decplace, b;
  int sign = 1;
  while (*str == ' ' || *str == '\n' || *str == '\t' || *str == '\r' ||
         *str == '\x0B' || *str == '\f')
    ++str;
  if (*str == '+') ++str;
  if (*str == '-') {
    sign = -1;
    ++str;
  }
  for (a = 0; *str && isdigit(*str); ++str) a = a * 10 + (*str - '0');
  if (*str == '.') ++str;
  for (decplace = 1.; *str && isdigit(*str); ++str, decplace *= 10.)
    a = a * 10. + (*str - '0');
  if (*str == 'e' || *str == 'E') {
    int bsign = 1;
    if (a <= 1e-6) a = 1;
    ++str;
    if (*str == '-') {
      bsign = -1;
      ++str;
    }
    if (*str == '+') ++str;
    for (b = 0; *str && isdigit(*str); ++str) b = b * 10 + (*str - '0');
    b *= bsign;
  } else {
    b = 0;
  }
  if ((*str == 'n' || *str == 'N') && (str[1] == 'a' || str[1] == 'A') &&
      (str[2] == 'n' || str[2] == 'N')) {
    str += 3;
    a = NAN * sign;
  }
  if ((*str == 'i' || *str == 'I') && (str[1] == 'n' || str[1] == 'N') &&
      (str[2] == 'f' || str[2] == 'F')) {
    str += 3;
    a = INFINITY * sign;
  }
  if (strend) *strend = start + (str - start);
  return (isnan(a) || isinf(a)) ? a : (a * sign / decplace) * powl(10, b);
}