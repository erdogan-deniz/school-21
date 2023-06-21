#include "s21_string.h"

#define TOKENS "cdieEfgGosuxXpn"
char conflicting_char = '.';

typedef struct var_parameters {
  int align_minus;
  int show_sign;
  int space_for_pos;
  int hash_zero;
  int direct_zero;
  int width;
  int star_width;
  int star_precision;
  int precision_zero;
  int dot_check;
  int precision_num;
  int len_h;
  int len_l;
  int len_double;
} params;

void process_string(va_list ap, params *variable, char *s, int *top);
void process_x(va_list ap, params *variable, long unsigned int v_x, char *array,
               int *top, const char *format);
void process_g(va_list ap, params *variable, long double v_e, char *array,
               int *top, const char *format_pointer);
void process_float(va_list ap, params *variable, long double v_f, char *array,
                   int *top);
void process_exp(va_list ap, params *variable, long double v_e, char *array,
                 int *top, const char *format_pointer);
void process_char(va_list ap, params *variable, char *array, int *top);
void process_int(va_list ap, params *variable, char *array, int *top,
                 const char *gen_pointer);
void process_oct(va_list ap, params *variable, char *array, int *top);
void process_p(va_list ap, params *variable, int *v_p, char *array, int *top);
void write_into_main_buf(const char *temp, char *main_buf, int *top, int count,
                         int flag, int hex_flag, int sign);
void align_left(char *main_buf, int *top, int len, int fill, params *variable,
                const char *temp);
int add_zero(char **temp, char *main_buf, int *top, int len, params *variable,
             int *shift);
void add_space(const char *temp, char *main_buf, int *top, int len,
               params *variable);
int parse_params(const char *str_pointer, params *variable, int *shift);
void init_struct(params *res);
char *s21_itoa(long int num);
char *oct_to_string(long int num, params *variable);
void delete_zero(char *g_string, int *top);
char *hex_to_string(unsigned long int num, int upper_flag, int pointer_flag,
                    int nil_flag);
char *float_to_string(long double num, int g_flag, params *variable);
char *exp_to_string(long double v_e, const char *exp_letter, int g_flag,
                    params *variable);
int check_fraction(int *top, params *variable, long double num);
int check_precision(params *variable, int expo);
int add_precision_zero(char **temp, char *main_buf, int *top, params *variable,
                       int flag_x, int *shift);
void add_space_precision_zero(char *temp, char *main_buf, int *top,
                              params *variable);
int find_exp(long double num);
void long_char_helper(wchar_t *long_str, params *variable, char *s, int *top);
void null_helper(params *variable, char *s, int *top);
void normal_string_helper(char *simple_str, params *variable, char *s,
                          int *top);

int s21_sprintf(char *s, const char *format, ...) {
  int top_buffer = 0;
  const char *gen_pointer = s21_NULL;
  int stop_flag = 0;
  long double v_e = 0;
  long double v_f = 0;
  int *v_p = s21_NULL;
  long unsigned int v_x = 0;
  params variable;

  va_list ap;
  va_start(ap, format);
  setlocale(LC_ALL, "");
  setlocale(LC_NUMERIC, "en_US.UTF-8");
  for (gen_pointer = format; *gen_pointer; gen_pointer++) {
    int shift;
    if ((*gen_pointer) != '%') {
      s[top_buffer] = *gen_pointer;
      top_buffer++;
      continue;
    } else {
      shift = 0;
      init_struct(&variable);
      stop_flag = parse_params(gen_pointer, &variable, &shift);
    }
    if (!stop_flag) {
      gen_pointer += shift;
      if (s21_strchr("diu", (int)(*gen_pointer))) {
        process_int(ap, &variable, s, &top_buffer, gen_pointer);
      } else if (*gen_pointer == 'c') {
        process_char(ap, &variable, s, &top_buffer);
      } else if (*gen_pointer == 'E' || *gen_pointer == 'e') {
        process_exp(ap, &variable, v_e, s, &top_buffer, gen_pointer);
      } else if (*gen_pointer == 'f') {
        process_float(ap, &variable, v_f, s, &top_buffer);
      } else if (*gen_pointer == 'G' || *gen_pointer == 'g') {
        process_g(ap, &variable, v_e, s, &top_buffer, gen_pointer);
      } else if (*gen_pointer == 'o') {
        process_oct(ap, &variable, s, &top_buffer);
      } else if (*gen_pointer == 's') {
        process_string(ap, &variable, s, &top_buffer);
      } else if (*gen_pointer == 'x' || *gen_pointer == 'X') {
        process_x(ap, &variable, v_x, s, &top_buffer, gen_pointer);
      } else if (*gen_pointer == 'p') {
        variable.hash_zero = 1;
        process_p(ap, &variable, v_p, s, &top_buffer);
      } else if (*gen_pointer == 'n') {
        int *bytes_num = s21_NULL;
        bytes_num = va_arg(ap, int *);
        *bytes_num = top_buffer;
      } else {
        s[top_buffer] = *gen_pointer;
        top_buffer++;
      }
    }
  }
  s[top_buffer] = '\0';
  va_end(ap);
  return s21_strlen(s);
}

void process_p(va_list ap, params *variable, int *v_p, char *array, int *top) {
  int zero_flag = 0;
  if (variable->star_width == 1) {
    variable->width = va_arg(ap, int);
  }
  v_p = va_arg(ap, int *);
  int nil_flag = 0;
  long long int convert = 0;
  if (v_p != s21_NULL) {
    convert = (long long int)v_p;
  } else {
    nil_flag = 1;
  }
  char *temp = hex_to_string(convert, 0, variable->hash_zero, nil_flag);
  if (variable->width > 0 && variable->align_minus == 0) {
    add_space(temp, array, top, (int)s21_strlen(temp), variable);
  }
  write_into_main_buf(temp, array, top, (int)s21_strlen(temp), zero_flag, 0, 0);
  if (variable->align_minus) {
    align_left(array, top, (int)s21_strlen(temp), variable->width, variable,
               temp);
  }
  free(temp);
}

void process_oct(va_list ap, params *variable, char *array, int *top) {
  int zero_flag = 0;
  long int v_int;
  if (variable->star_width == 1) {
    variable->width = va_arg(ap, int);
  }
  if (variable->star_precision) {
    variable->precision_num = va_arg(ap, int);
  }
  if (variable->precision_num == -1) variable->precision_num = 0;
  if (variable->len_h == 1) {
    v_int = va_arg(ap, int);
  } else if (variable->len_l == 1) {
    v_int = va_arg(ap, long int);
  } else {
    v_int = va_arg(ap, int);
  }
  v_int = (long int)v_int;
  if (variable->precision_num > 0) {
    char *temp_ar = oct_to_string(v_int, variable);
    int size_helper = (variable->hash_zero > 0) ? (s21_strlen(temp_ar) - 1)
                                                : s21_strlen(temp_ar);
    variable->precision_zero = (variable->precision_num - size_helper > 0)
                                   ? (variable->precision_num - size_helper)
                                   : 0;
    free(temp_ar);
  }
  int temp_shift = 0;
  char *temp = oct_to_string(v_int, variable);
  if (variable->precision_zero) {
    if (variable->width > 0 && variable->align_minus == 0) {
      add_space_precision_zero(temp, array, top, variable);
    }
    zero_flag = add_precision_zero(&temp, array, top, variable, 0, &temp_shift);
  } else if (variable->direct_zero) {
    zero_flag = add_zero(&temp, array, top, (int)s21_strlen(temp), variable,
                         &temp_shift);
  } else if (variable->width > 0 && variable->align_minus == 0) {
    add_space(temp, array, top, (int)s21_strlen(temp), variable);
  }
  write_into_main_buf(temp, array, top, (int)s21_strlen(temp), zero_flag, 0, 0);
  if (variable->align_minus) {
    align_left(array, top, (int)s21_strlen(temp), variable->width, variable,
               temp);
  }
  free(temp - temp_shift);
}

char *oct_to_string(long int num, params *variable) {
  char *res = malloc(sizeof(char) * 50);
  if (!res) exit(0);
  char *reverse = malloc(sizeof(char) * 50);
  if (!reverse) {
    free(res);
    exit(0);
  }
  int count = 0;
  int sign = (num >= 0) ? 0 : 1;
  if (num == 0) {
    reverse[count] = '0';
    count++;
  }
  if (!sign) {
    int i = 0;
    long int next = 1;
    long int octanum = 0;
    while (num != 0) {
      octanum = octanum + (num % 8) * next;
      num = num / 8;
      next = next * 10;
    }
    while (octanum > 0) {
      next = octanum % 10;
      reverse[count] = next + '0';
      count++;
      octanum /= 10;
    }
    if (variable->hash_zero) {
      reverse[count] = '0';
      count++;
    }
    for (; i < count; i++) {
      res[i] = reverse[count - i - 1];
    }
    res[i] = '\0';
  } else {
    res[0] = '\0';
  }
  free(reverse);
  return res;
}

void process_string(va_list ap, params *variable, char *s, int *top) {
  char *simple_str = s21_NULL;
  wchar_t *long_str = s21_NULL;
  if (variable->star_width) {
    variable->width = va_arg(ap, int);
  }
  if (variable->star_precision) {
    variable->precision_num = va_arg(ap, int);
  }
  if (variable->len_l == 1) {
    long_str = va_arg(ap, wchar_t *);
    if (!long_str) {
      variable->len_l = 0;
    }
  } else {
    simple_str = va_arg(ap, char *);
  }
  if (variable->len_l == 1) {
    long_char_helper(long_str, variable, s, top);
  } else {
    if (!simple_str) {
      null_helper(variable, s, top);
    } else {
      normal_string_helper(simple_str, variable, s, top);
    }
  }
}

void normal_string_helper(char *simple_str, params *variable, char *s,
                          int *top) {
  char reserve[1000] = {'\0'};
  s21_strcpy(reserve, simple_str);
  int len = (int)s21_strlen(reserve);
  if ((variable->precision_num > 0) && (variable->precision_num < len)) {
    reserve[variable->precision_num] = '\0';
    variable->width -= variable->precision_num;
  } else if (variable->precision_num != 0) {
    variable->width -= len;
  }
  if ((variable->width > 0) && (variable->align_minus == 0)) {
    for (int k = 0; k < variable->width; k++) {
      s[*top] = ' ';
      *top = (*top) + 1;
    }
  }
  if (variable->precision_num != 0) {
    for (int i = 0; i < (int)s21_strlen(reserve); i++) {
      s[*top] = reserve[i];
      *top = (*top) + 1;
    }
  }
  if ((variable->width > 0) && (variable->align_minus == 1)) {
    for (int m = 0; m < variable->width; m++) {
      s[*top] = ' ';
      *top = (*top) + 1;
    }
  }
  s[*top] = '\0';
}

void long_char_helper(wchar_t *long_str, params *variable, char *s, int *top) {
  if (variable->precision_num == -1) variable->precision_num = 0;
  int len = wcslen(long_str);
  int bytes_helper = sizeof(long_str[0]);
  int size_helper = wcstombs(s + (*top), long_str, len * bytes_helper);
  if (variable->precision_num) {
    if (variable->align_minus == 0 && variable->width > size_helper) {
      int space_var = variable->width - variable->precision_num;
      if (space_var > 0) {
        for (int i = 0; i < space_var; i++) {
          s[*top] = ' ';
          *top += 1;
        }
      }
    }
  } else {
    if (variable->align_minus == 0 && variable->width > size_helper) {
      for (int i = 0; i < (variable->width - size_helper); i++) {
        s[*top] = ' ';
        *top += 1;
      }
    }
  }
  if (variable->precision_num) {
    size_helper = (variable->precision_num < size_helper)
                      ? variable->precision_num
                      : size_helper;
  }
  size_helper = wcstombs(s + (*top), long_str, size_helper);
  *top += size_helper;
  if (variable->align_minus == 1 && variable->width > size_helper) {
    if (variable->precision_num > size_helper) {
      int space = variable->width - variable->precision_num;
      if (space > 0) {
        for (int i = 0; i < space; i++) {
          s[*top] = ' ';
          *top += 1;
        }
      }
    } else {
      for (int i = 0; i < (variable->width - size_helper); i++) {
        s[*top] = ' ';
        *top += 1;
      }
    }
  }
}

void null_helper(params *variable, char *s, int *top) {
  char null_str[7] = "(null)";
  int len = (int)s21_strlen(null_str);
  char reserve_buf[10] = {'\0'};
  if ((variable->precision_num > 0) && (variable->precision_num < len)) {
    for (int i = 0; i < variable->precision_num; i++) {
      reserve_buf[i] = null_str[i];
    }
    variable->width -= variable->precision_num;
  } else if (variable->precision_num != 0) {
    for (int j = 0; j < len; j++) {
      reserve_buf[j] = null_str[j];
    }
    variable->width -= len;
  }
  if ((variable->width > 0) && (variable->align_minus == 0)) {
    for (int k = 0; k < variable->width; k++) {
      s[*top] = ' ';
      *top = (*top) + 1;
    }
  }
  for (int l = 0; l < (int)s21_strlen(reserve_buf); l++) {
    s[*top] = reserve_buf[l];
    *top = (*top) + 1;
  }
  if ((variable->width > 0) && (variable->align_minus == 1)) {
    for (int m = 0; m < variable->width; m++) {
      s[*top] = ' ';
      *top = (*top) + 1;
    }
  }
  s[*top] = '\0';
}

void process_x(va_list ap, params *variable, long unsigned int v_x, char *array,
               int *top, const char *format) {
  int zero_flag = 0;
  if (variable->star_width == 1) {
    variable->width = va_arg(ap, int);
  }
  if (variable->star_precision) {
    variable->precision_num = va_arg(ap, int);
  }
  if (variable->precision_num == -1) variable->precision_num = 0;
  if (variable->len_h == 1) {
    v_x = va_arg(ap, int);
  } else if (variable->len_l == 1) {
    v_x = va_arg(ap, long int);
  } else {
    v_x = va_arg(ap, int);
  }
  v_x = (long int)v_x;
  int flag = (*format == 'X') ? 1 : 0;
  if (variable->precision_num > 0) {
    char *temp_ar = hex_to_string(v_x, flag, variable->hash_zero, 0);
    int len_helper = s21_strlen(temp_ar);
    int size_helper = (variable->hash_zero > 0) ? len_helper - 2 : len_helper;
    variable->precision_zero = (variable->precision_num - size_helper > 0)
                                   ? (variable->precision_num - size_helper)
                                   : 0;
    free(temp_ar);
  }
  int temp_shift = 0;
  char *temp = hex_to_string(v_x, flag, variable->hash_zero, 0);
  if (variable->precision_zero) {
    if (variable->width > 0 && variable->align_minus == 0) {
      add_space_precision_zero(temp, array, top, variable);
    }
    zero_flag = add_precision_zero(&temp, array, top, variable, 1, &temp_shift);
  } else if (variable->direct_zero) {
    zero_flag = add_zero(&temp, array, top, (int)s21_strlen(temp), variable,
                         &temp_shift);
  } else if (variable->width > 0 && variable->align_minus == 0) {
    add_space(temp, array, top, (int)s21_strlen(temp), variable);
  }
  int x_flag = (variable->hash_zero > 0) ? 1 : 0;
  write_into_main_buf(temp, array, top, (int)s21_strlen(temp), zero_flag,
                      x_flag, 0);
  if (variable->align_minus) {
    align_left(array, top, (int)s21_strlen(temp), variable->width, variable,
               temp);
  }
  free(temp - temp_shift);
}

void process_g(va_list ap, params *variable, long double v_e, char *array,
               int *top, const char *format_pointer) {
  char *temp = s21_NULL;
  if (variable->star_width) {
    variable->width = va_arg(ap, int);
  }
  if (variable->star_precision) {
    variable->precision_num = va_arg(ap, int);
  }
  if (variable->precision_num == -1) variable->precision_num = 0;
  if (variable->len_double) {
    v_e = va_arg(ap, long double);
  } else {
    v_e = va_arg(ap, double);
  }
  int temp_shift = 0;
  if (v_e >= 0 && variable->show_sign == 1 && variable->width == 0) {
    array[*top] = '+';
    *top += 1;
  }
  if (v_e > 0 && variable->space_for_pos == 1 && variable->width == 0) {
    array[*top] = ' ';
    *top += 1;
  }
  if (v_e == 0) {
    array[*top] = '0';
    *top += 1;
  } else {
    long double pos_v_e = (v_e < 0) ? (v_e * -1) : (v_e);
    int check_exp = find_exp(pos_v_e);
    if (variable->dot_check == 1 && variable->precision_num == 0) {
      variable->precision_num = 1;
    }
    int control = check_precision(variable, check_exp);
    if (control == 1) {
      if (variable->precision_num == 0 && variable->dot_check == 0) {
        variable->precision_num = 5;
      } else if (variable->precision_num > 0) {
        variable->precision_num = variable->precision_num - 1;
      }
      temp = exp_to_string(v_e, format_pointer, 1, variable);
    } else {
      if (variable->precision_num == 0 && variable->dot_check == 0) {
        if (check_exp < 0) {
          check_exp *= -1;
          variable->precision_num = (6 - check_exp);
        } else {
          variable->precision_num = (6 - (check_exp + 1));
        }
      } else if (variable->precision_num == 0 && variable->dot_check == 1) {
        if (check_exp < 0) check_exp *= -1;
        variable->precision_num = check_exp;
      } else if (variable->precision_num > 0) {
        variable->precision_num = (variable->precision_num - (check_exp + 1));
      }
      temp = float_to_string(v_e, 1, variable);
    }
    int zero_flag = 0;
    if (variable->direct_zero) {
      zero_flag = add_zero(&temp, array, top, (int)s21_strlen(temp), variable,
                           &temp_shift);
    } else if (variable->width > 0 && variable->align_minus == 0) {
      add_space(temp, array, top, (int)s21_strlen(temp), variable);
    }
    write_into_main_buf(temp, array, top, (int)s21_strlen(temp), zero_flag, 0,
                        0);
  }
  if (variable->align_minus) {
    align_left(array, top, (int)s21_strlen(temp), variable->width, variable,
               temp);
  }
  array[*top] = '\0';
  free(temp - temp_shift);
}

int find_exp(long double num) {
  int res = 0;
  if (num > 0 && num < 1) {
    while ((long int)num == 0) {
      num = num * 10;
      res++;
    }
    res *= -1;
  } else if (num > 1) {
    while (num != 0) {
      num = (long int)num / 10;
      res++;
    }
    res--;
  }
  return res;
}

void process_float(va_list ap, params *variable, long double v_f, char *array,
                   int *top) {
  int zero_flag = 0;
  if (variable->star_width) {
    variable->width = va_arg(ap, int);
  }
  if (variable->star_precision) {
    variable->precision_num = va_arg(ap, int);
  }
  if (variable->precision_num == -1) variable->precision_num = 0;
  if (variable->len_double) {
    v_f = va_arg(ap, long double);
  } else {
    v_f = va_arg(ap, double);
  }
  if (variable->precision_num == 0 && variable->dot_check == 0) {
    variable->precision_num = 6;
  } else if (variable->precision_num == 0 && variable->dot_check == 1) {
    variable->precision_num = 0;
  }
  if (v_f > 0 && variable->show_sign == 1 && variable->width == 0) {
    array[*top] = '+';
    *top += 1;
  }
  if (v_f >= 0 && variable->space_for_pos == 1 && variable->width == 0) {
    array[*top] = ' ';
    *top += 1;
  }
  int temp_shift = 0;
  char *temp = float_to_string(v_f, 0, variable);
  if (variable->direct_zero == 1) {
    zero_flag = add_zero(&temp, array, top, (int)s21_strlen(temp), variable,
                         &temp_shift);
  } else if (variable->width > 0) {
    add_space(temp, array, top, (int)s21_strlen(temp), variable);
  }
  write_into_main_buf(temp, array, top, (int)s21_strlen(temp), zero_flag, 0, 0);
  if (variable->align_minus) {
    align_left(array, top, (int)s21_strlen(temp), variable->width, variable,
               temp);
  }
  free(temp - temp_shift);
}

void process_exp(va_list ap, params *variable, long double v_e, char *array,
                 int *top, const char *format_pointer) {
  int zero_flag = 0;
  if (variable->star_width) {
    variable->width = va_arg(ap, int);
  }
  if (variable->star_precision) {
    variable->precision_num = va_arg(ap, int);
  }
  if (variable->precision_num == -1) variable->precision_num = 0;
  if (variable->len_double) {
    v_e = va_arg(ap, long double);
  } else {
    v_e = va_arg(ap, double);
  }
  if (variable->dot_check == 1 && variable->precision_num == 0) {
    variable->precision_num = 0;
  } else if (variable->precision_num == 0 && variable->dot_check == 0) {
    variable->precision_num = 6;
  }
  if (v_e > 0 && variable->show_sign == 1 && variable->width == 0) {
    array[*top] = '+';
    *top += 1;
  }
  if (v_e >= 0 && variable->space_for_pos == 1 && variable->width == 0) {
    array[*top] = ' ';
    *top += 1;
  }
  int temp_shift = 0;
  char *temp = exp_to_string(v_e, format_pointer, 0, variable);
  if (variable->direct_zero) {
    zero_flag = add_zero(&temp, array, top, (int)s21_strlen(temp), variable,
                         &temp_shift);
  } else if (variable->width > 0 && variable->align_minus == 0) {
    add_space(temp, array, top, (int)s21_strlen(temp), variable);
  }
  write_into_main_buf(temp, array, top, (int)s21_strlen(temp), zero_flag, 0, 0);
  if (variable->align_minus) {
    align_left(array, top, (int)s21_strlen(temp), variable->width, variable,
               temp);
  }
  free(temp - temp_shift);
}

void process_char(va_list ap, params *variable, char *array, int *top) {
  unsigned char v_char;
  wchar_t long_char;
  if (variable->star_width == 1) {
    variable->width = va_arg(ap, int);
  }
  if (variable->star_precision == 1) {
    variable->precision_num = va_arg(ap, int);
  }
  if (variable->len_l == 1) {
    long_char = va_arg(ap, wchar_t);
  } else {
    v_char = (unsigned char)va_arg(ap, int);
  }
  if (variable->len_l == 1) {
    wchar_t temp[2];
    temp[0] = long_char;
    temp[1] = '\0';
    int size_helper = sizeof(temp[0]);
    int add_size = wcstombs(array + (*top), temp, size_helper);
    if (variable->align_minus == 0 && variable->width > add_size) {
      for (int i = 0; i < (variable->width - add_size); i++) {
        array[*top] = ' ';
        *top += 1;
      }
    }
    add_size = wcstombs(array + (*top), temp, size_helper);
    *top += add_size;
    if (variable->align_minus == 1 && variable->width > add_size) {
      for (int i = 0; i < (variable->width - add_size); i++) {
        array[*top] = ' ';
        *top += 1;
      }
    }
  } else {
    if (variable->align_minus == 0 && variable->width > 1) {
      for (int i = 0; i < (variable->width - 1); i++) {
        array[*top] = ' ';
        *top += 1;
      }
    }
    array[*top] = v_char;
    *top += 1;
    if (variable->align_minus == 1 && variable->width > 1) {
      for (int i = 0; i < (variable->width - 1); i++) {
        array[*top] = ' ';
        *top += 1;
      }
    }
    array[*top] = '\0';
  }
}

void process_int(va_list ap, params *variable, char *array, int *top,
                 const char *gen_pointer) {
  long int v_int = 0;
  if (variable->star_width == 1) {
    variable->width = va_arg(ap, int);
  }
  if (variable->star_precision) {
    variable->precision_num = va_arg(ap, int);
  }
  if (variable->len_h == 1) {
    v_int = ((*gen_pointer) == 'u')
                ? (unsigned short int)va_arg(ap, unsigned int)
                : (short int)va_arg(ap, int);
  } else if (variable->len_l == 1) {
    v_int = ((*gen_pointer) == 'u') ? va_arg(ap, unsigned long int)
                                    : va_arg(ap, long int);
  } else if ((*gen_pointer) == 'u') {
    v_int = va_arg(ap, unsigned int);
  } else {
    v_int = va_arg(ap, int);
  }
  if ((*gen_pointer) == 'u') {
    variable->space_for_pos = 0;
    variable->show_sign = 0;
  }
  char *temp = s21_itoa(v_int);
  int temp_shift = 0;
  int sign = (v_int < 0) ? 1 : 0;
  if (v_int == 0 && variable->precision_num == 0) {
    array[*top] = '\0';
  } else {
    if (variable->precision_num == -1) variable->precision_num = 0;
    if (variable->precision_num > 0) {
      char *temp_ar = s21_itoa(v_int);
      int size_helper =
          (temp_ar[0] == '-') ? s21_strlen(temp_ar + 1) : s21_strlen(temp_ar);
      variable->precision_zero = (variable->precision_num - size_helper > 0)
                                     ? (variable->precision_num - size_helper)
                                     : 0;
      free(temp_ar);
    }
    if (v_int > 0 && variable->show_sign == 1 && variable->width == 0 &&
        variable->precision_zero == 0) {
      array[*top] = '+';
      *top += 1;
    }
    if (v_int >= 0 && variable->space_for_pos == 1 && variable->width == 0) {
      array[*top] = ' ';
      *top += 1;
    }
    int zero_flag = 0;
    if (variable->precision_zero) {
      if (variable->width > 0 && variable->align_minus == 0) {
        add_space_precision_zero(temp, array, top, variable);
      }
      zero_flag =
          add_precision_zero(&temp, array, top, variable, 0, &temp_shift);
      if (temp_shift) sign = 0;
    } else if (variable->direct_zero) {
      zero_flag = add_zero(&temp, array, top, (int)s21_strlen(temp), variable,
                           &temp_shift);
      if (temp_shift) sign = 0;
    } else if (variable->width > 0) {
      add_space(temp, array, top, (int)s21_strlen(temp), variable);
    }
    write_into_main_buf(temp, array, top, (int)s21_strlen(temp), zero_flag, 0,
                        sign);
  }
  if (variable->align_minus) {
    align_left(array, top, (int)s21_strlen(temp) + variable->precision_zero,
               variable->width, variable, temp);
  }
  array[*top] = '\0';
  free(temp - temp_shift);
}

int add_precision_zero(char **temp, char *main_buf, int *top, params *variable,
                       int flag_x, int *shift) {
  int count = 0;
  if ((variable->width == 0) || (variable->align_minus == 1)) {
    if (((*temp)[0] != '-') && (variable->space_for_pos == 1)) {
      main_buf[*top] = ' ';
      *top += 1;
    } else if (((*temp)[0] != '-') && (variable->show_sign == 1)) {
      main_buf[*top] = '+';
      *top += 1;
    }
  }
  if (variable->precision_zero > 0 && flag_x == 0) {
    if ((*temp)[0] == '-') {
      main_buf[*top] = '-';
      *top += 1;
      for (int i = 0; i < variable->precision_zero; i++) {
        main_buf[*top] = '0';
        *top += 1;
        count++;
      }
      (*temp) += 1;
      (*shift) += 1;
    } else {
      for (int i = 0; i < variable->precision_zero; i++) {
        main_buf[*top] = '0';
        *top += 1;
      }
    }
  }
  if (variable->precision_zero > 0 && flag_x == 1) {
    if (variable->hash_zero) {
      main_buf[*top] = '0';
      *top += 1;
      main_buf[*top] = 'x';
      *top += 1;
    }
    for (int i = 0; i < variable->precision_zero; i++) {
      main_buf[*top] = '0';
      *top += 1;
      count++;
    }
  }
  return count;
}

void write_into_main_buf(const char *temp, char *main_buf, int *top, int count,
                         int flag, int hex_flag, int sign) {
  int i = 0;
  if (flag) {
    if (hex_flag) {
      i = 2;
    } else if (sign) {
      i = 1;
    }
  }
  for (; i < count; i++) {
    main_buf[*top] = temp[i];
    *top += 1;
  }
  main_buf[*top] = '\0';
}

void align_left(char *main_buf, int *top, int len, int fill, params *variable,
                const char *temp) {
  if (variable->show_sign == 1 && temp[0] != '-') {
    len++;
  }
  if ((variable->space_for_pos == 1) && (temp[0] != '-')) {
    len++;
  }
  if (fill > len) {
    for (int i = 0; i < (fill - len); i++) {
      main_buf[*top] = ' ';
      *top += 1;
    }
    main_buf[*top] = '\0';
  }
}

int add_zero(char **temp, char *main_buf, int *top, int len, params *variable,
             int *shift) {
  int count = 0;
  if (((*temp)[0] != '-') && (variable->show_sign == 1)) {
    len++;
    if (variable->width > 0) {
      main_buf[*top] = '+';
      *top += 1;
    }
  }
  if (variable->width > len) {
    if ((*temp)[0] == '-') {
      main_buf[*top] = '-';
      *top += 1;
      for (int i = 0; i < (variable->width - len); i++) {
        main_buf[*top] = '0';
        *top += 1;
        count++;
      }
      (*temp) += 1;
      (*shift) += 1;
    } else {
      for (int i = 0; i < (variable->width - len); i++) {
        main_buf[*top] = '0';
        *top += 1;
      }
    }
  }
  return count;
}

void add_space_precision_zero(char *temp, char *main_buf, int *top,
                              params *variable) {
  int len = 0;
  if (variable->show_sign == 1 && temp[0] != '-') {
    len++;
  }
  len = variable->width - variable->precision_zero - s21_strlen(temp) - len;
  if (len > 0) {
    for (int i = 0; i < len; i++) {
      main_buf[*top] = ' ';
      *top += 1;
    }
    if ((temp[0] != '-') && (variable->show_sign == 1)) {
      main_buf[*top] = '+';
      *top += 1;
    }
  } else if ((temp[0] != '-') && (variable->space_for_pos == 1)) {
    main_buf[*top] = ' ';
    *top += 1;
  } else if ((temp[0] != '-') && (variable->show_sign == 1)) {
    main_buf[*top] = '+';
    *top += 1;
  }
}

void add_space(const char *temp, char *main_buf, int *top, int len,
               params *variable) {
  if (variable->align_minus == 0) {
    if ((temp[0] != '-') && (variable->show_sign == 1)) {
      len++;
      if (variable->width <= len) {
        main_buf[*top] = '+';
        *top += 1;
      }
    }
    if (variable->width > len) {
      if (temp[0] == '-') {
        for (int i = 0; i < (variable->width - len); i++) {
          main_buf[*top] = ' ';
          *top += 1;
        }
      } else {
        for (int i = 0; i < (variable->width - len); i++) {
          main_buf[*top] = ' ';
          *top += 1;
        }
        if (variable->show_sign == 1) {
          main_buf[*top] = '+';
          *top += 1;
        }
      }
    } else if ((temp[0] != '-') && (variable->space_for_pos == 1)) {
      main_buf[*top] = ' ';
      *top += 1;
    }
  } else {
    if ((temp[0] != '-') && (variable->space_for_pos == 1)) {
      main_buf[*top] = ' ';
      *top += 1;
    } else if ((temp[0] != '-') && (variable->show_sign == 1)) {
      main_buf[*top] = '+';
      *top += 1;
    }
  }
}

int parse_params(const char *str_pointer, params *variable, int *shift) {
  *shift += 1;
  int local_stop_flag = 0;
  while (!local_stop_flag) {
    str_pointer++;
    if (*str_pointer == '-') {
      variable->align_minus = 1;
    } else if (*str_pointer == '+') {
      variable->show_sign = 1;
    } else if (*str_pointer == ' ') {
      variable->space_for_pos = 1;
    } else if (*str_pointer == '#') {
      variable->hash_zero = 1;
    } else if (*str_pointer >= 48 && *str_pointer <= 57) {
      if (*str_pointer == '0') {
        if (variable->dot_check == 0) {
          if (variable->direct_zero == 0 && variable->width == 0) {
            variable->direct_zero = 1;
          } else {
            variable->width = variable->width * 10;
          }
        } else {
          variable->precision_num =
              (variable->precision_num > 0)
                  ? (variable->precision_num * 10 + (*str_pointer - '0'))
                  : ((*str_pointer) - '0');
        }
      } else {
        if (variable->dot_check == 1) {
          variable->precision_num =
              (variable->precision_num > 0)
                  ? (variable->precision_num * 10 + (*str_pointer - '0'))
                  : ((*str_pointer) - '0');
        } else {
          variable->width =
              (variable->width > 0)
                  ? ((variable->width * 10) + (*str_pointer - '0'))
                  : (*str_pointer) - '0';
        }
      }
    } else if ((*str_pointer) == '.' || (*str_pointer) == ',') {
      variable->dot_check = 1;
    } else if (*str_pointer == '*') {
      if (variable->dot_check == 1) {
        variable->star_precision = 1;
      } else {
        variable->star_width = 1;
      }
    } else if (*str_pointer == 'h') {
      variable->len_h = 1;
    } else if (*str_pointer == 'l') {
      variable->len_l = 1;
    } else if (*str_pointer == 'L') {
      variable->len_double = 1;
    } else if (s21_strchr(TOKENS, (int)(*str_pointer)) ||
               (*str_pointer == '%')) {
      break;
    } else {
      local_stop_flag = 1;
    }
    *shift += 1;
  }
  return local_stop_flag;
}

void init_struct(params *res) {
  res->align_minus = 0;
  res->show_sign = 0;
  res->space_for_pos = 0;
  res->hash_zero = 0;
  res->direct_zero = 0;
  res->width = 0;
  res->star_width = 0;
  res->star_precision = 0;
  res->dot_check = 0;
  res->precision_num = -1;
  res->precision_zero = 0;
  res->len_h = 0;
  res->len_l = 0;
  res->len_double = 0;
}

char *s21_itoa(long int num) {
  char *res = malloc(sizeof(char) * 40);
  if (!res) exit(0);
  char *reverse = malloc(sizeof(char) * 40);
  if (!reverse) {
    free(res);
    exit(0);
  }
  int count = 0;
  int sign = 0;
  if (num < 0) {
    sign = 1;
    num *= -1;
  }
  if (num == 0) {
    res[count++] = '0';
    res[count++] = '\0';
  } else {
    int i;
    while (num > 0) {
      long int next = num % 10;
      reverse[count++] = '0' + next;
      num /= 10;
    }
    if (sign) {
      reverse[count++] = '-';
    }
    for (i = 0; i < count; i++) {
      res[i] = reverse[count - i - 1];
    }
    res[i] = '\0';
  }
  free(reverse);
  return res;
}

void delete_zero(char *g_string, int *top) {
  while (g_string[(*top) - 1] == '0') {
    g_string[(*top) - 1] = '\0';
    (*top) -= 1;
  }
  if (g_string[(*top) - 1] == conflicting_char) {
    g_string[(*top) - 1] = '\0';
    (*top) -= 1;
  }
}

char *hex_to_string(unsigned long int num, int upper_flag, int pointer_flag,
                    int nil_flag) {
  char *res = malloc(sizeof(char) * 50);
  if (!res) exit(0);
  char *reverse = malloc(sizeof(char) * 50);
  if (!reverse) {
    free(res);
    exit(0);
  }
  if (num == 0) {
    if (nil_flag) {
      for (int i = 0; i < 3; i++) {
        res[i] = "0x0"[i];
      }
      res[3] = '\0';
    } else {
      res[0] = '0';
      res[1] = '\0';
    }
  } else {
    int count = 0;
    int i = 0;
    while (num > 0) {
      long int next = num % 16;
      if (next > 9) {
        if (upper_flag) {
          reverse[count++] = 'A' + next - 10;
        } else {
          reverse[count++] = 'a' + next - 10;
        }
      } else {
        reverse[count++] = next + '0';
      }
      num /= 16;
    }
    reverse[count] = '\0';
    char *first = s21_strstr(reverse, "ffffffff");
    char *second = s21_strstr(reverse, "FFFFFFFF");
    if (first != s21_NULL || second != s21_NULL) {
      count = count - 8;
    }
    if (pointer_flag) {
      if (upper_flag) {
        reverse[count++] = 'X';
        reverse[count++] = '0';
      } else {
        reverse[count++] = 'x';
        reverse[count++] = '0';
      }
    }
    for (; i < count; i++) {
      res[i] = reverse[count - i - 1];
    }
    res[i] = '\0';
  }
  free(reverse);
  return res;
}

char *float_to_string(long double num, int g_flag, params *variable) {
  char *res = malloc(sizeof(char) * 50);
  if (!res) exit(0);
  char *reverse = s21_NULL;
  int top = 0;
  int loc_precision = variable->precision_num;
  int sign_flag = 0;

  if (num < 0) {
    res[top] = '-';
    num *= -1;
    top++;
    sign_flag = 1;
  }
  if (num != 0 && log10(num) >= 0) {
    reverse = s21_itoa((long int)num);
    for (int j = 0; j < (int)s21_strlen(reverse); j++) {
      res[top] = reverse[j];
      top++;
    }
    free(reverse);
  } else {
    res[top] = '0';
    top++;
  }
  res[top] = conflicting_char;
  top++;
  int fraction = check_fraction(&top, variable, num);
  long double int_part;
  long double frac_part = modfl(num, &int_part);
  if (fraction == 1) {
    int indicator = 0;
    long double next;
    for (int k = 0; k < (loc_precision + 1); k++) {
      frac_part *= 10;
      frac_part = modfl(frac_part, &next);
      res[top] = (int)next + '0';
      top++;
    }
    if (res[top - 1] >= 53) {
      res[top - 2] = ((res[top - 2] - '0') + 1) % 10 + '0';
      indicator++;
    }
    res[top - 1] = '\0';
    top--;
    if (indicator && (res[top - 1] == '0')) {
      int helper;
      int reminder = 1;
      for (int i = top - 2; i >= sign_flag; i--) {
        if (res[i] == '.' || res[i] == ',') {
          continue;
        }
        helper = reminder + res[i] - '0';
        res[i] = (helper % 10) + '0';
        reminder = helper / 10;
      }
    }
  } else {
    if ((long long int)round(num) - (long int)int_part > 0) {
      int helper;
      int reminder = 0;
      helper = reminder + res[top - 1] - '0';
      res[top - 1] = ((helper + 1) % 10) + '0';
      reminder = (helper + 1) / 10;
      for (int i = top - 2; i >= sign_flag; i--) {
        helper = reminder + res[i] - '0';
        res[i] = (helper % 10) + '0';
        reminder = helper / 10;
      }
    }
  }
  if (g_flag == 1 && variable->hash_zero == 0) {
    delete_zero(res, &top);
  }

  res[top] = '\0';
  top++;
  return res;
}

char *exp_to_string(long double v_e, const char *exp_letter, int g_flag,
                    params *variable) {
  char *res = malloc(sizeof(char) * 50);
  if (!res) exit(0);
  int top = 0;
  char exp_sign = '+';
  int loc_precision = variable->precision_num;
  char letter = (*exp_letter == 'E' || *exp_letter == 'G') ? 'E' : 'e';
  int main_sign = 0;

  if (v_e < 0) {
    res[top] = '-';
    v_e *= -1;
    top++;
    main_sign = 1;
  }
  int v_log = 0;
  if (v_e > 0) {
    v_log = find_exp(v_e);
  }
  if (v_e > 0 && v_e < 1) {
    exp_sign = '-';
  }
  long double num_to_save = (v_e / pow(10, v_log));
  res[top] = '0' + (int)num_to_save;
  top++;
  res[top] = conflicting_char;
  top++;
  long double int_part;
  long double frac_part = modfl(num_to_save, &int_part);
  int fraction = check_fraction(&top, variable, num_to_save);
  if (fraction == 1) {
    int indicator = 0;
    long double next;
    for (int i = 0; i < loc_precision + 1; i++) {
      frac_part *= 10;
      frac_part = modfl(frac_part, &next);
      res[top] = (int)next + '0';
      top++;
    }
    if (res[top - 1] >= 53) {
      res[top - 2] = ((res[top - 2] - '0') + 1) % 10 + '0';
      indicator++;
    }
    res[top - 1] = '\0';
    top--;
    if (indicator && (res[top - 1] == '0')) {
      int helper;
      int reminder = 1;
      for (int i = top - 2; i >= main_sign; i--) {
        if (res[i] == ',' || res[i] == '.') {
          continue;
        }
        helper = reminder + res[i] - '0';
        res[i] = (helper % 10) + '0';
        reminder = helper / 10;
      }
    }
    if (g_flag == 1 && variable->hash_zero == 0) {
      delete_zero(res, &top);
    }
  } else {
    if ((long long int)round(num_to_save) - (long int)int_part > 0) {
      int helper2 = res[0] - '0';
      res[0] = ((helper2 + 1) % 10) + '0';
    }
  }
  res[top] = letter;
  top++;
  res[top] = exp_sign;
  top++;
  if (v_log < 10 && v_log > -10) {
    res[top] = '0';
    top++;
  }
  char *exp_string = s21_itoa(v_log);
  int i = (v_log >= 0) ? 0 : 1;
  for (; i < (int)s21_strlen(exp_string); i++) {
    res[top] = exp_string[i];
    top++;
  }
  free(exp_string);
  res[top] = '\0';
  return res;
}

int check_fraction(int *top, params *variable, long double num) {
  int total;
  long int check = (long int)num;
  if ((num - check) == 0) {
    if (variable->precision_num == 0 && variable->dot_check == 1 &&
        variable->hash_zero == 1) {
      total = 0;
    } else if (variable->precision_num == 0 && variable->dot_check == 1 &&
               variable->hash_zero == 0) {
      total = 0;
      *top -= 1;
    } else {
      total = 1;
    }
  } else if (variable->dot_check == 1 && variable->precision_num == 0) {
    if (variable->hash_zero == 0) {
      total = 0;
      *top -= 1;
    } else {
      total = 0;
    }
  } else {
    total = 1;
  }
  return total;
}

int check_precision(params *variable, int expo) {
  int res = 2;
  if (variable->precision_num == 0) {
    if (expo < -4 || expo >= 6) {
      res = 1;
    }
  } else if (variable->precision_num > 0) {
    if (expo < -4 || expo >= variable->precision_num) {
      res = 1;
    }
  }
  return res;
}