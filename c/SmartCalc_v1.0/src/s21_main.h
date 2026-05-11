/**
 * @file s21_main.h
 * @brief Umbrella include — every public C header in `SmartCalc_v1.0`.
 *
 * Pulling this single header is enough to use every internal module
 * (parser, calculator, list / stack containers, transform helpers,
 * validation, financial extras). The public-facing entry point is
 * still `s21_calculator()` from @ref s21_calculator.h.
 */

#ifndef SRC_S21_MAIN_H_
#define SRC_S21_MAIN_H_

#include "additional/s21_additional.h"
#include "bonus/s21_bonus.h"
#include "calculate/s21_calculate.h"
#include "list/s21_list.h"
#include "parser/s21_parser.h"
#include "s21_calculator.h"
#include "stack/s21_stack.h"
#include "transform/s21_transform.h"
#include "validation/s21_validation.h"

#endif  // SRC_S21_MAIN_H_
