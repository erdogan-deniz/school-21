#include "s21_grep.h"

// Функция, которая проверяет, можно ли открыть данный на вход файл.
bool open_file(FILE **ptr, char *filepath, GrepArgs grepArgs) {
  *ptr = fopen(filepath, "r");

  if (*ptr == NULL) {
    if (!grepArgs.s)
      fprintf(stderr, "./s21_grep: %s: No such file or directory\n", filepath);
    return true;
  }

  return false;
}

// Функция очистки массива с паттернами и массива с файлами
void free_array(char **arr, int len) {
  for (int i = 0; i < len; i++) {
    free(arr[i]);
  }

  free(arr);
}

// Сравнение паттерна со строкой, с помощью регулярных выражений
// и дополнительных флагов.
int match_grep(char *template, char line[1096], GrepArgs grepArgs) {
  int value;

  regfree(&regex);

  grepArgs.i ? regcomp(&regex, template, REG_EXTENDED | REG_ICASE)
             : regcomp(&regex, template, REG_EXTENDED);

  value = regexec(&regex, line, 0, NULL, 0);

  return value;
}

// Функция-опция флага -с, которая считает количество строк в файле, где
// произошло совпадение с паттерном.
void c_option(char *filepath, char **template_arr, char line[1096], FILE *ptr,
              GrepArgs grepArgs) {
  int line_count = 0;
  int value = 1;

  while (fgets(line, 1096, ptr) != NULL) {
    for (int i = 0; i < grepArgs.templates_len; i++) {
      value = match_grep(template_arr[i], line, grepArgs);
      if (!value) break;
    }

    if (grepArgs.v && value)
      line_count++;
    else if (!grepArgs.v && !value)
      line_count++;
  }
  fseek(ptr, 0, SEEK_SET);

  grepArgs.filepaths_len == 1 || grepArgs.h
      ? printf("%d\n", line_count)
      : printf("%s:%d\n", filepath, line_count);
}

void o_option(char line[1096], char *template, char *filepath,
              GrepArgs grepArgs, int line_num, int *last_line_num) {
  regmatch_t pmatch[1];
  regoff_t len;

  regfree(&regex);

  grepArgs.i ? regcomp(&regex, template, REG_NEWLINE | REG_ICASE)
             : regcomp(&regex, template, REG_NEWLINE);

  for (int i = 0;; i++) {
    if (regexec(&regex, line, ARRAY_SIZE(pmatch), pmatch, 0)) break;

    len = pmatch[0].rm_eo - pmatch[0].rm_so;

    if (grepArgs.n && *last_line_num != line_num) {
      (grepArgs.filepaths_len == 1 || grepArgs.h)
          ? printf("%d:%.*s\n", line_num, (int)len, line + pmatch[0].rm_so)
          : printf("%s:%d:%.*s\n", filepath, line_num, (int)len,
                   line + pmatch[0].rm_so);
    } else if (!grepArgs.n && *last_line_num != line_num) {
      (grepArgs.filepaths_len == 1 || grepArgs.h)
          ? printf("%.*s\n", (int)len, line + pmatch[0].rm_so)
          : printf("%s:%.*s\n", filepath, (int)len, line + pmatch[0].rm_so);
    } else {
      printf("%.*s\n", (int)len, line + pmatch[0].rm_so);
    }

    line += pmatch[0].rm_eo;
    *last_line_num = line_num;
  }
}

// Функция обработки сочетания флагов -c -l, показывающего,
// есть ли совпадения паттерна в файле.
void cl_option(char *filepath, char **template_arr, FILE *ptr,
               GrepArgs grepArgs) {
  char line[1096] = {0};
  char line_cpy[1096] = {0};
  int value = 1;
  bool found = false, not_found = false;

  while (fgets(line, 1096, ptr) != NULL) {
    strcpy(line_cpy, line);
    for (int i = 0; i < grepArgs.templates_len; i++) {
      value = match_grep(template_arr[i], line, grepArgs);
      if (!value) break;
    }

    if (!value && !grepArgs.v)
      found = true;
    else if (value && grepArgs.v)
      not_found = true;
  }

  if ((grepArgs.v && not_found) || found) {
    (grepArgs.filepaths_len == 1 || grepArgs.h)
        ? printf("%d\n%s\n", 1, filepath)
        : printf("%s:%d\n%s\n", filepath, 1, filepath);
  } else {
    (grepArgs.filepaths_len == 1 || grepArgs.h)
        ? printf("%d\n", 0)
        : printf("%s:%d\n", filepath, 0);
  }
}

// Главная функция-обработчик, которая вызывается только при наличии
// флага -v в списке флагов.
void grep_utility_v(char *filepath, char **template_arr, FILE *ptr,
                    GrepArgs grepArgs) {
  char line[1096] = {0};
  int line_num = 1;
  int value = -1;

  if (grepArgs.l && grepArgs.c) {
    cl_option(filepath, template_arr, ptr, grepArgs);
  } else if (grepArgs.c) {
    c_option(filepath, template_arr, line, ptr, grepArgs);
  } else {
    while (fgets(line, 1096, ptr) != NULL) {
      for (int i = 0; i < grepArgs.templates_len; i++) {
        value = match_grep(template_arr[i], line, grepArgs);
        if (!value) break;
      }

      if (value && grepArgs.l) {
        printf("%s\n", filepath);
        break;
      } else if (grepArgs.n && value) {
        grepArgs.filepaths_len == 1 || grepArgs.h
            ? printf("%d:%s", line_num, line)
            : printf("%s:%d:%s", filepath, line_num, line);
      } else if (value || (grepArgs.o && value)) {
        grepArgs.filepaths_len == 1 || grepArgs.h
            ? printf("%s", line)
            : printf("%s:%s", filepath, line);
      }
      line_num++;
    }
    if (value == 1 && !grepArgs.l && line[strlen(line) - 1] != '\n')
      printf("\n");
  }
}

// Главная функция-обработчик, которая вызывается только тогда, когда
// флага -v нет в списке флагов.
void grep_utility(char *filepath, char **template_arr, FILE *ptr,
                  GrepArgs grepArgs) {
  char line[1096] = {0};
  int line_num = 1;
  int value = 1;
  int last_line_num = 0;

  if (grepArgs.c && grepArgs.l) {
    cl_option(filepath, template_arr, ptr, grepArgs);
  } else if (grepArgs.c) {
    c_option(filepath, template_arr, line, ptr, grepArgs);
  } else {
    while (fgets(line, 1096, ptr) != NULL) {
      for (int i = 0; i < grepArgs.templates_len; i++) {
        value = match_grep(template_arr[i], line, grepArgs);
        if (!value) break;
      }

      if (!value && grepArgs.l) {
        printf("%s\n", filepath);
        break;
      } else if (grepArgs.o) {
        for (int i = 0; i < grepArgs.templates_len; i++)
          o_option(line, template_arr[i], filepath, grepArgs, line_num,
                   &last_line_num);
      } else if (grepArgs.n && !value) {
        grepArgs.filepaths_len == 1 || grepArgs.h
            ? printf("%d:%s", line_num, line)
            : printf("%s:%d:%s", filepath, line_num, line);
      } else if (!value) {
        grepArgs.filepaths_len == 1 || grepArgs.h
            ? printf("%s", line)
            : printf("%s:%s", filepath, line);
      }
      line_num++;
    }
    if (!value && !grepArgs.l && (grepArgs.n || grepArgs.h) && !grepArgs.o &&
        line[strlen(line) - 1] != '\n')
      printf("\n");
  }
}

void filepaths_handler(char **template_arr, char **filepath_arr,
                       GrepArgs grepArgs) {
  FILE *ptr = NULL;

  for (int i = 0; i < grepArgs.filepaths_len; i++) {
    if (!open_file(&ptr, filepath_arr[i], grepArgs)) {
      if (grepArgs.v) {
        grep_utility_v(filepath_arr[i], template_arr, ptr, grepArgs);
      } else {
        grep_utility(filepath_arr[i], template_arr, ptr, grepArgs);
      }
      fclose(ptr);
    }
  }
}

// Функция аллокации памяти под паттерн, в случае, когда пользователем
// не был указан флаг -е или флаг -f. В таком случае за паттерн считается первое
// в списке аргументов слово.
char **template_allocator(int argc, char *argv[], char **template_arr,
                          GrepArgs *grepArgs) {
  int t = 0;

  for (int i = 1; i < argc; i++)
    if (*argv[i] != '-') {
      template_arr[t] = malloc((strlen(argv[i]) + 1) * sizeof(char));
      strcpy(template_arr[t], argv[i]);
      grepArgs->template_idx = i;
      grepArgs->templates_len++;

      break;
    }

  return template_arr;
}

// Функция аллокации памяти под все файлы, в случае, когда пользователем
// не был указан флаг -е или флаг -f. В таком случае за файл считается все
// подряд идущие агрументы, начиная со второго.
char **filepath_allocator(int argc, char *argv[], char **filepath_arr,
                          GrepArgs *grepArgs) {
  int f = 0;

  for (int i = grepArgs->template_idx + 1; i < argc; i++)
    if (*argv[i] != '-') {
      filepath_arr[f] = malloc((strlen(argv[i]) + 1) * sizeof(char));
      strcpy(filepath_arr[f], argv[i]);
      grepArgs->filepaths_len++;
      f++;

      filepath_arr = realloc(filepath_arr, (f + 1) * sizeof(char *));
    }

  return filepath_arr;
}

// Фунция обработки файла, следующего за флагом -f, которая считывает
// по порядку строки и записывает их в массив всех паттернов.
void parse_f_filepath(char *f_filepath, char ***template_arr,
                      GrepArgs *grepArgs, int *i) {
  FILE *ptr = NULL;

  if (!open_file(&ptr, f_filepath, *grepArgs)) {
    char line[1096] = {0};

    while (fgets(line, 1096, ptr) != NULL) {
      if (*line != '\n') line[strcspn(line, "\n")] = 0;

      (*template_arr)[*i] = malloc((strlen(line) + 1) * sizeof(char));
      strcpy((*template_arr)[*i], line);
      grepArgs->templates_len++;
      (void)(*i)++;

      *template_arr = realloc(*template_arr, (*i + 1) * sizeof(char *));
    }
  }

  fclose(ptr);
}

// Фукнция обработки флагов.
bool parse_flags(int argc, char *argv[], char ***template_arr,
                 GrepArgs *grepArgs) {
  char ch;
  int i = 0;

  while ((ch = getopt_long(argc, argv, "e:ivclnhsf:o", long_options, NULL)) !=
         -1) {
    switch (ch) {
      case 'e':
        (*template_arr)[i] = malloc((strlen(optarg) + 1) * sizeof(char));
        strcpy((*template_arr)[i], optarg);
        grepArgs->templates_len++;
        grepArgs->e = true;
        i++;

        *template_arr = realloc(*template_arr, (i + 1) * sizeof(char *));
        break;
      case 'i':
        grepArgs->i = true;
        break;
      case 'v':
        grepArgs->v = true;
        break;
      case 'c':
        grepArgs->c = true;
        break;
      case 'l':
        grepArgs->l = true;
        break;
      case 'n':
        grepArgs->n = true;
        break;
      case 'h':
        grepArgs->h = true;
        break;
      case 's':
        grepArgs->s = true;
        break;
      case 'f':
        parse_f_filepath(optarg, template_arr, grepArgs, &i);
        grepArgs->f = true;
        break;
      case 'o':
        grepArgs->o = true;
        break;
      default:
        return false;
        break;
    }
  }

  return true;
}

// Парсинг аргументов, флагов, заполнение массивов паттернами и файлами,
// а также очищение памяти после использования массивов.
void parse_args(int argc, char *argv[]) {
  GrepArgs grepArgs = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

  char **template_arr = malloc(sizeof(char *));
  char **filepath_arr = malloc(sizeof(char *));

  parse_flags(argc, argv, &template_arr, &grepArgs);

  if (grepArgs.e || grepArgs.f) {
    int f = 0;
    for (int i = optind; i < argc; i++) {
      filepath_arr[f] = malloc((strlen(argv[i]) + 1) * sizeof(char));
      strcpy(filepath_arr[f], argv[i]);
      grepArgs.filepaths_len++;
      f++;

      char **tmp = realloc(filepath_arr, (f + 1) * sizeof(char *));
      if (tmp != NULL) filepath_arr = tmp;
    }
  } else {
    template_arr = template_allocator(argc, argv, template_arr, &grepArgs);
    filepath_arr = filepath_allocator(argc, argv, filepath_arr, &grepArgs);
  }

  filepaths_handler(template_arr, filepath_arr, grepArgs);

  free_array(template_arr, grepArgs.templates_len);
  free_array(filepath_arr, grepArgs.filepaths_len);
}

// Точка входа в программу.
int main(int argc, char *argv[]) {
  parse_args(argc, argv);

  regfree(&regex);

  return 0;
}
