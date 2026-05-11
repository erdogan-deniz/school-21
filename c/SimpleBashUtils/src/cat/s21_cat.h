#ifndef _CAT_MAIN_H
#define _CAT_MAIN_H

#include <ctype.h>
#include <getopt.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_LINE_SIZE 4096

#define CAT_PRFX "cat: "

#define VMASK (1 << 6)
#define BMASK (1 << 5)
#define EMASK (1 << 4)
#define NMASK (1 << 3)
#define SMASK (1 << 2)
#define TMASK (1 << 1)

#define STDERR_STR(msg) STDERR("%s", msg);

#define STDERR(fmt, msg) \
  { fprintf(stderr, fmt, msg); }

#define USAGE(fmt, option) \
  { STDERR(fmt, option); }

#define USAGE_TEXT              \
  "cat: illegal option -- %c\n" \
  "usage: cat [-benstuv] [file ...]\n"

int handle_flags(int argc, char **argv, uint8_t *flags);

int get_next_line(char *line, size_t size, FILE *file);

void fabric_read(const uint8_t flags, FILE *file);

void line_operation(const uint8_t flags, int *line_cnt, char *line,
                    int line_size);

int line_empty(char *line);

#endif  // !_CAT_MAIN_H
