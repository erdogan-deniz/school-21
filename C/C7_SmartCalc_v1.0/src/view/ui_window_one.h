/********************************************************************************
** Form generated from reading UI file 'window_one.ui'
**
** Created by: Qt User Interface Compiler version 6.5.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINDOW_ONE_H
#define UI_WINDOW_ONE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_Window_One {
 public:
  QCustomPlot *plot;
  QLabel *Result;
  QPushButton *button_1;
  QPushButton *button_4;
  QPushButton *button_2;
  QPushButton *button_3;
  QPushButton *button_6;
  QPushButton *button_5;
  QPushButton *button_7;
  QPushButton *button_8;
  QPushButton *button_9;
  QPushButton *button_0;
  QPushButton *button_point;
  QPushButton *button_rb;
  QPushButton *button_lb;
  QPushButton *button_x;
  QPushButton *button_plus;
  QPushButton *button_mult;
  QPushButton *button_pow;
  QPushButton *button_minus;
  QPushButton *button_mod;
  QPushButton *button_div;
  QPushButton *button_sin;
  QPushButton *button_cos;
  QPushButton *button_tan;
  QPushButton *button_asin;
  QPushButton *button_atan;
  QPushButton *button_acos;
  QPushButton *button_sqrt;
  QPushButton *button_log;
  QPushButton *button_ln;
  QPushButton *button_eq;
  QPushButton *button_clear;
  QLineEdit *line_x;
  QLabel *label_x_eq;
  QLabel *label_x_in;
  QLabel *label_points_2;
  QLabel *label_rb_2;
  QLineEdit *line_x_from;
  QLineEdit *line_x_to;
  QLabel *label_rb;
  QLineEdit *line_y_to;
  QLabel *label_y_in;
  QLineEdit *line_y_from;
  QLabel *label_points;
  QLabel *label_background;

  void setupUi(QWidget *Window_One) {
    if (Window_One->objectName().isEmpty())
      Window_One->setObjectName("Window_One");
    Window_One->resize(1600, 900);
    plot = new QCustomPlot(Window_One);
    plot->setObjectName("plot");
    plot->setEnabled(false);
    plot->setGeometry(QRect(1020, 340, 560, 485));
    Result = new QLabel(Window_One);
    Result->setObjectName("Result");
    Result->setGeometry(QRect(10, 10, 1580, 100));
    QFont font;
    font.setFamilies({QString::fromUtf8("Nasalization")});
    font.setPointSize(28);
    font.setBold(false);
    font.setItalic(false);
    Result->setFont(font);
    Result->setStyleSheet(
        QString::fromUtf8("    border-style: outset;\n"
                          "    border-width: 4px;\n"
                          "    border-radius: 10px;\n"
                          "    border-color: black;\n"
                          "    min-width: 10em;\n"
                          "	background-color: Azure;"));
    button_1 = new QPushButton(Window_One);
    button_1->setObjectName("button_1");
    button_1->setGeometry(QRect(20, 420, 75, 75));
    QFont font1;
    font1.setFamilies({QString::fromUtf8("Nasalization")});
    font1.setPointSize(30);
    button_1->setFont(font1);
    button_1->setStyleSheet(QString::fromUtf8(
        "QPushButton {\n"
        "   border: 1px solid gray;\n"
        "}\n"
        "QPushButton:pressed {\n"
        "    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
        "                                      stop: 0 #dadbde, stop: 1 "
        "#f6f7fa);\n"
        "}"));
    button_4 = new QPushButton(Window_One);
    button_4->setObjectName("button_4");
    button_4->setGeometry(QRect(20, 500, 75, 75));
    button_4->setFont(font1);
    button_4->setStyleSheet(QString::fromUtf8(
        "QPushButton {\n"
        "   border: 1px solid gray;\n"
        "}\n"
        "QPushButton:pressed {\n"
        "    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
        "                                      stop: 0 #dadbde, stop: 1 "
        "#f6f7fa);\n"
        "}"));
    button_2 = new QPushButton(Window_One);
    button_2->setObjectName("button_2");
    button_2->setGeometry(QRect(100, 420, 75, 75));
    button_2->setFont(font1);
    button_2->setStyleSheet(QString::fromUtf8(
        "QPushButton {\n"
        "   border: 1px solid gray;\n"
        "}\n"
        "QPushButton:pressed {\n"
        "    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
        "                                      stop: 0 #dadbde, stop: 1 "
        "#f6f7fa);\n"
        "}"));
    button_3 = new QPushButton(Window_One);
    button_3->setObjectName("button_3");
    button_3->setGeometry(QRect(180, 420, 75, 75));
    button_3->setFont(font1);
    button_3->setStyleSheet(QString::fromUtf8(
        "QPushButton {\n"
        "   border: 1px solid gray;\n"
        "}\n"
        "QPushButton:pressed {\n"
        "    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
        "                                      stop: 0 #dadbde, stop: 1 "
        "#f6f7fa);\n"
        "}"));
    button_6 = new QPushButton(Window_One);
    button_6->setObjectName("button_6");
    button_6->setGeometry(QRect(180, 500, 75, 75));
    button_6->setFont(font1);
    button_6->setStyleSheet(QString::fromUtf8(
        "QPushButton {\n"
        "   border: 1px solid gray;\n"
        "}\n"
        "QPushButton:pressed {\n"
        "    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
        "                                      stop: 0 #dadbde, stop: 1 "
        "#f6f7fa);\n"
        "}"));
    button_5 = new QPushButton(Window_One);
    button_5->setObjectName("button_5");
    button_5->setGeometry(QRect(100, 500, 75, 75));
    button_5->setFont(font1);
    button_5->setStyleSheet(QString::fromUtf8(
        "QPushButton {\n"
        "   border: 1px solid gray;\n"
        "}\n"
        "QPushButton:pressed {\n"
        "    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
        "                                      stop: 0 #dadbde, stop: 1 "
        "#f6f7fa);\n"
        "}"));
    button_7 = new QPushButton(Window_One);
    button_7->setObjectName("button_7");
    button_7->setGeometry(QRect(20, 580, 75, 75));
    button_7->setFont(font1);
    button_7->setStyleSheet(QString::fromUtf8(
        "QPushButton {\n"
        "   border: 1px solid gray;\n"
        "}\n"
        "QPushButton:pressed {\n"
        "    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
        "                                      stop: 0 #dadbde, stop: 1 "
        "#f6f7fa);\n"
        "}"));
    button_8 = new QPushButton(Window_One);
    button_8->setObjectName("button_8");
    button_8->setGeometry(QRect(100, 580, 75, 75));
    button_8->setFont(font1);
    button_8->setStyleSheet(QString::fromUtf8(
        "QPushButton {\n"
        "   border: 1px solid gray;\n"
        "}\n"
        "QPushButton:pressed {\n"
        "    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
        "                                      stop: 0 #dadbde, stop: 1 "
        "#f6f7fa);\n"
        "}"));
    button_9 = new QPushButton(Window_One);
    button_9->setObjectName("button_9");
    button_9->setGeometry(QRect(180, 580, 75, 75));
    button_9->setFont(font1);
    button_9->setStyleSheet(QString::fromUtf8(
        "QPushButton {\n"
        "   border: 1px solid gray;\n"
        "}\n"
        "QPushButton:pressed {\n"
        "    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
        "                                      stop: 0 #dadbde, stop: 1 "
        "#f6f7fa);\n"
        "}"));
    button_0 = new QPushButton(Window_One);
    button_0->setObjectName("button_0");
    button_0->setGeometry(QRect(20, 660, 155, 75));
    button_0->setFont(font1);
    button_0->setStyleSheet(QString::fromUtf8(
        "QPushButton {\n"
        "   border: 1px solid gray;\n"
        "}\n"
        "QPushButton:pressed {\n"
        "    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
        "                                      stop: 0 #dadbde, stop: 1 "
        "#f6f7fa);\n"
        "}"));
    button_point = new QPushButton(Window_One);
    button_point->setObjectName("button_point");
    button_point->setGeometry(QRect(180, 660, 75, 75));
    button_point->setFont(font1);
    button_point->setStyleSheet(QString::fromUtf8("background-color: #400261"));
    button_rb = new QPushButton(Window_One);
    button_rb->setObjectName("button_rb");
    button_rb->setGeometry(QRect(100, 340, 75, 75));
    button_rb->setFont(font1);
    button_rb->setStyleSheet(QString::fromUtf8("background-color: #6F07A6"));
    button_lb = new QPushButton(Window_One);
    button_lb->setObjectName("button_lb");
    button_lb->setGeometry(QRect(20, 340, 75, 75));
    button_lb->setFont(font1);
    button_lb->setStyleSheet(QString::fromUtf8("background-color: #6F07A6"));
    button_x = new QPushButton(Window_One);
    button_x->setObjectName("button_x");
    button_x->setGeometry(QRect(420, 660, 75, 75));
    button_x->setFont(font1);
    button_x->setStyleSheet(QString::fromUtf8("background-color: #400261"));
    button_plus = new QPushButton(Window_One);
    button_plus->setObjectName("button_plus");
    button_plus->setGeometry(QRect(180, 340, 75, 75));
    button_plus->setFont(font1);
    button_plus->setStyleSheet(QString::fromUtf8("background-color: #6F07A6"));
    button_mult = new QPushButton(Window_One);
    button_mult->setObjectName("button_mult");
    button_mult->setGeometry(QRect(260, 420, 75, 75));
    button_mult->setFont(font1);
    button_mult->setStyleSheet(QString::fromUtf8("background-color: #5E048D"));
    button_pow = new QPushButton(Window_One);
    button_pow->setObjectName("button_pow");
    button_pow->setGeometry(QRect(260, 580, 75, 75));
    button_pow->setFont(font1);
    button_pow->setStyleSheet(QString::fromUtf8("background-color: #4A036F"));
    button_minus = new QPushButton(Window_One);
    button_minus->setObjectName("button_minus");
    button_minus->setGeometry(QRect(260, 340, 75, 75));
    button_minus->setFont(font1);
    button_minus->setStyleSheet(QString::fromUtf8("background-color: #6F07A6"));
    button_mod = new QPushButton(Window_One);
    button_mod->setObjectName("button_mod");
    button_mod->setGeometry(QRect(260, 660, 75, 75));
    QFont font2;
    font2.setFamilies({QString::fromUtf8("Nasalization")});
    font2.setPointSize(22);
    button_mod->setFont(font2);
    button_mod->setStyleSheet(QString::fromUtf8("background-color: #400261"));
    button_div = new QPushButton(Window_One);
    button_div->setObjectName("button_div");
    button_div->setGeometry(QRect(260, 500, 75, 75));
    button_div->setFont(font1);
    button_div->setStyleSheet(QString::fromUtf8("background-color: #54037E"));
    button_sin = new QPushButton(Window_One);
    button_sin->setObjectName("button_sin");
    button_sin->setGeometry(QRect(340, 340, 75, 75));
    QFont font3;
    font3.setFamilies({QString::fromUtf8("Nasalization")});
    font3.setPointSize(25);
    button_sin->setFont(font3);
    button_sin->setStyleSheet(QString::fromUtf8("background-color: #6F07A6"));
    button_cos = new QPushButton(Window_One);
    button_cos->setObjectName("button_cos");
    button_cos->setGeometry(QRect(340, 420, 75, 75));
    button_cos->setFont(font3);
    button_cos->setStyleSheet(QString::fromUtf8("background-color: #5E048D"));
    button_tan = new QPushButton(Window_One);
    button_tan->setObjectName("button_tan");
    button_tan->setGeometry(QRect(340, 500, 75, 75));
    button_tan->setFont(font3);
    button_tan->setStyleSheet(QString::fromUtf8("background-color: #54037E"));
    button_asin = new QPushButton(Window_One);
    button_asin->setObjectName("button_asin");
    button_asin->setGeometry(QRect(420, 340, 75, 75));
    button_asin->setFont(font2);
    button_asin->setStyleSheet(QString::fromUtf8("background-color: #6F07A6"));
    button_atan = new QPushButton(Window_One);
    button_atan->setObjectName("button_atan");
    button_atan->setGeometry(QRect(420, 500, 75, 75));
    button_atan->setFont(font2);
    button_atan->setStyleSheet(QString::fromUtf8("background-color: #54037E"));
    button_acos = new QPushButton(Window_One);
    button_acos->setObjectName("button_acos");
    button_acos->setGeometry(QRect(420, 420, 75, 75));
    button_acos->setFont(font2);
    button_acos->setStyleSheet(QString::fromUtf8("background-color: #5E048D"));
    button_sqrt = new QPushButton(Window_One);
    button_sqrt->setObjectName("button_sqrt");
    button_sqrt->setGeometry(QRect(420, 580, 75, 75));
    button_sqrt->setFont(font2);
    button_sqrt->setStyleSheet(QString::fromUtf8("background-color: #4A036F"));
    button_log = new QPushButton(Window_One);
    button_log->setObjectName("button_log");
    button_log->setGeometry(QRect(340, 580, 75, 75));
    button_log->setFont(font3);
    button_log->setStyleSheet(QString::fromUtf8("background-color: #4A036F"));
    button_ln = new QPushButton(Window_One);
    button_ln->setObjectName("button_ln");
    button_ln->setGeometry(QRect(340, 660, 75, 75));
    button_ln->setFont(font3);
    button_ln->setStyleSheet(QString::fromUtf8("background-color: #400261"));
    button_eq = new QPushButton(Window_One);
    button_eq->setObjectName("button_eq");
    button_eq->setGeometry(QRect(500, 500, 85, 235));
    button_eq->setFont(font1);
    button_eq->setStyleSheet(QString::fromUtf8("background-color: #B56200"));
    button_clear = new QPushButton(Window_One);
    button_clear->setObjectName("button_clear");
    button_clear->setGeometry(QRect(500, 340, 85, 155));
    button_clear->setFont(font2);
    button_clear->setStyleSheet(QString::fromUtf8("background-color: #6F07A6"));
    line_x = new QLineEdit(Window_One);
    line_x->setObjectName("line_x");
    line_x->setGeometry(QRect(1125, 140, 210, 40));
    line_x->setStyleSheet(
        QString::fromUtf8("    border-style: outset;\n"
                          "    border-width: 2px;\n"
                          "    border-radius: 10px;\n"
                          "    border-color: black;\n"
                          "    font: bold 14px;\n"
                          "    min-width: 10em;\n"
                          "    padding: 6px;\n"
                          "	background-color: Azure;"));
    label_x_eq = new QLabel(Window_One);
    label_x_eq->setObjectName("label_x_eq");
    label_x_eq->setGeometry(QRect(1045, 120, 70, 70));
    QFont font4;
    font4.setFamilies({QString::fromUtf8("Snap ITC")});
    font4.setPointSize(28);
    font4.setBold(false);
    label_x_eq->setFont(font4);
    label_x_eq->setMouseTracking(false);
    label_x_eq->setStyleSheet(QString::fromUtf8("color: purple"));
    label_x_in = new QLabel(Window_One);
    label_x_in->setObjectName("label_x_in");
    label_x_in->setGeometry(QRect(1020, 200, 100, 50));
    label_x_in->setFont(font4);
    label_x_in->setMouseTracking(false);
    label_x_in->setStyleSheet(QString::fromUtf8("color: purple"));
    label_points_2 = new QLabel(Window_One);
    label_points_2->setObjectName("label_points_2");
    label_points_2->setGeometry(QRect(1340, 195, 20, 50));
    label_points_2->setFont(font4);
    label_points_2->setMouseTracking(false);
    label_points_2->setStyleSheet(QString::fromUtf8("color: purple"));
    label_rb_2 = new QLabel(Window_One);
    label_rb_2->setObjectName("label_rb_2");
    label_rb_2->setGeometry(QRect(1570, 200, 20, 50));
    label_rb_2->setFont(font4);
    label_rb_2->setMouseTracking(false);
    label_rb_2->setStyleSheet(QString::fromUtf8("color: purple"));
    line_x_from = new QLineEdit(Window_One);
    line_x_from->setObjectName("line_x_from");
    line_x_from->setGeometry(QRect(1125, 210, 210, 30));
    line_x_from->setStyleSheet(
        QString::fromUtf8("    border-style: outset;\n"
                          "    border-width: 2px;\n"
                          "    border-radius: 10px;\n"
                          "    border-color: black;\n"
                          "    font: bold 14px;\n"
                          "    min-width: 10em;\n"
                          "    padding: 6px;\n"
                          "	background-color: Azure;"));
    line_x_to = new QLineEdit(Window_One);
    line_x_to->setObjectName("line_x_to");
    line_x_to->setGeometry(QRect(1360, 210, 210, 30));
    line_x_to->setStyleSheet(
        QString::fromUtf8("    border-style: outset;\n"
                          "    border-width: 2px;\n"
                          "    border-radius: 10px;\n"
                          "    border-color: black;\n"
                          "    font: bold 14px;\n"
                          "    min-width: 10em;\n"
                          "    padding: 6px;\n"
                          "	background-color: Azure;"));
    label_rb = new QLabel(Window_One);
    label_rb->setObjectName("label_rb");
    label_rb->setGeometry(QRect(1570, 280, 20, 50));
    label_rb->setFont(font4);
    label_rb->setMouseTracking(false);
    label_rb->setStyleSheet(QString::fromUtf8("color: purple"));
    line_y_to = new QLineEdit(Window_One);
    line_y_to->setObjectName("line_y_to");
    line_y_to->setGeometry(QRect(1360, 290, 210, 30));
    line_y_to->setStyleSheet(
        QString::fromUtf8("    border-style: outset;\n"
                          "    border-width: 2px;\n"
                          "    border-radius: 10px;\n"
                          "    border-color: black;\n"
                          "    font: bold 14px;\n"
                          "    min-width: 10em;\n"
                          "    padding: 6px;\n"
                          "	background-color: Azure;"));
    label_y_in = new QLabel(Window_One);
    label_y_in->setObjectName("label_y_in");
    label_y_in->setGeometry(QRect(1020, 280, 100, 50));
    label_y_in->setFont(font4);
    label_y_in->setMouseTracking(false);
    label_y_in->setStyleSheet(QString::fromUtf8("color: purple"));
    line_y_from = new QLineEdit(Window_One);
    line_y_from->setObjectName("line_y_from");
    line_y_from->setGeometry(QRect(1125, 290, 210, 30));
    line_y_from->setStyleSheet(
        QString::fromUtf8("    border-style: outset;\n"
                          "    border-width: 2px;\n"
                          "    border-radius: 10px;\n"
                          "    border-color: black;\n"
                          "    font: bold 14px;\n"
                          "    min-width: 10em;\n"
                          "    padding: 6px;\n"
                          "	background-color: Azure;"));
    label_points = new QLabel(Window_One);
    label_points->setObjectName("label_points");
    label_points->setGeometry(QRect(1340, 275, 20, 50));
    label_points->setFont(font4);
    label_points->setMouseTracking(false);
    label_points->setStyleSheet(QString::fromUtf8("color: purple"));
    label_background = new QLabel(Window_One);
    label_background->setObjectName("label_background");
    label_background->setGeometry(QRect(0, 0, 1600, 900));
    QFont font5;
    font5.setFamilies({QString::fromUtf8("Nasalization")});
    label_background->setFont(font5);
    label_background->setStyleSheet(QString::fromUtf8("color: purple"));
    label_background->setPixmap(
        QPixmap(QString::fromUtf8("images/calculator_background.jpg")));
    label_background->raise();
    plot->raise();
    Result->raise();
    button_1->raise();
    button_4->raise();
    button_2->raise();
    button_3->raise();
    button_6->raise();
    button_5->raise();
    button_7->raise();
    button_8->raise();
    button_9->raise();
    button_0->raise();
    button_point->raise();
    button_rb->raise();
    button_lb->raise();
    button_x->raise();
    button_plus->raise();
    button_mult->raise();
    button_pow->raise();
    button_minus->raise();
    button_mod->raise();
    button_div->raise();
    button_sin->raise();
    button_cos->raise();
    button_tan->raise();
    button_asin->raise();
    button_atan->raise();
    button_acos->raise();
    button_sqrt->raise();
    button_log->raise();
    button_ln->raise();
    button_eq->raise();
    button_clear->raise();
    line_x->raise();
    label_x_eq->raise();
    label_x_in->raise();
    label_points_2->raise();
    label_rb_2->raise();
    line_x_from->raise();
    line_x_to->raise();
    label_rb->raise();
    line_y_to->raise();
    label_y_in->raise();
    line_y_from->raise();
    label_points->raise();

    retranslateUi(Window_One);

    QMetaObject::connectSlotsByName(Window_One);
  }  // setupUi

  void retranslateUi(QWidget *Window_One) {
    Window_One->setWindowTitle(
        QCoreApplication::translate("Window_One", "Form", nullptr));
    Result->setText(QString());
    button_1->setText(QCoreApplication::translate("Window_One", "1", nullptr));
    button_4->setText(QCoreApplication::translate("Window_One", "4", nullptr));
    button_2->setText(QCoreApplication::translate("Window_One", "2", nullptr));
    button_3->setText(QCoreApplication::translate("Window_One", "3", nullptr));
    button_6->setText(QCoreApplication::translate("Window_One", "6", nullptr));
    button_5->setText(QCoreApplication::translate("Window_One", "5", nullptr));
    button_7->setText(QCoreApplication::translate("Window_One", "7", nullptr));
    button_8->setText(QCoreApplication::translate("Window_One", "8", nullptr));
    button_9->setText(QCoreApplication::translate("Window_One", "9", nullptr));
    button_0->setText(QCoreApplication::translate("Window_One", "0", nullptr));
    button_point->setText(
        QCoreApplication::translate("Window_One", ".", nullptr));
    button_rb->setText(QCoreApplication::translate("Window_One", ")", nullptr));
    button_lb->setText(QCoreApplication::translate("Window_One", "(", nullptr));
    button_x->setText(QCoreApplication::translate("Window_One", "x", nullptr));
    button_plus->setText(
        QCoreApplication::translate("Window_One", "+", nullptr));
    button_mult->setText(
        QCoreApplication::translate("Window_One", "*", nullptr));
    button_pow->setText(
        QCoreApplication::translate("Window_One", "^", nullptr));
    button_minus->setText(
        QCoreApplication::translate("Window_One", "-", nullptr));
    button_mod->setText(
        QCoreApplication::translate("Window_One", "mod", nullptr));
    button_div->setText(
        QCoreApplication::translate("Window_One", "/", nullptr));
    button_sin->setText(
        QCoreApplication::translate("Window_One", "sin", nullptr));
    button_cos->setText(
        QCoreApplication::translate("Window_One", "cos", nullptr));
    button_tan->setText(
        QCoreApplication::translate("Window_One", "tan", nullptr));
    button_asin->setText(
        QCoreApplication::translate("Window_One", "asin", nullptr));
    button_atan->setText(
        QCoreApplication::translate("Window_One", "atan", nullptr));
    button_acos->setText(
        QCoreApplication::translate("Window_One", "acos", nullptr));
    button_sqrt->setText(
        QCoreApplication::translate("Window_One", "sqrt", nullptr));
    button_log->setText(
        QCoreApplication::translate("Window_One", "log", nullptr));
    button_ln->setText(
        QCoreApplication::translate("Window_One", "ln", nullptr));
    button_eq->setText(QCoreApplication::translate("Window_One", "=", nullptr));
    button_clear->setText(
        QCoreApplication::translate("Window_One", "clear", nullptr));
    label_x_eq->setText(
        QCoreApplication::translate("Window_One", "X = ", nullptr));
    label_x_in->setText(
        QCoreApplication::translate("Window_One", "X \342\210\210[", nullptr));
    label_points_2->setText(
        QCoreApplication::translate("Window_One", ":", nullptr));
    label_rb_2->setText(
        QCoreApplication::translate("Window_One", "]", nullptr));
    label_rb->setText(QCoreApplication::translate("Window_One", "]", nullptr));
    label_y_in->setText(
        QCoreApplication::translate("Window_One", "Y \342\210\210[", nullptr));
    label_points->setText(
        QCoreApplication::translate("Window_One", ":", nullptr));
    label_background->setText(QString());
  }  // retranslateUi
};

namespace Ui {
class Window_One : public Ui_Window_One {};
}  // namespace Ui

QT_END_NAMESPACE

#endif  // UI_WINDOW_ONE_H
