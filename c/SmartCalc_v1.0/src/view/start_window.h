/**
 * @file start_window.h
 * @brief Launcher window — three buttons routing the user to the
 *        calculator, credit, or deposit panel.
 *
 * The three downstream windows (@ref Window_One / @ref Window_Two /
 * @ref Window_Three) are constructed eagerly as members so switching
 * between them only flips visibility — no reconstruction cost.
 */

#ifndef START_WINDOW_H
#define START_WINDOW_H

#include <window_one.h>
#include <window_three.h>
#include <window_two.h>

#include <QMainWindow>

QT_BEGIN_NAMESPACE

namespace Ui {
class Start_Window;
}

QT_END_NAMESPACE

/**
 * @brief Top-level launcher for `SmartCalc_v1.0`.
 *
 * Owns the three feature windows and routes the user via three
 * push-button slots.
 */
class Start_Window : public QMainWindow {
  Q_OBJECT

 public:
  Start_Window(QWidget* parent = nullptr);
  ~Start_Window();

 private slots:
  /** @brief Show the @ref Window_One calculator panel. */
  void on_Calculator_Button_clicked();
  /** @brief Show the @ref Window_Two credit panel. */
  void on_Credit_Button_clicked();
  /** @brief Show the @ref Window_Three deposit panel. */
  void on_Deposit_Button_clicked();

 private:
  Ui ::Start_Window* ui;
  Window_One calculator;            ///< Calculator panel (eager-constructed).
  Window_Two credit_calculator;     ///< Credit panel.
  Window_Three deposit_calculator;  ///< Deposit panel.
};

#endif  // START_WINDOW_H
