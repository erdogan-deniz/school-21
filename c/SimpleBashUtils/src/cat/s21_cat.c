#include "s21_cat.h"

/*

-b (GNU: --number-nonblank) -- нумерует только непустые строки
-e предполагает и -v (GNU only: -E то же самое, но без применения -v) -- также
отображает символы конца строки как $ -n (GNU: --number) -- нумерует все
выходные строки -s (GNU: --squeeze-blank) -- сжимает несколько смежных пустых
строк -t предполагает и -v (GNU: -T то же самое, но без применения -v) -- также
отображает табы как ^I

*/

int handle_flags(int argc, char **argv, uint8_t *flags) {
  const char *short_options = "+vbeEnstT";
  const struct option long_options[] = {
      {"number-nonblank", no_argument, NULL, 'B'},
      {"number", no_argument, NULL, 'N'},
      {"squeeze-blank", no_argument, NULL, 'S'},
      {NULL, 0, NULL, 0}};

  int res = 0, option_index;
  while ((res = getopt_long(argc, argv, short_options, long_options,
                            &option_index)) != -1) {
    switch (res) {
      case 'v':
        *flags |= VMASK;
        break;
      case 'b':
      case 'B':
        *flags |= BMASK;
        break;
      case 'e':
      case 'E':
        *flags |= EMASK;
        break;
      case 'n':
      case 'N':
        *flags |= NMASK;
        break;
      case 's':
      case 'S':
        *flags |= SMASK;
        break;
      case 't':
      case 'T':
        *flags |= TMASK;
        break;
      case '?':
        USAGE(USAGE_TEXT, res);
        break;
    }
  }

  return optind;
}

int get_next_line(char *line, size_t size, FILE *file) {
  size_t idx = 0;
  int c = 0, flag = 1;
  while (flag && (c = fgetc(file)) != EOF && idx < size) {
    line[idx] = c;
    idx++;
    if (c == '\n') flag = 0;
  }
  line[idx] = '\0';
  return idx;
}

void fabric_read(const uint8_t flags, FILE *file) {
  char line[MAX_LINE_SIZE] = {0};
  int line_cnt = 1, empty_neib = 0;
  int line_len;
  // (line_len = get_next_line(line, MAX_LINE_SIZE, file))
  while ((line_len = get_next_line(line, MAX_LINE_SIZE, file))) {
    int empty = line_empty(line);
    empty_neib = (empty) ? empty_neib + 1 : 0;
    if ((flags & SMASK) == 0 || empty_neib <= 1)
      line_operation(flags, &line_cnt, line, line_len);
  }
}

void line_operation(const uint8_t flags, int *line_cnt, char *line,
                    int line_size) {
  char *tmp = line;
  (void)line_size;
  if (flags & BMASK) {
    if (!line_empty(line)) printf("%6d\t", (*line_cnt)++);
  } else if (flags & NMASK) {
    printf("%6d\t", (*line_cnt)++);
  }
  for (int i = 0; i < line_size - 1; i++) {
    if (flags & TMASK || flags & VMASK || flags & EMASK) {
      if (*tmp == '\t' && flags & TMASK)
        printf("^I");
      else if (*tmp < 32 && *tmp != '\t' && *tmp != '\n')
        printf("^%c", *tmp + 64);
      else if (*tmp == 0x7f)
        printf("^?");
      else
        printf("%c", *tmp);
    } else
      printf("%c", *tmp);
    tmp++;
  }
  if (flags & EMASK && *tmp == '\n') printf("$");
  putchar(*tmp);
}

int line_empty(char *line) { return *line == '\n' || *line == '\r'; }

int main(int argc, char **argv) {
  if (argc == 1) {
    STDERR_STR(CAT_PRFX "Input from STDIN unsupported\n");
  } else {
    uint8_t flags = 0x0;
    FILE *file;
    int filename_idx = handle_flags(argc, argv, &flags);

    for (; filename_idx < argc; filename_idx++) {
      const char *filename = argv[filename_idx];
      if ((file = fopen(filename, "r")) != NULL) {
        fabric_read(flags, file);
        fclose(file);
      } else {
        STDERR(CAT_PRFX "%s: No such file or directory\n", filename);
      }
    }
  }

  return 0;
}
