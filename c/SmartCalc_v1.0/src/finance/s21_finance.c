#include "s21_finance.h"

#include <math.h>

int s21_loan_annuity(double principal, int months, double annual_rate,
                     double *monthly_payment, double *overpayment,
                     double *total) {
  if (principal <= 0.0 || months <= 0 || annual_rate < 0.0) return 1;
  if (!monthly_payment || !overpayment || !total) return 1;

  double r = annual_rate / 12.0 / 100.0;
  double payment;

  if (r == 0.0) {
    payment = principal / months;
  } else {
    /* payment = P*r / (1-(1+r)^-n)
       denom   = 1-(1+r)^-n = -expm1(-n*log1p(r))
       expm1/log1p give numerical stability when r -> 0 */
    double denom = -expm1(-(double)months * log1p(r));
    payment = (denom != 0.0) ? (principal * r / denom) : (principal / months);
  }

  *monthly_payment = payment;
  *total = payment * months;
  *overpayment = *total - principal;
  return 0;
}

int s21_loan_differentiated(double principal, int months, double annual_rate,
                            double *payments_out, double *overpayment,
                            double *total) {
  if (principal <= 0.0 || months <= 0 || annual_rate < 0.0) return 1;
  if (!payments_out || !overpayment || !total) return 1;

  double r = annual_rate / 12.0 / 100.0;
  double principal_part = principal / months;
  double sum = 0.0;

  /* Caller must allocate payments_out[months] before calling. */
  for (int i = 0; i < months; i++) {
    double remaining = principal - principal_part * i;
    payments_out[i] = principal_part + remaining * r;
    sum += payments_out[i];
  }

  *total = sum;
  *overpayment = sum - principal;
  return 0;
}

int s21_deposit(double amount, int months, double annual_rate, double tax_rate,
                int periods_per_year, int capitalize, const int *add_months,
                const double *add_amounts, int add_count, const int *wd_months,
                const double *wd_amounts, int wd_count, double *total_interest,
                double *tax_out, double *final_amount) {
  if (amount <= 0.0 || months <= 0 || annual_rate < 0.0 || tax_rate < 0.0 ||
      tax_rate > 100.0 || periods_per_year <= 0 || 12 % periods_per_year != 0)
    return 1;
  if (!total_interest || !tax_out || !final_amount) return 1;

  double monthly_rate = annual_rate / 12.0 / 100.0;
  int pay_every = 12 / periods_per_year;
  double balance = amount;
  double total_int = 0.0;
  double accrued = 0.0;

  for (int month = 1; month <= months; month++) {
    /* Apply scheduled additions */
    for (int i = 0; i < add_count; i++)
      if (add_months[i] == month) balance += add_amounts[i];

    /* Apply scheduled withdrawals; clamp to 0 */
    for (int i = 0; i < wd_count; i++) {
      if (wd_months[i] == month) {
        balance -= wd_amounts[i];
        if (balance < 0.0) balance = 0.0;
      }
    }

    accrued += balance * monthly_rate;

    if (month % pay_every == 0) {
      total_int += accrued;
      if (capitalize) balance += accrued;
      accrued = 0.0;
    }
  }

  /* Flush tail period (months not divisible by pay_every) */
  if (accrued > 0.0) {
    total_int += accrued;
    if (capitalize) balance += accrued;
  }

  *total_interest = total_int;
  *tax_out = total_int * tax_rate / 100.0;
  double gross = capitalize ? balance : (balance + total_int);
  *final_amount = gross - *tax_out;
  return 0;
}
