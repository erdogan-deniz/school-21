#ifndef WINDOW_TWO_H
#define WINDOW_TWO_H

#include <math.h>

#include <QWidget>
#include <sstream>

#define empty 0

typedef struct s21_payments {
  long double debt;
  long double percents;
  int month_number;
  struct s21_payments* next;
  struct s21_payments* prev;
} s21_payments;

namespace Ui {
class Window_Two;
}

class Window_Two : public QWidget {
  Q_OBJECT

 public:
  explicit Window_Two(QWidget* parent = nullptr);
  ~Window_Two();

 private slots:
  QString s21_long_double_to_QString(long double value);
  int s21_QString_to_int(QString qstring);
  long double s21_QString_to_long_double(QString qstring);
  void on_annuity_box_clicked();
  void s21_annuity_solution(long double total_amount, int month_duration,
                            long double percents);
  void s21_differtial_solution(long double total_amount, int month_duration,
                               long double percents);
  void on_button_calculate_clicked();
  void on_box_differentiated_clicked();
  void on_line_total_credit_amount_textEdited();
  void on_line_interest_rate_textEdited();
  void on_line_term_textEdited();

 private:
  Ui :: Window_Two* ui;
};

#endif  // WINDOW_TWO_H
