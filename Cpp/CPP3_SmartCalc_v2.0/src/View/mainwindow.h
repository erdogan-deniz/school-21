#ifndef SRC_VIEW_MAINWINDOW_H
#define SRC_VIEW_MAINWINDOW_H

#include <QDoubleValidator>
#include <QIntValidator>
#include <QMainWindow>
#include <cstring>

#include "creditwindow.h"
#include "depositwindow.h"
#include "graphwindow.h"
#include "ui_mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  // Constructor
  MainWindow(QWidget* parent = nullptr);
  // Destructor
  ~MainWindow();
  // Sets up connections between buttons and slots
  void ConnectButtonToSlot(QPushButton* button, const char* slot);
  void InitializeConnections();
  // Setters
  void SetNull();
  void SetValidators();
  void SetMaxMinValues();

 private:
  Ui::MainWindow* ui;
  QString q_problem_{};
  QString clone_{};
  QString x_value_{};
  QString x_max_value_{};
  QString x_min_value_{};
  int x_flag_{};
  int unar_flag_{};
  int not_null_{};
  int operands_flag_{};
  int brackets_flag_{};
  int result_flag_{};
  int graph_flag_{};
  int counter_{};
  std::string value_{};
  std::string problem_{};
  s21::CalculatorController controller_{};

 private slots:
  // Functions for checking various aspects of the input string
  void IsStringCorrect();
  void IsUnarSymbol();
  void CheckResultFlag();
  void IsEmptyString();
  // Functions for adding elements to the input string
  void AddNumber();
  void AddFunction();
  void AddOperator();
  void AddOpenBracket();
  void AddFunctionBrackets();
  void AddCloseBracket();
  // Function for drawing a graph
  void DrawGraph();
  // Functions for converting strings and processing results
  void ConvertQString();
  void SetResult();
  void CheckXValues(double* result, double* x_max, double* x_min);
  // Event handler functions for button clicks
  void on_pushButton_pow_clicked();
  void on_pushButton_clear_clicked();
  void on_pushButton_equal_sign_clicked();
  void on_pushButton_mod_clicked();
  void on_pushButton_x_clicked();
  void on_pushButton_credit_clicked();
  void on_pushButton_deposit_clicked();
};

#endif  // SRC_VIEW_MAINWINDOW_H
