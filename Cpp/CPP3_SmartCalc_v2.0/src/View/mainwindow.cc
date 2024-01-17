#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  setFixedSize(549, 366);
  SetValidators();
  InitializeConnections();
}

void MainWindow::ConnectButtonToSlot(QPushButton *button, const char *slot) {
  connect(button, SIGNAL(clicked()), this, slot);
}

void MainWindow::InitializeConnections() {
  ConnectButtonToSlot(ui->pushButton_0, SLOT(AddNumber()));
  ConnectButtonToSlot(ui->pushButton_1, SLOT(AddNumber()));
  ConnectButtonToSlot(ui->pushButton_2, SLOT(AddNumber()));
  ConnectButtonToSlot(ui->pushButton_3, SLOT(AddNumber()));
  ConnectButtonToSlot(ui->pushButton_4, SLOT(AddNumber()));
  ConnectButtonToSlot(ui->pushButton_5, SLOT(AddNumber()));
  ConnectButtonToSlot(ui->pushButton_6, SLOT(AddNumber()));
  ConnectButtonToSlot(ui->pushButton_7, SLOT(AddNumber()));
  ConnectButtonToSlot(ui->pushButton_8, SLOT(AddNumber()));
  ConnectButtonToSlot(ui->pushButton_9, SLOT(AddNumber()));
  ConnectButtonToSlot(ui->pushButton_dot, SLOT(AddOperator()));
  ConnectButtonToSlot(ui->pushButton_br_open, SLOT(AddOpenBracket()));
  ConnectButtonToSlot(ui->pushButton_br_close, SLOT(AddCloseBracket()));
  ConnectButtonToSlot(ui->pushButton_minus, SLOT(AddOperator()));
  ConnectButtonToSlot(ui->pushButton_plus, SLOT(AddOperator()));
  ConnectButtonToSlot(ui->pushButton_multiply, SLOT(AddOperator()));
  ConnectButtonToSlot(ui->pushButton_divide, SLOT(AddOperator()));
  ConnectButtonToSlot(ui->pushButton_sqrt, SLOT(AddFunction()));
  ConnectButtonToSlot(ui->pushButton_sin, SLOT(AddFunction()));
  ConnectButtonToSlot(ui->pushButton_cos, SLOT(AddFunction()));
  ConnectButtonToSlot(ui->pushButton_asin, SLOT(AddFunction()));
  ConnectButtonToSlot(ui->pushButton_acos, SLOT(AddFunction()));
  ConnectButtonToSlot(ui->pushButton_ln, SLOT(AddFunction()));
  ConnectButtonToSlot(ui->pushButton_log, SLOT(AddFunction()));
  ConnectButtonToSlot(ui->pushButton_tan, SLOT(AddFunction()));
  ConnectButtonToSlot(ui->pushButton_atan, SLOT(AddFunction()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::SetValidators() {
  ui->result_show->setAlignment(Qt::AlignCenter | Qt::AlignRight);
  ui->x_show->setValidator(new QDoubleValidator(-1000000, 1000000, 7, this));
  ui->x_max->setValidator(new QDoubleValidator(-1000000, 1000000, 7, this));
  ui->x_min->setValidator(new QDoubleValidator(-1000000, 1000000, 7, this));

  ui->x_show->setMaxLength(6);
  ui->x_max->setMaxLength(6);
  ui->x_min->setMaxLength(6);
  on_pushButton_clear_clicked();
}

void MainWindow::SetNull() {
  unar_flag_ = 0;
  graph_flag_ = 0;
  operands_flag_ = 0;
  brackets_flag_ = 0;
  result_flag_ = 0;
  x_flag_ = 0;
  counter_ = 0;
}

void MainWindow::AddNumber() {
  if (counter_ < 256) {
    QPushButton *button = (QPushButton *)sender();
    if (button->text() >= '0' && button->text() <= '9') {
      operands_flag_ = 0;
      x_flag_ = 1;
      CheckResultFlag();
      counter_++;
    }
    q_problem_.append(button->text());
    ui->result_show->setText(q_problem_);
  }
}

void MainWindow::on_pushButton_x_clicked() {
  if (counter_ < 256 && x_flag_ != 1) {
    operands_flag_ = 0;
    CheckResultFlag();
    counter_++;
    x_flag_ = 1;
    graph_flag_ = 1;
    q_problem_.append('x');
  }
  ui->result_show->setText(q_problem_);
}

void MainWindow::CheckResultFlag() {
  if (result_flag_ == 1) {
    q_problem_.clear();
    result_flag_ = 0;
  }
}

void MainWindow::AddOperator() {
  QPushButton *button = (QPushButton *)sender();
  if (q_problem_.isEmpty() && button->text() != '-') q_problem_.append('0');
  if ((operands_flag_ == 0 || (unar_flag_ && button->text() == '-')) &&
      counter_ < 256) {
    q_problem_.append(button->text());
    ui->result_show->setText(q_problem_);
    operands_flag_ = 1;
    result_flag_ = 0;
    not_null_ = 0;
    x_flag_ = 0;
    IsUnarSymbol();
    counter_++;
  }
}

void MainWindow::IsUnarSymbol() {
  if (q_problem_.endsWith('*') || q_problem_.endsWith('/'))
    unar_flag_ = 1;
  else if (q_problem_.endsWith('-') && unar_flag_)
    unar_flag_ = 0;
}

void MainWindow::on_pushButton_mod_clicked() {
  QPushButton *button = (QPushButton *)sender();
  if (q_problem_.isEmpty() && button->text() != '-') q_problem_.append('0');
  if (operands_flag_ == 0 && counter_ < 256) {
    q_problem_.append(" mod ");
    ui->result_show->setText(q_problem_);
    operands_flag_ = 1;
    result_flag_ = 0;
    x_flag_ = 0;
    counter_ += 3;
  }
}

void MainWindow::AddOpenBracket() {
  if ((operands_flag_ == 1 || q_problem_.isEmpty()) && counter_ < 256) {
    QPushButton *button = (QPushButton *)sender();
    q_problem_.append(button->text());
    ui->result_show->setText(q_problem_);
    brackets_flag_++;
    unar_flag_ = 1;
    operands_flag_ = 1;
    x_flag_ = 0;
    counter_++;
  }
}

void MainWindow::AddFunctionBrackets() {
  q_problem_.append('(');
  ui->result_show->setText(q_problem_);
  brackets_flag_++;
  unar_flag_ = 1;
  operands_flag_ = 1;
  x_flag_ = 0;
  counter_++;
}

void MainWindow::AddCloseBracket() {
  QPushButton *button = (QPushButton *)sender();
  if (brackets_flag_ > 0 && counter_ < 256) {
    q_problem_.append(button->text());
    ui->result_show->setText(q_problem_);
    brackets_flag_--;
    x_flag_ = 1;
    counter_++;
  }
}

void MainWindow::AddFunction() {
  CheckResultFlag();
  if ((operands_flag_ == 1 || q_problem_.isEmpty()) && counter_ < 256) {
    QPushButton *button = (QPushButton *)sender();
    q_problem_.append(button->text());
    AddFunctionBrackets();
    ui->result_show->setText(q_problem_);
    counter_ += 3;
  }
}

void MainWindow::on_pushButton_pow_clicked() {
  if (q_problem_.isEmpty()) q_problem_.append('0');
  if (operands_flag_ == 0 && counter_ < 256) {
    q_problem_.append('^');
    ui->result_show->setText(q_problem_);
    operands_flag_ = 1;
    result_flag_ = 0;
    x_flag_ = 0;
    counter_++;
  }
}

void MainWindow::on_pushButton_clear_clicked() {
  SetNull();
  q_problem_ = "0";
  ui->result_show->setText(q_problem_);
  ui->x_show->clear();
  ui->x_max->clear();
  ui->x_min->clear();
  q_problem_.clear();
}

void MainWindow::DrawGraph() {
  double result = q_problem_.toDouble();
  double x_max = x_max_value_.toDouble();
  double x_min = x_min_value_.toDouble();
  CheckXValues(&result, &x_max, &x_min);
  if (graph_flag_) {
    ui->result_show->setText(q_problem_);
    GraphWindow graph_window;
    graph_window.DrawFinalGraph(x_max, x_min, problem_, value_);
    graph_window.setModal(true);
    graph_window.exec();
  }
}

void MainWindow::IsEmptyString() {
  if (x_max_value_.isEmpty() && x_min_value_.isEmpty()) graph_flag_ = 0;
  if (x_max_value_.isEmpty() && !x_min_value_.isEmpty()) graph_flag_ = 0;
  if (!x_max_value_.isEmpty() && x_min_value_.isEmpty()) graph_flag_ = 0;
}

void MainWindow::CheckXValues(double *result, double *x_max, double *x_min) {
  if (*result > *x_max) *x_max = *result;
  if (*x_min > *result) *x_min = *result;
  if (*x_min >= *x_max) {
    double tmp = *x_min;
    *x_min = *x_max;
    *x_max = tmp;
  }
  IsEmptyString();
}

void MainWindow::IsStringCorrect() {
  if (q_problem_ == "inf" || q_problem_ == "nan" || q_problem_ == "Error") {
    q_problem_.clear();
  } else {
    DrawGraph();
  }
}

void MainWindow::SetMaxMinValues() {
  x_value_ = ui->x_show->text();
  x_min_value_ = ui->x_min->text();
  x_max_value_ = ui->x_max->text();
  if (x_value_.isEmpty()) x_value_ = "0";
}

void MainWindow::ConvertQString() {
  QByteArray x_byte = x_value_.toUtf8();
  QByteArray str_byte = q_problem_.toUtf8();
  value_ = std::string(x_byte.constData());
  problem_ = std::string(str_byte.constData());
  controller_.Run(problem_, value_);
}

void MainWindow::SetResult() {
  if (controller_.GetError() == 1) {
    q_problem_ = "Error";
    controller_.SetError(0);
  } else {
    q_problem_ = QString::number(controller_.GetResult(), 'g', 14);
  }
  ui->result_show->setText(q_problem_);
  IsStringCorrect();
  SetNull();
  result_flag_ = 1;
  clone_ = q_problem_;
}

void MainWindow::on_pushButton_equal_sign_clicked() {
  if (operands_flag_ == 0 && q_problem_ != clone_) {
    SetMaxMinValues();
    ConvertQString();
    SetResult();
  } else if (operands_flag_ && counter_ == 256) {
    on_pushButton_clear_clicked();
  }
}

void MainWindow::on_pushButton_credit_clicked() {
  CreditWindow credit_window;
  credit_window.setModal(true);
  credit_window.exec();
}

void MainWindow::on_pushButton_deposit_clicked() {
  DepositWindow deposit_window;
  deposit_window.setModal(true);
  deposit_window.exec();
}
