/**
 * @file s21_finance.h
 * @brief Flat-API loan and deposit calculators — alternative to the
 *        list-based @ref s21_bonus module.
 *
 * The functions return scalar aggregates (monthly payment,
 * overpayment, total) via output parameters instead of a per-month
 * schedule. Suitable for the simpler "result-only" UI panels.
 */

#ifndef SRC_FINANCE_S21_FINANCE_H_
#define SRC_FINANCE_S21_FINANCE_H_

/**
 * @brief Annuity (fixed monthly payment) loan calculator.
 * @param principal     Loan principal.
 * @param months        Loan duration.
 * @param annual_rate   Annual rate (e.g. `0.075` for 7.5 %).
 * @param[out] monthly_payment  Constant monthly instalment.
 * @param[out] overpayment      Total interest paid.
 * @param[out] total            principal + overpayment.
 * @return 1 on success, 0 on invalid input.
 */
int s21_loan_annuity(double principal, int months, double annual_rate,
                     double *monthly_payment, double *overpayment,
                     double *total);

/**
 * @brief Differentiated-payment loan calculator.
 * @param[out] payments_out Array of `months` monthly payments (caller-allocated).
 */
int s21_loan_differentiated(double principal, int months, double annual_rate,
                            double *payments_out, double *overpayment,
                            double *total);

/**
 * @brief Deposit profitability calculator with replenishments, withdrawals,
 *        capitalisation, and tax.
 * @param amount             Initial deposit.
 * @param months             Term length.
 * @param annual_rate        Annual interest rate.
 * @param tax_rate           Tax on interest (0..1).
 * @param periods_per_year   Compounding frequency (12 = monthly, 4 = quarterly).
 * @param capitalize         1 = re-deposit interest, 0 = pay out.
 * @param add_months / add_amounts / add_count  Replenishment schedule.
 * @param wd_months / wd_amounts / wd_count     Withdrawal schedule.
 * @param[out] total_interest Total interest earned across the term.
 * @param[out] tax_out        Tax payable on @p total_interest.
 * @param[out] final_amount   Closing balance.
 * @return 1 on success, 0 on invalid input.
 */
int s21_deposit(double amount, int months, double annual_rate, double tax_rate,
                int periods_per_year, int capitalize, const int *add_months,
                const double *add_amounts, int add_count, const int *wd_months,
                const double *wd_amounts, int wd_count, double *total_interest,
                double *tax_out, double *final_amount);

#endif /* SRC_FINANCE_S21_FINANCE_H_ */
