/********************************************************************************
** Form generated from reading UI file 'start_window.ui'
**
** Created by: Qt User Interface Compiler version 6.5.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_START_WINDOW_H
#define UI_START_WINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Start_Window {
 public:
  QWidget *centralwidget;
  QPushButton *Calculator_Button;
  QPushButton *Credit_Button;
  QPushButton *Deposit_Button;
  QLabel *label;
  QMenuBar *menubar;
  QMenu *menu_s21_calculator;
  QStatusBar *statusbar;

  void setupUi(QMainWindow *Start_Window) {
    if (Start_Window->objectName().isEmpty())
      Start_Window->setObjectName("Start_Window");
    Start_Window->resize(1600, 900);
    Start_Window->setAcceptDrops(false);
    centralwidget = new QWidget(Start_Window);
    centralwidget->setObjectName("centralwidget");
    Calculator_Button = new QPushButton(centralwidget);
    Calculator_Button->setObjectName("Calculator_Button");
    Calculator_Button->setEnabled(true);
    Calculator_Button->setGeometry(QRect(550, 100, 500, 150));
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(
        Calculator_Button->sizePolicy().hasHeightForWidth());
    Calculator_Button->setSizePolicy(sizePolicy);
    QFont font;
    font.setFamilies({QString::fromUtf8("Cooper Black")});
    font.setPointSize(36);
    font.setBold(false);
    font.setItalic(false);
    font.setUnderline(false);
    font.setStrikeOut(false);
    Calculator_Button->setFont(font);
    Calculator_Button->setCursor(QCursor(Qt::PointingHandCursor));
    Calculator_Button->setAcceptDrops(false);
    Calculator_Button->setLayoutDirection(Qt::LeftToRight);
    Calculator_Button->setAutoFillBackground(false);
    Calculator_Button->setStyleSheet(QString::fromUtf8(""));
    QIcon icon;
    QString iconThemeName = QString::fromUtf8("applications-development");
    if (QIcon::hasThemeIcon(iconThemeName)) {
      icon = QIcon::fromTheme(iconThemeName);
    } else {
      icon.addFile(QString::fromUtf8("."), QSize(), QIcon::Normal, QIcon::Off);
    }
    Calculator_Button->setIcon(icon);
    Credit_Button = new QPushButton(centralwidget);
    Credit_Button->setObjectName("Credit_Button");
    Credit_Button->setGeometry(QRect(550, 350, 500, 150));
    QFont font1;
    font1.setFamilies({QString::fromUtf8("Cooper Black")});
    font1.setPointSize(36);
    font1.setStyleStrategy(QFont::PreferDefault);
    Credit_Button->setFont(font1);
    Credit_Button->setCursor(QCursor(Qt::PointingHandCursor));
    Deposit_Button = new QPushButton(centralwidget);
    Deposit_Button->setObjectName("Deposit_Button");
    Deposit_Button->setGeometry(QRect(550, 600, 500, 150));
    QFont font2;
    font2.setFamilies({QString::fromUtf8("Cooper Black")});
    font2.setPointSize(36);
    Deposit_Button->setFont(font2);
    Deposit_Button->setCursor(QCursor(Qt::PointingHandCursor));
    Deposit_Button->setMouseTracking(false);
    QIcon icon1;
    iconThemeName = QString::fromUtf8("call-start");
    if (QIcon::hasThemeIcon(iconThemeName)) {
      icon1 = QIcon::fromTheme(iconThemeName);
    } else {
      icon1.addFile(QString::fromUtf8("."), QSize(), QIcon::Normal, QIcon::Off);
    }
    Deposit_Button->setIcon(icon1);
    label = new QLabel(centralwidget);
    label->setObjectName("label");
    label->setGeometry(QRect(-10, -10, 1600, 900));
    label->setPixmap(
        QPixmap(QString::fromUtf8("images/start_window_background.jpg")));
    Start_Window->setCentralWidget(centralwidget);
    label->raise();
    Calculator_Button->raise();
    Credit_Button->raise();
    Deposit_Button->raise();
    menubar = new QMenuBar(Start_Window);
    menubar->setObjectName("menubar");
    menubar->setGeometry(QRect(0, 0, 1600, 21));
    menu_s21_calculator = new QMenu(menubar);
    menu_s21_calculator->setObjectName("menu_s21_calculator");
    Start_Window->setMenuBar(menubar);
    statusbar = new QStatusBar(Start_Window);
    statusbar->setObjectName("statusbar");
    Start_Window->setStatusBar(statusbar);

    menubar->addAction(menu_s21_calculator->menuAction());

    retranslateUi(Start_Window);

    QMetaObject::connectSlotsByName(Start_Window);
  }  // setupUi

  void retranslateUi(QMainWindow *Start_Window) {
    Start_Window->setWindowTitle(
        QCoreApplication::translate("Start_Window", "Start_Window", nullptr));
    Calculator_Button->setText(
        QCoreApplication::translate("Start_Window", "Calculator", nullptr));
    Credit_Button->setText(QCoreApplication::translate(
        "Start_Window", "Credit calculator", nullptr));
    Deposit_Button->setText(QCoreApplication::translate(
        "Start_Window", "Deposit calculator", nullptr));
    label->setText(QString());
    menu_s21_calculator->setTitle(
        QCoreApplication::translate("Start_Window", "s21_calculator", nullptr));
  }  // retranslateUi
};

namespace Ui {
class Start_Window : public Ui_Start_Window {};
}  // namespace Ui

QT_END_NAMESPACE

#endif  // UI_START_WINDOW_H
