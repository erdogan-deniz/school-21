#include "depositwindow.h"

// Constructor
DepositWindow::DepositWindow(QWidget* parent)
    : QDialog(parent), ui(new Ui::DepositWindow) {
  ui->setupUi(this);
  setFixedSize(483, 390);
  EditDate();
  SetValidators();
  SetStartNumbers();
}

// Destructor
DepositWindow::~DepositWindow() { delete ui; }

// Edits date of credit
void DepositWindow::EditDate() {
  ui->input_date->setDisplayFormat("dd/MM/yyyy");
  current_ = QDate::currentDate();
  ui->input_date->setDate(current_);
}

void DepositWindow::SetStartNumbers() {
  ui->sum_input->setText("120000");
  ui->period_input->setText("12");
  ui->interest_rate_input->setText("12.5");
  ui->tax_rate_input->setText("35");
}

void DepositWindow::SetValidators() {
  ui->sum_input->setValidator(new QDoubleValidator(1, 1.7E-308, 7, this));
  ui->period_input->setValidator(new QIntValidator(1, 600, this));
  ui->interest_rate_input->setValidator(new QDoubleValidator(1, 999, 7, this));
  ui->tax_rate_input->setValidator(new QIntValidator(1, 35, this));
}
// Validates user input
int DepositWindow::ValidateInput() {
  return CheckNull(ui->sum_input->text()) ||
         CheckNull(ui->period_input->text()) ||
         CheckNull(ui->interest_rate_input->text()) ||
         CheckNull(ui->tax_rate_input->text());
}

// Checks if a QString is null or empty
int DepositWindow::CheckNull(QString str) {
  return str == '0' || str == "00" || str.isEmpty();
}

void DepositWindow::SetNull() {
  ui->tax_show->setText("0");
  ui->income_show->setText("0");
  ui->total_deposit->setText("0");
}

void DepositWindow::SetDepositInfo() {
  info_.start_sum = ui->sum_input->text().toDouble();
  info_.months = ui->period_input->text().toDouble();
  info_.interest = ui->interest_rate_input->text().toDouble() / 100;
  info_.tax = ui->tax_rate_input->text().toDouble() / 100;
  QDate futureDate = current_.addMonths(info_.months);
  info_.days = current_.daysTo(futureDate);
  SetFrequency();
}

void DepositWindow::SetFrequency() {
  if (ui->caps_button->isChecked()) {
    if (ui->freq_of_pay->currentText() == "daily") {
      info_.frequency = s21::kDaily;
    } else if (ui->freq_of_pay->currentText() == "monthly") {
      info_.frequency = s21::kMonthly;
    } else if (ui->freq_of_pay->currentText() == "quarterly") {
      info_.frequency = s21::kQuarterly;
    } else if (ui->freq_of_pay->currentText() == "every six months") {
      info_.frequency = s21::kHalfYearly;
    } else if (ui->freq_of_pay->currentText() == "yearly") {
      info_.frequency = s21::kYearly;
    } else
      info_.frequency = s21::kEnd;
  } else {
    info_.frequency = s21::kEnd;
  }
}

void DepositWindow::SetResult() {
  income_ = QString::number(result_.income, 'g', 14);
  tax_ = QString::number(result_.tax, 'g', 14);
  total_sum_ = QString::number(result_.end_sum, 'g', 14);

  if (clone_total_sum_ != total_sum_) {
    clone_total_sum_ = total_sum_;
    ui->income_show->setText(income_);
    ui->tax_show->setText(tax_);
    ui->total_deposit->setText(total_sum_);
  }
}

// Deletes values of result
void DepositWindow::DeleteResult() {
  income_.clear();
  tax_.clear();
  total_sum_.clear();
}

// Handles the click event of the "calculate" button
void DepositWindow::on_pushButton_calculate_clicked() {
  if (!ValidateInput()) {
    SetDepositInfo();
    result_ = controller_.Run(info_);
    SetResult();
  } else {
    SetNull();
  }
  DeleteResult();
}
