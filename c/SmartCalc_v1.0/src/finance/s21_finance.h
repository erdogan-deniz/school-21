#ifndef SRC_FINANCE_S21_FINANCE_H_
#define SRC_FINANCE_S21_FINANCE_H_

int s21_loan_annuity(double principal, int months, double annual_rate,
                     double *monthly_payment, double *overpayment,
                     double *total);

int s21_loan_differentiated(double principal, int months, double annual_rate,
                             double *payments_out, double *overpayment,
                             double *total);

int s21_deposit(double amount, int months, double annual_rate, double tax_rate,
                int periods_per_year, int capitalize,
                const int *add_months, const double *add_amounts, int add_count,
                const int *wd_months, const double *wd_amounts, int wd_count,
                double *total_interest, double *tax_out, double *final_amount);

#endif  /* SRC_FINANCE_S21_FINANCE_H_ */
