#ifndef WINDOW_THREE_H
#define WINDOW_THREE_H

#include <QWidget>

#include "window_two.h"

namespace Ui {
    class Window_Three;
}

class Window_Three : public QWidget {
  Q_OBJECT

 public:
  explicit Window_Three(QWidget* parent = nullptr);
  s21_payments* set_money;
  s21_payments* get_money;
  ~Window_Three();

 private slots:
  void s21_deposit_solution(long double sum, int month_duration,
                            long double percents, long double tax_percents,
                            int ratio_payments_mounths, bool capital_percents,
                            s21_payments* set_money, s21_payments* get_money);
  void on_button_calculate_clicked();
  QString s21_long_double_to_QString(long double value);
  int s21_QString_to_int(QString qstring);
  long double s21_QString_to_long_double(QString qstring);
  void on_button_plus_clicked();
  void on_button_plus2_clicked();

 private:
  Ui :: Window_Three* ui;
};

#endif  // WINDOW_THREE_H
