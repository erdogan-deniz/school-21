/********************************************************************************
** Form generated from reading UI file 'window_two.ui'
**
** Created by: Qt User Interface Compiler version 6.5.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINDOW_TWO_H
#define UI_WINDOW_TWO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Window_Two {
 public:
  QLabel *label_input_data;
  QLineEdit *line_total_credit_amount;
  QLabel *label_total_credit_amount;
  QLineEdit *line_term;
  QLabel *label_term;
  QLabel *label_interest_rate;
  QLineEdit *line_interest_rate;
  QLabel *label_type;
  QRadioButton *box_annuity;
  QRadioButton *box_differentiated;
  QLabel *output_data;
  QLabel *label_overpayment_on_credit;
  QLineEdit *line_overpayment_on_credit;
  QLineEdit *line_total_payment;
  QLabel *label_total_payment;
  QLabel *label_monthly_payments;
  QLabel *label_line;
  QPushButton *button_calculate;
  QLineEdit *line_monthly_payments;
  QLabel *label_bigger_then;
  QLabel *label_bigger_then2;
  QLabel *label_bigger_then3;
  QLabel *label_payments;
  QLabel *label_background;
  QListWidget *list_payments;

  void setupUi(QWidget *Window_Two) {
    if (Window_Two->objectName().isEmpty())
      Window_Two->setObjectName("Window_Two");
    Window_Two->resize(1600, 900);
    label_input_data = new QLabel(Window_Two);
    label_input_data->setObjectName("label_input_data");
    label_input_data->setGeometry(QRect(0, 0, 800, 110));
    QFont font;
    font.setFamilies({QString::fromUtf8("Palatino Linotype")});
    font.setPointSize(36);
    font.setBold(false);
    label_input_data->setFont(font);
    label_input_data->setStyleSheet(
        QString::fromUtf8("background-color: #060ADE;\n"
                          "color: White;\n"
                          "border-style: outset;\n"
                          "border-width: 2px;\n"
                          "border-color: black;\n"
                          "border-top: 0;\n"
                          "border-right: 0; \n"
                          "border-bottom: 2px solid;\n"
                          " border-left: 0"));
    line_total_credit_amount = new QLineEdit(Window_Two);
    line_total_credit_amount->setObjectName("line_total_credit_amount");
    line_total_credit_amount->setGeometry(QRect(40, 215, 240, 40));
    QFont font1;
    font1.setFamilies({QString::fromUtf8("Cascadia Code Light")});
    font1.setPointSize(20);
    line_total_credit_amount->setFont(font1);
    line_total_credit_amount->setStyleSheet(
        QString::fromUtf8("    border-style: outset;\n"
                          "    border-width: 2px;\n"
                          "    border-radius: 10px;\n"
                          "    border-color: black;\n"
                          "	background-color: rgba(0, 0, 0, 0.1);"));
    label_total_credit_amount = new QLabel(Window_Two);
    label_total_credit_amount->setObjectName("label_total_credit_amount");
    label_total_credit_amount->setGeometry(QRect(40, 160, 440, 55));
    QFont font2;
    font2.setFamilies({QString::fromUtf8("Miriam Mono CLM")});
    font2.setPointSize(28);
    label_total_credit_amount->setFont(font2);
    line_term = new QLineEdit(Window_Two);
    line_term->setObjectName("line_term");
    line_term->setGeometry(QRect(40, 350, 240, 40));
    line_term->setFont(font1);
    line_term->setStyleSheet(
        QString::fromUtf8("    border-style: outset;\n"
                          "    border-width: 2px;\n"
                          "    border-radius: 10px;\n"
                          "    border-color: black;\n"
                          "	background-color: rgba(0, 0, 0, 0.1);"));
    label_term = new QLabel(Window_Two);
    label_term->setObjectName("label_term");
    label_term->setGeometry(QRect(40, 300, 310, 55));
    label_term->setFont(font2);
    label_interest_rate = new QLabel(Window_Two);
    label_interest_rate->setObjectName("label_interest_rate");
    label_interest_rate->setGeometry(QRect(40, 435, 350, 55));
    label_interest_rate->setFont(font2);
    line_interest_rate = new QLineEdit(Window_Two);
    line_interest_rate->setObjectName("line_interest_rate");
    line_interest_rate->setGeometry(QRect(40, 490, 240, 40));
    line_interest_rate->setFont(font1);
    line_interest_rate->setStyleSheet(
        QString::fromUtf8("    border-style: outset;\n"
                          "    border-width: 2px;\n"
                          "    border-radius: 10px;\n"
                          "    border-color: black;\n"
                          "	background-color: rgba(0, 0, 0, 0.1);"));
    label_type = new QLabel(Window_Two);
    label_type->setObjectName("label_type");
    label_type->setGeometry(QRect(40, 575, 110, 55));
    label_type->setFont(font2);
    box_annuity = new QRadioButton(Window_Two);
    box_annuity->setObjectName("box_annuity");
    box_annuity->setGeometry(QRect(40, 635, 180, 55));
    box_annuity->setFont(font2);
    box_annuity->setStyleSheet(QString::fromUtf8(""));
    box_differentiated = new QRadioButton(Window_Two);
    box_differentiated->setObjectName("box_differentiated");
    box_differentiated->setGeometry(QRect(250, 635, 330, 55));
    box_differentiated->setFont(font2);
    output_data = new QLabel(Window_Two);
    output_data->setObjectName("output_data");
    output_data->setGeometry(QRect(800, 0, 800, 110));
    QFont font3;
    font3.setFamilies({QString::fromUtf8("Palatino Linotype")});
    font3.setPointSize(36);
    output_data->setFont(font3);
    output_data->setStyleSheet(
        QString::fromUtf8("background-color: #8906DE;\n"
                          "color: White;\n"
                          "border-style: outset;\n"
                          "border-width: 2px;\n"
                          "border-color: black;\n"
                          "border-top: 0;\n"
                          "border-right: 0; \n"
                          "border-bottom: 2px solid;\n"
                          " border-left: 0"));
    label_overpayment_on_credit = new QLabel(Window_Two);
    label_overpayment_on_credit->setObjectName("label_overpayment_on_credit");
    label_overpayment_on_credit->setGeometry(QRect(840, 265, 480, 55));
    label_overpayment_on_credit->setFont(font2);
    line_overpayment_on_credit = new QLineEdit(Window_Two);
    line_overpayment_on_credit->setObjectName("line_overpayment_on_credit");
    line_overpayment_on_credit->setGeometry(QRect(840, 320, 300, 40));
    line_overpayment_on_credit->setFont(font1);
    line_overpayment_on_credit->setStyleSheet(
        QString::fromUtf8("    border-style: outset;\n"
                          "    border-width: 2px;\n"
                          "    border-radius: 10px;\n"
                          "    border-color: black;\n"
                          "	background-color: rgba(0, 0, 0, 0.1);\n"
                          ""));
    line_total_payment = new QLineEdit(Window_Two);
    line_total_payment->setObjectName("line_total_payment");
    line_total_payment->setGeometry(QRect(840, 430, 300, 40));
    line_total_payment->setFont(font1);
    line_total_payment->setStyleSheet(
        QString::fromUtf8("    border-style: outset;\n"
                          "    border-width: 2px;\n"
                          "    border-radius: 10px;\n"
                          "    border-color: black;\n"
                          "	background-color: rgba(0, 0, 0, 0.1);"));
    label_total_payment = new QLabel(Window_Two);
    label_total_payment->setObjectName("label_total_payment");
    label_total_payment->setGeometry(QRect(840, 375, 300, 55));
    label_total_payment->setFont(font2);
    label_monthly_payments = new QLabel(Window_Two);
    label_monthly_payments->setObjectName("label_monthly_payments");
    label_monthly_payments->setGeometry(QRect(840, 160, 590, 55));
    label_monthly_payments->setFont(font2);
    label_line = new QLabel(Window_Two);
    label_line->setObjectName("label_line");
    label_line->setGeometry(QRect(798, 0, 4, 900));
    label_line->setStyleSheet(QString::fromUtf8("background-color: Black;"));
    button_calculate = new QPushButton(Window_Two);
    button_calculate->setObjectName("button_calculate");
    button_calculate->setGeometry(QRect(525, 450, 200, 65));
    QFont font4;
    font4.setFamilies({QString::fromUtf8("Segoe UI Semilight")});
    font4.setPointSize(24);
    button_calculate->setFont(font4);
    button_calculate->setCursor(QCursor(Qt::PointingHandCursor));
    button_calculate->setStyleSheet(
        QString::fromUtf8("    border-style: outset;\n"
                          "    border-width: 2px;\n"
                          "    border-radius: 10px;\n"
                          "    border-color: black;\n"
                          "	background-color: rgba(0, 0, 0, 0.1);"));
    line_monthly_payments = new QLineEdit(Window_Two);
    line_monthly_payments->setObjectName("line_monthly_payments");
    line_monthly_payments->setGeometry(QRect(840, 215, 300, 40));
    line_monthly_payments->setFont(font1);
    line_monthly_payments->setStyleSheet(
        QString::fromUtf8("border-style: outset;\n"
                          "border-width: 2px;\n"
                          "border-radius: 10px;\n"
                          "border-color: black;\n"
                          "background-color: rgba(0, 0, 0, 0.1);"));
    label_bigger_then = new QLabel(Window_Two);
    label_bigger_then->setObjectName("label_bigger_then");
    label_bigger_then->setGeometry(QRect(40, 260, 320, 25));
    QFont font5;
    font5.setPointSize(12);
    label_bigger_then->setFont(font5);
    label_bigger_then2 = new QLabel(Window_Two);
    label_bigger_then2->setObjectName("label_bigger_then2");
    label_bigger_then2->setGeometry(QRect(40, 395, 220, 25));
    QFont font6;
    font6.setPointSize(11);
    label_bigger_then2->setFont(font6);
    label_bigger_then3 = new QLabel(Window_Two);
    label_bigger_then3->setObjectName("label_bigger_then3");
    label_bigger_then3->setGeometry(QRect(40, 535, 220, 25));
    label_bigger_then3->setFont(font6);
    label_payments = new QLabel(Window_Two);
    label_payments->setObjectName("label_payments");
    label_payments->setGeometry(QRect(840, 485, 191, 55));
    label_payments->setFont(font2);
    label_background = new QLabel(Window_Two);
    label_background->setObjectName("label_background");
    label_background->setGeometry(QRect(30, -10, 1600, 900));
    label_background->setPixmap(
        QPixmap(QString::fromUtf8("images/window_two_background.jpg")));
    list_payments = new QListWidget(Window_Two);
    list_payments->setObjectName("list_payments");
    list_payments->setGeometry(QRect(840, 540, 600, 275));
    QFont font7;
    font7.setFamilies({QString::fromUtf8("Noto Serif Lao")});
    font7.setPointSize(18);
    list_payments->setFont(font7);
    list_payments->setStyleSheet(
        QString::fromUtf8("border-style: outset;\n"
                          "border-width: 2px;\n"
                          "border-radius: 10px;\n"
                          "border-color: black;\n"
                          "background-color: rgba(0, 0, 0, 0.1);"));
    label_background->raise();
    label_input_data->raise();
    line_total_credit_amount->raise();
    label_total_credit_amount->raise();
    line_term->raise();
    label_term->raise();
    label_interest_rate->raise();
    line_interest_rate->raise();
    label_type->raise();
    box_annuity->raise();
    box_differentiated->raise();
    output_data->raise();
    label_overpayment_on_credit->raise();
    line_overpayment_on_credit->raise();
    line_total_payment->raise();
    label_total_payment->raise();
    label_monthly_payments->raise();
    label_line->raise();
    button_calculate->raise();
    line_monthly_payments->raise();
    label_bigger_then->raise();
    label_bigger_then2->raise();
    label_bigger_then3->raise();
    label_payments->raise();
    list_payments->raise();

    retranslateUi(Window_Two);

    QMetaObject::connectSlotsByName(Window_Two);
  }  // setupUi

  void retranslateUi(QWidget *Window_Two) {
    Window_Two->setWindowTitle(
        QCoreApplication::translate("Window_Two", "Form", nullptr));
    label_input_data->setText(QCoreApplication::translate(
        "Window_Two", "                    INPUT DATA:", nullptr));
    line_total_credit_amount->setText(QString());
    label_total_credit_amount->setText(QCoreApplication::translate(
        "Window_Two", "TOTAL CREDIT AMOUNT:", nullptr));
    line_term->setText(QString());
    label_term->setText(
        QCoreApplication::translate("Window_Two", "TERM (MONTHS):", nullptr));
    label_interest_rate->setText(
        QCoreApplication::translate("Window_Two", "INTEREST RATE:", nullptr));
    line_interest_rate->setText(QString());
    label_type->setText(
        QCoreApplication::translate("Window_Two", "TYPE:", nullptr));
    box_annuity->setText(
        QCoreApplication::translate("Window_Two", "ANNUITY", nullptr));
    box_differentiated->setText(
        QCoreApplication::translate("Window_Two", "DIFFERENTIATED", nullptr));
    output_data->setText(QCoreApplication::translate(
        "Window_Two", "                    OUTPUT DATA:", nullptr));
    label_overpayment_on_credit->setText(QCoreApplication::translate(
        "Window_Two", "OVERPAYMENT ON CREDIT:", nullptr));
    line_overpayment_on_credit->setText(QString());
    line_total_payment->setText(QString());
    label_total_payment->setText(
        QCoreApplication::translate("Window_Two", "TOTAL PAYMENT:", nullptr));
    label_monthly_payments->setText(QCoreApplication::translate(
        "Window_Two", "MONTHLY PAYMENTS (average):", nullptr));
    label_line->setText(QString());
    button_calculate->setText(
        QCoreApplication::translate("Window_Two", "CALCULATE", nullptr));
    line_monthly_payments->setText(QString());
    label_bigger_then->setText(QCoreApplication::translate(
        "Window_Two", "(* more then 10 and less then 1 000 000 000)", nullptr));
    label_bigger_then2->setText(QCoreApplication::translate(
        "Window_Two", "(* more then 0 and less then 600)", nullptr));
    label_bigger_then3->setText(QCoreApplication::translate(
        "Window_Two", "(* more then 0 and less then 300)", nullptr));
    label_payments->setText(
        QCoreApplication::translate("Window_Two", "PAYMENTS:", nullptr));
    label_background->setText(QString());
  }  // retranslateUi
};

namespace Ui {
class Window_Two : public Ui_Window_Two {};
}  // namespace Ui

QT_END_NAMESPACE

#endif  // UI_WINDOW_TWO_H
