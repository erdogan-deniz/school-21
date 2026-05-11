/**
 * @file s21_grep.h
 * @brief Reimplementation of POSIX `grep(1)` — flag struct, regex
 *        handle, and `getopt_long` table.
 *
 * Each command-line flag has a dedicated `bool` in @ref GrepArgs so
 * the matching loop can branch on intent rather than a packed mask
 * (cf. `s21_cat`'s `uint8_t` flags). The compiled regex lives in the
 * file-scope @ref regex variable — single-shot per invocation.
 */

#ifndef SRC_GREP_S21_GREP_H_
#define SRC_GREP_S21_GREP_H_

#include <getopt.h>
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/** @brief Number of elements in a fixed-size array. */
#define ARRAY_SIZE(arr) (sizeof((arr)) / sizeof((arr)[0]))

/** @brief Compiled POSIX regex shared across the whole `grep` run. */
regex_t regex;

/**
 * @brief State bag for the parsed command-line flags.
 *
 * Each boolean corresponds to one short option; the `_len` / `_idx`
 * fields track the position-only arguments (extra `-e patterns` and
 * the trailing file paths) after `getopt` finishes.
 */
typedef struct {
  bool e;  ///< `-e PATTERN` — extra patterns supplied separately.
  bool i;  ///< `-i` — case-insensitive match.
  bool v;  ///< `-v` — invert match.
  bool c;  ///< `-c` — print only the count of matches.
  bool l;  ///< `-l` — print only file names with matches.
  bool n;  ///< `-n` — prefix each match with its line number.
  bool h;  ///< `-h` — suppress file-name prefix in output.
  bool s;  ///< `-s` — suppress errors about missing / unreadable files.
  bool f;  ///< `-f FILE` — read patterns from a file (one per line).
  bool o;  ///< `-o` — print only the matched (non-empty) part.
  int templates_len;   ///< Total number of patterns to match against.
  int template_idx;    ///< Current pattern index during the match loop.
  int filepaths_len;   ///< Number of files passed on the command line.
  int filepath_idx;    ///< Current file index during iteration.
} GrepArgs;

/** @brief `getopt_long` table for the long-option-spelt `-e` and `-f` flags. */
static struct option long_options[] = {{"e", required_argument, NULL, 'e'},
                                       {"f", required_argument, NULL, 'f'},
                                       {NULL, 0, NULL, 0}};

#endif  // SRC_GREP_S21_GREP_H_
