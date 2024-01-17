#include "creditwindow.h"

// Constructor
CreditWindow::CreditWindow(QWidget* parent)
    : QDialog(parent), ui(new Ui::CreditWindow) {
  ui->setupUi(this);
  setFixedSize(515, 350);
  SetValidators();
}

// Destructor
CreditWindow::~CreditWindow() { delete ui; }

void CreditWindow::SetValidators() {
  ui->credit_show->setValidator(new QDoubleValidator(1, 1.7E-308, 7, this));
  ui->term_show->setValidator(new QIntValidator(1, 50, this));
  ui->interest_show->setValidator(new QDoubleValidator(1, 999, 7, this));
}

// Validates user input
int CreditWindow::ValidateInput() {
  return CheckNull(ui->credit_show->text()) ||
         CheckNull(ui->term_show->text()) ||
         CheckNull(ui->interest_show->text());
}

// Checks if a QString is null or empty
int CreditWindow::CheckNull(QString str) {
  return str == '0' || str == "00" || str.isEmpty();
}

void CreditWindow::SetCreditInfo() {
  info_.sum = ui->credit_show->text().toDouble();
  info_.months = ui->term_show->text().toDouble();
  info_.interest = ui->interest_show->text().toDouble();

  QString q_period = ui->period_term->currentText();
  QString q_payment = ui->type_show->currentText();
  info_.period = q_period.toStdString();
  info_.payment = q_payment.toStdString();
}

//  Appends points to QString
void CreditWindow::AppendPoints() {
  if (result_.min_pay != 0) {
    q_pay_.append(" ... ");
    double min_pay = result_.min_pay;
    QString q_min_pay = QString::number(round(min_pay * 100) / 100, 'g', 14);
    q_pay_.append(q_min_pay);
  }
}

void CreditWindow::SetResult() {
  if (q_pay_clone_ != q_pay_) {
    q_pay_clone_ = q_pay_;
    ui->payment_show->setText(q_pay_);
    ui->clean_int_show->setText(q_overpay_);
    ui->debt_plus_int_show->setText(q_sum_);
  }
}

// Deletes values of result
void CreditWindow::DeleteResult() {
  q_pay_.clear();
  q_overpay_.clear();
  q_sum_.clear();
}

void CreditWindow::SetNull() {
  ui->payment_show->setText("0");
  ui->clean_int_show->setText("0");
  ui->debt_plus_int_show->setText("0");
}

// Handles the click event of the "calculate" button
void CreditWindow::on_pushButton_calculate_clicked() {
  if (!ValidateInput()) {
    SetCreditInfo();
    result_ = controller_.Run(info_);
    q_overpay_ = QString::number(result_.overpay, 'g', 14);
    q_sum_ = QString::number(result_.sum_total, 'g', 14);
    q_pay_ = QString::number(round(result_.max_pay * 100) / 100, 'g', 14);
    AppendPoints();
    SetResult();
    DeleteResult();
  } else {
    SetNull();
    DeleteResult();
  }
}
