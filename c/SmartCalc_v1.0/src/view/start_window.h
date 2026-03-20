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

class Start_Window : public QMainWindow {
  Q_OBJECT

 public:
  Start_Window(QWidget* parent = nullptr);
  ~Start_Window();

 private slots:
  void on_Calculator_Button_clicked();
  void on_Credit_Button_clicked();
  void on_Deposit_Button_clicked();

 private:
  Ui ::Start_Window* ui;
  Window_One calculator;
  Window_Two credit_calculator;
  Window_Three deposit_calculator;
};

#endif  // START_WINDOW_H
