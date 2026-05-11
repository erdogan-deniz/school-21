/**
 * @file s21_bonus.h
 * @brief Bonus credit / deposit schedule — doubly-linked list of
 *        per-month @ref s21_payments nodes.
 *
 * The list is the result of differentiated-payment or compound-
 * interest deposit modelling: each node represents one month with
 * its principal, interest, and serial number.
 */

#ifndef SRC_BONUS_S21_BONUS_H_
#define SRC_BONUS_S21_BONUS_H_

/**
 * @brief Per-month entry in a credit / deposit schedule.
 */
typedef struct s21_payments {
  long double debt;             ///< Remaining principal at month end.
  long double percents;         ///< Interest accrued this month.
  int month_number;             ///< 1-based month index in the schedule.
  struct s21_payments* next;    ///< Next month (NULL at the tail).
  struct s21_payments* prev;    ///< Previous month (NULL at the head).
} s21_payments;

#define empty 0

#include "../stack/s21_stack.h"

/** @brief Zero-fill one node — does not free. */
s21_payments* s21_clear_payment(s21_payments* payment);
/** @brief Allocate one fresh payment node, linked at the tail. */
s21_payments* s21_create_payment(s21_payments* payments);
/** @brief Allocate the head sentinel of a fresh payment list. */
s21_payments* s21_create_payments(s21_payments* payments);
/**
 * @brief Compute the @p month_number row of a deposit schedule.
 * @param sum Initial deposit principal.
 * @param month_number 1-based month index to compute.
 * @param payment Node to fill (in-place).
 */
s21_payments* s21_fill_deposit(long double sum, int month_number,
                               s21_payments* payment);
/**
 * @brief Compute the @p month_number row of a differentiated credit.
 * @param sum Initial loan principal.
 * @param months Total loan duration.
 * @param month_number 1-based month index to compute.
 * @param interest_rate Annual rate, e.g. `0.075` for 7.5 %.
 */
s21_payments* s21_fill_payment(long double sum, int months, int month_number,
                               long double interest_rate,
                               s21_payments* payment);
/** @brief Free the entire payments list. Returns NULL. */
s21_payments* s21_free_payments(s21_payments* payments);
/** @brief Sum the principal column over rows [from, to]. */
long double s21_get_action_amount(int from, int to, s21_payments* payments);
/** @brief Total amount paid this month (debt + percents). */
long double s21_get_payment_amount(s21_payments* payment);
/** @brief Grand total of every payment in the schedule. */
long double s21_get_total_amount(s21_payments* payments);
/** @brief Total principal repaid across the schedule. */
long double s21_get_total_debt(s21_payments* payments);
/** @brief Convert an annual rate to a monthly ratio. */
long double s21_interest_rate_to_month_ratio(long double interest_rate);
/** @brief Drop the head node and return the new head. */
s21_payments* s21_pop_payment(s21_payments* payment);
/** @brief Append a deposit row at the tail. */
s21_payments* s21_push_deposit(long double sum, int month,
                               s21_payments* payments);
/** @brief Append a credit row at the tail. */
s21_payments* s21_push_payment(long double sum, int months, int month,
                               long double interest_rate,
                               s21_payments* payments);

#endif  // SRC_BONUS_S21_BONUS_H_
