#ifndef SRC_VIEW_DEPOSITWINDOW_H
#define SRC_VIEW_DEPOSITWINDOW_H

#include <QDate>
#include <QDialog>
#include <QLineEdit>

#include "../Controller/depositcontroller.h"
#include "ui_depositwindow.h"

namespace Ui {
class DepositWindow;
}

class DepositWindow : public QDialog {
  Q_OBJECT

 public:
  // Constructor
  explicit DepositWindow(QWidget* parent = nullptr);
  // Destructor
  ~DepositWindow();
  // Setters
  void SetNull();
  void SetResult();
  void SetFrequency();
  void SetStartNumbers();
  void SetValidators();
  void SetDepositInfo();

 private:
  Ui::DepositWindow* ui;
  QString tax_{};
  QDate current_{};
  QString income_{};
  QString total_sum_{};
  QString clone_total_sum_{};
  s21::DepositInfo info_{};
  s21::DepositResult result_{};
  s21::DepositController controller_{};

 private slots:
  // Validates user input
  int ValidateInput();
  // Edits date of credit
  void EditDate();
  // Deletes values of result
  void DeleteResult();
  // Checks if a QString is null or empty
  int CheckNull(QString str);
  // Handles the click event of the "calculate" button
  void on_pushButton_calculate_clicked();
};

#endif  // SRC_VIEW_DEPOSITWINDOW_H
