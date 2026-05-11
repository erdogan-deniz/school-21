/**
 * @file s21_calculator.h
 * @brief Public C API of `SmartCalc_v1.0` — the single entry point
 *        @ref s21_calculator that ties together parsing, validation,
 *        and RPN evaluation.
 *
 * The library is built as a shared object (`*.so` / `*.dll`) and
 * consumed by the Qt front end via dynamic loading. Windows builds
 * use `__declspec(dllexport)`; ELF / Mach-O builds use default
 * visibility.
 */

#ifndef SRC_S21_CALCULATOR_H_
#define SRC_S21_CALCULATOR_H_

#define true 1   ///< Boolean literal — C99-compatible.
#define false 0  ///< Boolean literal — C99-compatible.

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#define S21_API __declspec(dllexport)  ///< Windows DLL export decoration.
#else
#define S21_API                        ///< Default visibility on Unix.
#endif

/**
 * @brief Evaluate an infix arithmetic expression with optional `x`.
 * @param string Null-terminated infix expression
 *               (e.g. `"sin(x) + 2"`).
 * @param x      Pointer to the value substituted for every `x`
 *               literal in @p string. Pass `NULL` if the expression
 *               contains no `x`.
 * @return The evaluated value, or `NAN` on parse / domain error
 *         (caller can test with `isnan`).
 */
S21_API long double s21_calculator(char* string, long double* x);

#endif  // SRC_S21_CALCULATOR_H_
