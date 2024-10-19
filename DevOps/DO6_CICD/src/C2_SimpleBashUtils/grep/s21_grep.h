#ifndef SRC_GREP_S21_GREP_H_
#define SRC_GREP_S21_GREP_H_

#include <getopt.h>
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define ARRAY_SIZE(arr) (sizeof((arr)) / sizeof((arr)[0]))

regex_t regex;

typedef struct {
  bool e;
  bool i;
  bool v;
  bool c;
  bool l;
  bool n;
  bool h;
  bool s;
  bool f;
  bool o;
  int templates_len;
  int template_idx;
  int filepaths_len;
  int filepath_idx;
} GrepArgs;

static struct option long_options[] = {{"e", required_argument, NULL, 'e'},
                                       {"f", required_argument, NULL, 'f'},
                                       {NULL, 0, NULL, 0}};

#endif  // SRC_GREP_S21_GREP_H_
