/**
 * @file window_two.h
 * @brief Credit panel — annuity / differentiated payment calculator.
 *
 * Re-declares @ref s21_payments locally (so the widget doesn't pull
 * the full `bonus/s21_bonus.h` umbrella). The two solution functions
 * dispatch based on the radio-button group.
 */

#ifndef WINDOW_TWO_H
#define WINDOW_TWO_H

#include <math.h>

#include <QWidget>
#include <sstream>

#define empty 0

/**
 * @brief Per-month credit row — duplicate of the one in
 *        `bonus/s21_bonus.h`, kept here so the widget header stays
 *        independent.
 */
typedef struct s21_payments {
  long double debt;             ///< Remaining principal at month end.
  long double percents;         ///< Interest accrued this month.
  int month_number;             ///< 1-based month index.
  struct s21_payments* next;
  struct s21_payments* prev;
} s21_payments;

namespace Ui {
class Window_Two;
}

/**
 * @brief Credit-calculator panel.
 *
 * Pulls user input from the form, dispatches to the appropriate
 * (annuity / differentiated) solver, and renders the result inline.
 */
class Window_Two : public QWidget {
  Q_OBJECT

 public:
  explicit Window_Two(QWidget* parent = nullptr);
  ~Window_Two();

 private slots:
  /** @brief Format a `long double` with the panel's display precision. */
  QString s21_long_double_to_QString(long double value);
  /** @brief Strict QString → int conversion. */
  int s21_QString_to_int(QString qstring);
  /** @brief Strict QString → long double conversion. */
  long double s21_QString_to_long_double(QString qstring);
  /** @brief Annuity radio-button selected. */
  void on_annuity_box_clicked();
  /** @brief Compute annuity-formula schedule and render results. */
  void s21_annuity_solution(long double total_amount, int month_duration,
                            long double percents);
  /** @brief Compute differentiated-formula schedule and render results. */
  void s21_differtial_solution(long double total_amount, int month_duration,
                               long double percents);
  /** @brief Main "Calculate" button — dispatches to the chosen solver. */
  void on_button_calculate_clicked();
  /** @brief Differentiated radio-button selected. */
  void on_box_differentiated_clicked();
  void on_line_total_credit_amount_textEdited();
  void on_line_interest_rate_textEdited();
  void on_line_term_textEdited();

 private:
  Ui ::Window_Two* ui;
};

#endif  // WINDOW_TWO_H
