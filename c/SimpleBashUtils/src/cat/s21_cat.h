/**
 * @file s21_cat.h
 * @brief Reimplementation of POSIX `cat(1)` — interface for flag
 *        handling, the read fabric, and per-line transforms.
 *
 * Flags are packed into a single `uint8_t` via the `*MASK` macros
 * below — bit 0 is reserved, bits 1-6 map to `-t`, `-s`, `-n`, `-e`,
 * `-b`, `-v` respectively. The fabric dispatches on this mask to the
 * appropriate per-line transform.
 */

#ifndef _CAT_MAIN_H
#define _CAT_MAIN_H

#include <ctype.h>
#include <getopt.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_LINE_SIZE 4096  ///< Upper bound for a single input line.

#define CAT_PRFX "cat: "    ///< Stderr prefix used by error messages.

#define VMASK (1 << 6)  ///< `-v` — display non-printing characters.
#define BMASK (1 << 5)  ///< `-b` — number non-empty output lines.
#define EMASK (1 << 4)  ///< `-e` — display `$` at end of each line (+ `-v`).
#define NMASK (1 << 3)  ///< `-n` — number every output line.
#define SMASK (1 << 2)  ///< `-s` — squeeze consecutive empty lines.
#define TMASK (1 << 1)  ///< `-t` — display tabs as `^I` (+ `-v`).

/** @brief Emit a literal string to stderr — convenience wrapper. */
#define STDERR_STR(msg) STDERR("%s", msg);

/** @brief Emit a formatted error message to stderr. */
#define STDERR(fmt, msg) \
  { fprintf(stderr, fmt, msg); }

/** @brief Emit a usage message — currently identical to @ref STDERR. */
#define USAGE(fmt, option) \
  { STDERR(fmt, option); }

#define USAGE_TEXT              \
  "cat: illegal option -- %c\n" \
  "usage: cat [-benstuv] [file ...]\n"

/**
 * @brief Parse argv into @p flags using `getopt_long`.
 * @return Index of the first non-flag argument (the first file path).
 */
int handle_flags(int argc, char **argv, uint8_t *flags);

/** @brief Read one line into @p line, returns characters read (0 on EOF). */
int get_next_line(char *line, size_t size, FILE *file);

/** @brief Read @p file line by line and apply the per-line transform
 *         dictated by @p flags. */
void fabric_read(const uint8_t flags, FILE *file);

/** @brief Apply numbering, tab/end-line markup, and `-v` rendering to
 *         a single @p line based on @p flags. */
void line_operation(const uint8_t flags, int *line_cnt, char *line,
                    int line_size);

/** @brief Returns nonzero iff @p line is empty (only `\n` or zero len). */
int line_empty(char *line);

#endif  // !_CAT_MAIN_H
