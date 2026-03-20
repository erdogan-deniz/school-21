/********************************************************************************
** Form generated from reading UI file 'window_three.ui'
**
** Created by: Qt User Interface Compiler version 6.5.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINDOW_THREE_H
#define UI_WINDOW_THREE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Window_Three {
 public:
  QLabel *label_deposit_amount;
  QLabel *label_input_data;
  QLabel *label_deposit_term;
  QLabel *label_interest_rate;
  QLabel *label_tax_rate;
  QLabel *label_periodicity_of;
  QListWidget *list_with;
  QLabel *label_with_list;
  QLineEdit *line_sum;
  QLabel *label_add_with;
  QLabel *label_sum_2;
  QLineEdit *line_num_month;
  QLabel *label_n_month2;
  QLabel *label_output_data;
  QLineEdit *line_deposit_amount;
  QLineEdit *line_deposit_term;
  QLineEdit *line_interest_rate;
  QLineEdit *line_tax_rate;
  QLineEdit *line_periodicity_of;
  QCheckBox *checkbox_capitalization;
  QLabel *label_repl_list;
  QListWidget *list_repl;
  QLineEdit *line_num_month2;
  QLineEdit *line_sum2;
  QLabel *label_sum;
  QLabel *label_n_month;
  QLabel *label_accrued_int;
  QLineEdit *line_accrued_interest;
  QLineEdit *line_tax_amount;
  QLabel *label_tax_amount;
  QLineEdit *line_deposit_amount_by_the_end;
  QLabel *label_deposit_amount_2;
  QPushButton *button_calculate;
  QLabel *label_line;
  QLabel *label_by_the_end;
  QPushButton *button_plus;
  QLabel *label_add_repl;
  QLabel *label_payments;
  QLabel *label_interest;
  QPushButton *button_plus2;
  QLabel *label_months;
  QLabel *label;

  void setupUi(QWidget *Window_Three) {
    if (Window_Three->objectName().isEmpty())
      Window_Three->setObjectName("Window_Three");
    Window_Three->resize(1600, 900);
    label_deposit_amount = new QLabel(Window_Three);
    label_deposit_amount->setObjectName("label_deposit_amount");
    label_deposit_amount->setGeometry(QRect(30, 165, 240, 45));
    QFont font;
    font.setFamilies({QString::fromUtf8("Scheherazade")});
    font.setPointSize(26);
    label_deposit_amount->setFont(font);
    label_input_data = new QLabel(Window_Three);
    label_input_data->setObjectName("label_input_data");
    label_input_data->setGeometry(QRect(0, 0, 1196, 90));
    QFont font1;
    font1.setFamilies({QString::fromUtf8("Sylfaen")});
    font1.setPointSize(26);
    label_input_data->setFont(font1);
    label_input_data->setStyleSheet(
        QString::fromUtf8("background-color: Purple;\n"
                          "color: White;\n"
                          "border-style: outset;\n"
                          "border-width: 2px;\n"
                          "border-color: black;\n"
                          "border-top: 0;\n"
                          "border-right: 0; \n"
                          "border-bottom: 2px solid;\n"
                          " border-left: 0"));
    label_deposit_term = new QLabel(Window_Three);
    label_deposit_term->setObjectName("label_deposit_term");
    label_deposit_term->setGeometry(QRect(30, 260, 205, 45));
    label_deposit_term->setFont(font);
    label_interest_rate = new QLabel(Window_Three);
    label_interest_rate->setObjectName("label_interest_rate");
    label_interest_rate->setGeometry(QRect(30, 380, 210, 45));
    label_interest_rate->setFont(font);
    label_tax_rate = new QLabel(Window_Three);
    label_tax_rate->setObjectName("label_tax_rate");
    label_tax_rate->setGeometry(QRect(30, 475, 140, 45));
    label_tax_rate->setFont(font);
    label_periodicity_of = new QLabel(Window_Three);
    label_periodicity_of->setObjectName("label_periodicity_of");
    label_periodicity_of->setGeometry(QRect(30, 570, 210, 45));
    label_periodicity_of->setFont(font);
    list_with = new QListWidget(Window_Three);
    list_with->setObjectName("list_with");
    list_with->setGeometry(QRect(350, 470, 300, 325));
    QFont font2;
    font2.setFamilies({QString::fromUtf8("System")});
    font2.setPointSize(12);
    font2.setBold(true);
    list_with->setFont(font2);
    list_with->setStyleSheet(
        QString::fromUtf8("border-style: outset;\n"
                          "border-width: 2px;\n"
                          "border-radius: 10px;\n"
                          "border-color: black;\n"
                          "background-color: rgba(0, 0, 0, 0.1);"));
    label_with_list = new QLabel(Window_Three);
    label_with_list->setObjectName("label_with_list");
    label_with_list->setGeometry(QRect(370, 165, 260, 45));
    label_with_list->setFont(font);
    line_sum = new QLineEdit(Window_Three);
    line_sum->setObjectName("line_sum");
    line_sum->setGeometry(QRect(350, 430, 150, 35));
    QFont font3;
    font3.setFamilies({QString::fromUtf8("System")});
    font3.setPointSize(10);
    font3.setBold(true);
    line_sum->setFont(font3);
    line_sum->setStyleSheet(
        QString::fromUtf8("border-style: outset;\n"
                          "border-width: 2px;\n"
                          "border-radius: 10px;\n"
                          "border-color: black;\n"
                          "background-color: rgba(0, 0, 0, 0.1);"));
    label_add_with = new QLabel(Window_Three);
    label_add_with->setObjectName("label_add_with");
    label_add_with->setGeometry(QRect(350, 325, 260, 45));
    label_add_with->setFont(font);
    label_sum_2 = new QLabel(Window_Three);
    label_sum_2->setObjectName("label_sum_2");
    label_sum_2->setGeometry(QRect(350, 380, 65, 45));
    label_sum_2->setFont(font);
    line_num_month = new QLineEdit(Window_Three);
    line_num_month->setObjectName("line_num_month");
    line_num_month->setGeometry(QRect(520, 430, 65, 35));
    line_num_month->setFont(font3);
    line_num_month->setStyleSheet(
        QString::fromUtf8("border-style: outset;\n"
                          "border-width: 2px;\n"
                          "border-radius: 10px;\n"
                          "border-color: black;\n"
                          "background-color: rgba(0, 0, 0, 0.1);"));
    label_n_month2 = new QLabel(Window_Three);
    label_n_month2->setObjectName("label_n_month2");
    label_n_month2->setGeometry(QRect(520, 380, 135, 45));
    label_n_month2->setFont(font);
    label_output_data = new QLabel(Window_Three);
    label_output_data->setObjectName("label_output_data");
    label_output_data->setGeometry(QRect(1204, 0, 500, 90));
    label_output_data->setFont(font1);
    label_output_data->setStyleSheet(
        QString::fromUtf8("background-color: #060ADE;\n"
                          "color: White;\n"
                          "border-style: outset;\n"
                          "border-width: 2px;\n"
                          "border-color: black;\n"
                          "border-top: 0;\n"
                          "border-right: 0; \n"
                          "border-bottom: 2px solid;\n"
                          " border-left: 0"));
    line_deposit_amount = new QLineEdit(Window_Three);
    line_deposit_amount->setObjectName("line_deposit_amount");
    line_deposit_amount->setGeometry(QRect(30, 205, 230, 35));
    line_deposit_amount->setFont(font3);
    line_deposit_amount->setStyleSheet(
        QString::fromUtf8("border-style: outset;\n"
                          "border-width: 2px;\n"
                          "border-radius: 10px;\n"
                          "border-color: blac;\n"
                          "background-color: rgba(0, 0, 0, 0.1);"));
    line_deposit_term = new QLineEdit(Window_Three);
    line_deposit_term->setObjectName("line_deposit_term");
    line_deposit_term->setGeometry(QRect(30, 325, 190, 35));
    line_deposit_term->setFont(font3);
    line_deposit_term->setStyleSheet(
        QString::fromUtf8("border-style: outset;\n"
                          "border-width: 2px;\n"
                          "border-radius: 10px;\n"
                          "border-color: black;\n"
                          "background-color: rgba(0, 0, 0, 0.1);"));
    line_interest_rate = new QLineEdit(Window_Three);
    line_interest_rate->setObjectName("line_interest_rate");
    line_interest_rate->setGeometry(QRect(30, 420, 200, 35));
    line_interest_rate->setFont(font3);
    line_interest_rate->setStyleSheet(
        QString::fromUtf8("border-style: outset;\n"
                          "border-width: 2px;\n"
                          "border-radius: 10px;\n"
                          "border-color: black;\n"
                          "background-color: rgba(0, 0, 0, 0.1);"));
    line_tax_rate = new QLineEdit(Window_Three);
    line_tax_rate->setObjectName("line_tax_rate");
    line_tax_rate->setGeometry(QRect(30, 515, 130, 35));
    line_tax_rate->setFont(font3);
    line_tax_rate->setStyleSheet(
        QString::fromUtf8("border-style: outset;\n"
                          "border-width: 2px;\n"
                          "border-radius: 10px;\n"
                          "border-color: black;\n"
                          "background-color: rgba(0, 0, 0, 0.1);"));
    line_periodicity_of = new QLineEdit(Window_Three);
    line_periodicity_of->setObjectName("line_periodicity_of");
    line_periodicity_of->setGeometry(QRect(30, 635, 280, 35));
    line_periodicity_of->setFont(font3);
    line_periodicity_of->setStyleSheet(
        QString::fromUtf8("border-style: outset;\n"
                          "border-width: 2px;\n"
                          "border-radius: 10px;\n"
                          "border-color: black;\n"
                          "background-color: rgba(0, 0, 0, 0.1);"));
    checkbox_capitalization = new QCheckBox(Window_Three);
    checkbox_capitalization->setObjectName("checkbox_capitalization");
    checkbox_capitalization->setGeometry(QRect(30, 690, 281, 45));
    checkbox_capitalization->setFont(font);
    label_repl_list = new QLabel(Window_Three);
    label_repl_list->setObjectName("label_repl_list");
    label_repl_list->setGeometry(QRect(715, 165, 311, 45));
    label_repl_list->setFont(font);
    list_repl = new QListWidget(Window_Three);
    list_repl->setObjectName("list_repl");
    list_repl->setGeometry(QRect(710, 470, 300, 325));
    list_repl->setFont(font2);
    list_repl->setStyleSheet(
        QString::fromUtf8("border-style: outset;\n"
                          "border-width: 2px;\n"
                          "border-radius: 10px;\n"
                          "border-color: black;\n"
                          "background-color: rgba(0, 0, 0, 0.1);"));
    line_num_month2 = new QLineEdit(Window_Three);
    line_num_month2->setObjectName("line_num_month2");
    line_num_month2->setGeometry(QRect(880, 430, 65, 35));
    line_num_month2->setFont(font3);
    line_num_month2->setStyleSheet(
        QString::fromUtf8("border-style: outset;\n"
                          "border-width: 2px;\n"
                          "border-radius: 10px;\n"
                          "border-color: black;\n"
                          "background-color: rgba(0, 0, 0, 0.1);"));
    line_sum2 = new QLineEdit(Window_Three);
    line_sum2->setObjectName("line_sum2");
    line_sum2->setGeometry(QRect(710, 430, 150, 35));
    line_sum2->setFont(font3);
    line_sum2->setStyleSheet(
        QString::fromUtf8("border-style: outset;\n"
                          "border-width: 2px;\n"
                          "border-radius: 10px;\n"
                          "border-color: black;\n"
                          "background-color: rgba(0, 0, 0, 0.1);"));
    label_sum = new QLabel(Window_Three);
    label_sum->setObjectName("label_sum");
    label_sum->setGeometry(QRect(710, 380, 65, 45));
    label_sum->setFont(font);
    label_n_month = new QLabel(Window_Three);
    label_n_month->setObjectName("label_n_month");
    label_n_month->setGeometry(QRect(880, 380, 135, 45));
    label_n_month->setFont(font);
    label_accrued_int = new QLabel(Window_Three);
    label_accrued_int->setObjectName("label_accrued_int");
    label_accrued_int->setGeometry(QRect(1240, 375, 275, 45));
    label_accrued_int->setFont(font);
    line_accrued_interest = new QLineEdit(Window_Three);
    line_accrued_interest->setObjectName("line_accrued_interest");
    line_accrued_interest->setGeometry(QRect(1240, 420, 260, 40));
    line_accrued_interest->setFont(font3);
    line_accrued_interest->setStyleSheet(
        QString::fromUtf8("border-style: outset;\n"
                          "border-width: 2px;\n"
                          "border-radius: 10px;\n"
                          "border-color: black;\n"
                          "background-color: rgba(0, 0, 0, 0.1);"));
    line_tax_amount = new QLineEdit(Window_Three);
    line_tax_amount->setObjectName("line_tax_amount");
    line_tax_amount->setGeometry(QRect(1240, 585, 190, 40));
    line_tax_amount->setFont(font3);
    line_tax_amount->setStyleSheet(
        QString::fromUtf8("border-style: outset;\n"
                          "border-width: 2px;\n"
                          "border-radius: 10px;\n"
                          "border-color: black;\n"
                          "background-color: rgba(0, 0, 0, 0.1);"));
    label_tax_amount = new QLabel(Window_Three);
    label_tax_amount->setObjectName("label_tax_amount");
    label_tax_amount->setGeometry(QRect(1240, 540, 200, 45));
    QFont font4;
    font4.setFamilies({QString::fromUtf8("Scheherazade")});
    font4.setPointSize(28);
    label_tax_amount->setFont(font4);
    line_deposit_amount_by_the_end = new QLineEdit(Window_Three);
    line_deposit_amount_by_the_end->setObjectName(
        "line_deposit_amount_by_the_end");
    line_deposit_amount_by_the_end->setGeometry(QRect(1240, 245, 240, 40));
    line_deposit_amount_by_the_end->setFont(font3);
    line_deposit_amount_by_the_end->setStyleSheet(
        QString::fromUtf8("border-style: outset;\n"
                          "border-width: 2px;\n"
                          "border-radius: 10px;\n"
                          "border-color: black;\n"
                          "background-color: rgba(0, 0, 0, 0.1);"));
    label_deposit_amount_2 = new QLabel(Window_Three);
    label_deposit_amount_2->setObjectName("label_deposit_amount_2");
    label_deposit_amount_2->setGeometry(QRect(1240, 165, 250, 45));
    label_deposit_amount_2->setFont(font);
    button_calculate = new QPushButton(Window_Three);
    button_calculate->setObjectName("button_calculate");
    button_calculate->setGeometry(QRect(1020, 585, 170, 45));
    button_calculate->setFont(font);
    button_calculate->setStyleSheet(
        QString::fromUtf8("    border-style: outset;\n"
                          "    border-width: 2px;\n"
                          "    border-radius: 10px;\n"
                          "    border-color: black;\n"
                          "	background-color: rgba(0, 0, 0, 0.1);"));
    label_line = new QLabel(Window_Three);
    label_line->setObjectName("label_line");
    label_line->setGeometry(QRect(1196, 0, 8, 900));
    label_line->setStyleSheet(QString::fromUtf8("background-color: black"));
    label_by_the_end = new QLabel(Window_Three);
    label_by_the_end->setObjectName("label_by_the_end");
    label_by_the_end->setGeometry(QRect(1240, 195, 211, 45));
    label_by_the_end->setFont(font);
    button_plus = new QPushButton(Window_Three);
    button_plus->setObjectName("button_plus");
    button_plus->setGeometry(QRect(615, 430, 35, 35));
    button_plus->setFont(font);
    button_plus->setStyleSheet(
        QString::fromUtf8("border-style: outset;\n"
                          "border-width: 2px;\n"
                          "border-radius: 10px;\n"
                          "border-color: black;\n"
                          "background-color: #2FAB00;"));
    label_add_repl = new QLabel(Window_Three);
    label_add_repl->setObjectName("label_add_repl");
    label_add_repl->setGeometry(QRect(710, 325, 290, 45));
    label_add_repl->setFont(font);
    label_payments = new QLabel(Window_Three);
    label_payments->setObjectName("label_payments");
    label_payments->setGeometry(QRect(30, 595, 290, 45));
    label_payments->setFont(font);
    label_interest = new QLabel(Window_Three);
    label_interest->setObjectName("label_interest");
    label_interest->setGeometry(QRect(50, 715, 140, 45));
    label_interest->setFont(font);
    button_plus2 = new QPushButton(Window_Three);
    button_plus2->setObjectName("button_plus2");
    button_plus2->setGeometry(QRect(975, 430, 35, 35));
    button_plus2->setFont(font);
    button_plus2->setStyleSheet(
        QString::fromUtf8("border-style: outset;\n"
                          "border-width: 2px;\n"
                          "border-radius: 10px;\n"
                          "border-color: black;\n"
                          "background-color: #2FAB00;"));
    label_months = new QLabel(Window_Three);
    label_months->setObjectName("label_months");
    label_months->setGeometry(QRect(30, 285, 145, 45));
    label_months->setFont(font);
    label = new QLabel(Window_Three);
    label->setObjectName("label");
    label->setGeometry(QRect(0, 0, 1600, 900));
    label->setPixmap(
        QPixmap(QString::fromUtf8("images/window_three_background.jpg")));
    label->raise();
    label_deposit_amount->raise();
    label_input_data->raise();
    label_deposit_term->raise();
    label_interest_rate->raise();
    label_tax_rate->raise();
    label_periodicity_of->raise();
    list_with->raise();
    label_with_list->raise();
    line_sum->raise();
    label_add_with->raise();
    label_sum_2->raise();
    line_num_month->raise();
    label_n_month2->raise();
    label_output_data->raise();
    line_deposit_amount->raise();
    line_deposit_term->raise();
    line_interest_rate->raise();
    line_tax_rate->raise();
    line_periodicity_of->raise();
    checkbox_capitalization->raise();
    label_repl_list->raise();
    list_repl->raise();
    line_num_month2->raise();
    line_sum2->raise();
    label_sum->raise();
    label_n_month->raise();
    label_accrued_int->raise();
    line_accrued_interest->raise();
    line_tax_amount->raise();
    label_tax_amount->raise();
    line_deposit_amount_by_the_end->raise();
    label_deposit_amount_2->raise();
    button_calculate->raise();
    label_line->raise();
    label_by_the_end->raise();
    button_plus->raise();
    label_add_repl->raise();
    label_payments->raise();
    label_interest->raise();
    button_plus2->raise();
    label_months->raise();

    retranslateUi(Window_Three);

    QMetaObject::connectSlotsByName(Window_Three);
  }  // setupUi

  void retranslateUi(QWidget *Window_Three) {
    Window_Three->setWindowTitle(
        QCoreApplication::translate("Window_Three", "Form", nullptr));
    label_deposit_amount->setText(QCoreApplication::translate(
        "Window_Three", "DEPOSIT AMOUNT:", nullptr));
    label_input_data->setText(QCoreApplication::translate(
        "Window_Three",
        "                                                   INPUT DATA:",
        nullptr));
    label_deposit_term->setText(
        QCoreApplication::translate("Window_Three", "DEPOSIT TERM:", nullptr));
    label_interest_rate->setText(
        QCoreApplication::translate("Window_Three", "INTEREST RATE:", nullptr));
    label_tax_rate->setText(
        QCoreApplication::translate("Window_Three", "TAX RATE:", nullptr));
    label_periodicity_of->setText(
        QCoreApplication::translate("Window_Three", "PERIODICITY OF", nullptr));
    label_with_list->setText(QCoreApplication::translate(
        "Window_Three", "WITHDRAWAL LIST:", nullptr));
    label_add_with->setText(QCoreApplication::translate(
        "Window_Three", "ADD WITHDRAWAL:", nullptr));
    label_sum_2->setText(
        QCoreApplication::translate("Window_Three", "SUM:", nullptr));
    label_n_month2->setText(
        QCoreApplication::translate("Window_Three", "N MONTH:", nullptr));
    label_output_data->setText(QCoreApplication::translate(
        "Window_Three", "        OUTPUT DATA:", nullptr));
    checkbox_capitalization->setText(QCoreApplication::translate(
        "Window_Three", "CAPITALIZATION OF", nullptr));
    label_repl_list->setText(QCoreApplication::translate(
        "Window_Three", "REPLENISHMENT  LIST:", nullptr));
    label_sum->setText(
        QCoreApplication::translate("Window_Three", "SUM:", nullptr));
    label_n_month->setText(
        QCoreApplication::translate("Window_Three", "N MONTH:", nullptr));
    label_accrued_int->setText(QCoreApplication::translate(
        "Window_Three", "ACCRUED INTEREST:", nullptr));
    label_tax_amount->setText(
        QCoreApplication::translate("Window_Three", "TAX AMOUNT:", nullptr));
    label_deposit_amount_2->setText(QCoreApplication::translate(
        "Window_Three", "DEPOSIT AMOUNT:", nullptr));
    button_calculate->setText(
        QCoreApplication::translate("Window_Three", "CALCULATE", nullptr));
    label_line->setText(QString());
    label_by_the_end->setText(
        QCoreApplication::translate("Window_Three", "BY THE END:", nullptr));
    button_plus->setText(
        QCoreApplication::translate("Window_Three", "+", nullptr));
    label_add_repl->setText(QCoreApplication::translate(
        "Window_Three", "ADD REPLENISHMENT:", nullptr));
    label_payments->setText(QCoreApplication::translate(
        "Window_Three", "PAYMENTS (MONTHS):", nullptr));
    label_interest->setText(
        QCoreApplication::translate("Window_Three", "INTEREST:", nullptr));
    button_plus2->setText(
        QCoreApplication::translate("Window_Three", "+", nullptr));
    label_months->setText(
        QCoreApplication::translate("Window_Three", "(MONTHS):", nullptr));
    label->setText(QString());
  }  // retranslateUi
};

namespace Ui {
class Window_Three : public Ui_Window_Three {};
}  // namespace Ui

QT_END_NAMESPACE

#endif  // UI_WINDOW_THREE_H
