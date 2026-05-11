/**
 * @file window_three.h
 * @brief Deposit panel — compound-interest calculator with optional
 *        replenishments and withdrawals.
 *
 * Reuses @ref s21_payments from @ref window_two.h for the deposit /
 * withdrawal schedule lists.
 */

#ifndef WINDOW_THREE_H
#define WINDOW_THREE_H

#include <QWidget>

#include "window_two.h"

namespace Ui {
class Window_Three;
}

/**
 * @brief Deposit-calculator panel.
 *
 * Owns two `s21_payments*` chains — one for replenishments and one
 * for withdrawals — built incrementally as the user clicks the "+"
 * buttons.
 */
class Window_Three : public QWidget {
  Q_OBJECT

 public:
  explicit Window_Three(QWidget* parent = nullptr);
  s21_payments* set_money;  ///< Replenishment schedule (linked list).
  s21_payments* get_money;  ///< Withdrawal schedule (linked list).
  ~Window_Three();

 private slots:
  /** @brief Core deposit solver — folds @p set_money / @p get_money in. */
  void s21_deposit_solution(long double sum, int month_duration,
                            long double percents, long double tax_percents,
                            int ratio_payments_mounths, bool capital_percents,
                            s21_payments* set_money, s21_payments* get_money);
  /** @brief Main "Calculate" button. */
  void on_button_calculate_clicked();
  /** @brief Format a `long double` with the panel's display precision. */
  QString s21_long_double_to_QString(long double value);
  /** @brief Strict QString → int conversion. */
  int s21_QString_to_int(QString qstring);
  /** @brief Strict QString → long double conversion. */
  long double s21_QString_to_long_double(QString qstring);
  /** @brief Add a row to the replenishments table. */
  void on_button_plus_clicked();
  /** @brief Add a row to the withdrawals table. */
  void on_button_plus2_clicked();

 private:
  Ui ::Window_Three* ui;
};

#endif  // WINDOW_THREE_H
