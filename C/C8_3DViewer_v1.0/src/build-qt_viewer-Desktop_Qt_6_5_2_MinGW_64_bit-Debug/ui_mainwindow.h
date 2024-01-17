/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.5.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include <miwidget.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QPushButton *pushButton_4;
    QComboBox *comboBox_5;
    QComboBox *comboBox;
    QComboBox *comboBox_4;
    QSlider *horizontalSlider_7;
    QLabel *label_10;
    QLabel *label_4;
    QLabel *label_8;
    QSlider *horizontalSlider_3;
    QPushButton *pushButton_6;
    QLabel *label;
    QSlider *horizontalSlider_6;
    QSlider *horizontalSlider_2;
    QLineEdit *lineEdit;
    QPushButton *pushButton_7;
    QLabel *label_5;
    QLabel *label_3;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit_2;
    QLabel *label_2;
    QPushButton *pushButton_5;
    QPushButton *pushButton;
    QSlider *horizontalSlider;
    QLabel *label_9;
    miwidget *widget;
    QLabel *label_7;
    QSlider *horizontalSlider_5;
    QLabel *label_6;
    QSlider *horizontalSlider_4;
    QPushButton *bZoom_it;
    QPushButton *bZoom_out;
    QPushButton *pushButton_3;
    QPushButton *pushButton_2;
    QComboBox *comboBox_2;
    QComboBox *comboBox_3;
    QPushButton *btn_settings;
    QLabel *label_11;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(685, 433);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        pushButton_4 = new QPushButton(centralwidget);
        pushButton_4->setObjectName("pushButton_4");

        gridLayout->addWidget(pushButton_4, 5, 1, 1, 1);

        comboBox_5 = new QComboBox(centralwidget);
        comboBox_5->addItem(QString());
        comboBox_5->addItem(QString());
        comboBox_5->setObjectName("comboBox_5");

        gridLayout->addWidget(comboBox_5, 1, 3, 1, 1);

        comboBox = new QComboBox(centralwidget);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");

        gridLayout->addWidget(comboBox, 1, 1, 1, 1);

        comboBox_4 = new QComboBox(centralwidget);
        comboBox_4->addItem(QString());
        comboBox_4->addItem(QString());
        comboBox_4->setObjectName("comboBox_4");

        gridLayout->addWidget(comboBox_4, 1, 6, 1, 1);

        horizontalSlider_7 = new QSlider(centralwidget);
        horizontalSlider_7->setObjectName("horizontalSlider_7");
        QSizePolicy sizePolicy(QSizePolicy::Ignored, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(horizontalSlider_7->sizePolicy().hasHeightForWidth());
        horizontalSlider_7->setSizePolicy(sizePolicy);
        horizontalSlider_7->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(horizontalSlider_7, 9, 1, 1, 1);

        label_10 = new QLabel(centralwidget);
        label_10->setObjectName("label_10");

        gridLayout->addWidget(label_10, 1, 5, 1, 1);

        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");

        gridLayout->addWidget(label_4, 6, 4, 1, 1);

        label_8 = new QLabel(centralwidget);
        label_8->setObjectName("label_8");

        gridLayout->addWidget(label_8, 8, 0, 1, 1);

        horizontalSlider_3 = new QSlider(centralwidget);
        horizontalSlider_3->setObjectName("horizontalSlider_3");
        sizePolicy.setHeightForWidth(horizontalSlider_3->sizePolicy().hasHeightForWidth());
        horizontalSlider_3->setSizePolicy(sizePolicy);
        horizontalSlider_3->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(horizontalSlider_3, 7, 5, 1, 2);

        pushButton_6 = new QPushButton(centralwidget);
        pushButton_6->setObjectName("pushButton_6");

        gridLayout->addWidget(pushButton_6, 1, 0, 1, 1);

        label = new QLabel(centralwidget);
        label->setObjectName("label");
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(label, 5, 4, 1, 1);

        horizontalSlider_6 = new QSlider(centralwidget);
        horizontalSlider_6->setObjectName("horizontalSlider_6");
        sizePolicy.setHeightForWidth(horizontalSlider_6->sizePolicy().hasHeightForWidth());
        horizontalSlider_6->setSizePolicy(sizePolicy);
        horizontalSlider_6->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(horizontalSlider_6, 8, 1, 1, 1);

        horizontalSlider_2 = new QSlider(centralwidget);
        horizontalSlider_2->setObjectName("horizontalSlider_2");
        sizePolicy.setHeightForWidth(horizontalSlider_2->sizePolicy().hasHeightForWidth());
        horizontalSlider_2->setSizePolicy(sizePolicy);
        horizontalSlider_2->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(horizontalSlider_2, 6, 5, 1, 2);

        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName("lineEdit");
        QSizePolicy sizePolicy2(QSizePolicy::Ignored, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(lineEdit->sizePolicy().hasHeightForWidth());
        lineEdit->setSizePolicy(sizePolicy2);
        lineEdit->setReadOnly(true);

        gridLayout->addWidget(lineEdit, 0, 1, 1, 1);

        pushButton_7 = new QPushButton(centralwidget);
        pushButton_7->setObjectName("pushButton_7");

        gridLayout->addWidget(pushButton_7, 1, 2, 1, 1);

        label_5 = new QLabel(centralwidget);
        label_5->setObjectName("label_5");

        gridLayout->addWidget(label_5, 7, 4, 1, 1);

        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy3);
        label_3->setLayoutDirection(Qt::LeftToRight);

        gridLayout->addWidget(label_3, 0, 5, 1, 1);

        lineEdit_3 = new QLineEdit(centralwidget);
        lineEdit_3->setObjectName("lineEdit_3");
        sizePolicy2.setHeightForWidth(lineEdit_3->sizePolicy().hasHeightForWidth());
        lineEdit_3->setSizePolicy(sizePolicy2);
        lineEdit_3->setReadOnly(true);

        gridLayout->addWidget(lineEdit_3, 0, 6, 1, 1);

        lineEdit_2 = new QLineEdit(centralwidget);
        lineEdit_2->setObjectName("lineEdit_2");
        sizePolicy.setHeightForWidth(lineEdit_2->sizePolicy().hasHeightForWidth());
        lineEdit_2->setSizePolicy(sizePolicy);
        lineEdit_2->setReadOnly(true);

        gridLayout->addWidget(lineEdit_2, 0, 3, 1, 1);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");

        gridLayout->addWidget(label_2, 0, 2, 1, 1);

        pushButton_5 = new QPushButton(centralwidget);
        pushButton_5->setObjectName("pushButton_5");

        gridLayout->addWidget(pushButton_5, 6, 1, 1, 1);

        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setStyleSheet(QString::fromUtf8("background-color: rgb(192, 191, 188);\n"
"color: rgb(0, 0, 0);"));

        gridLayout->addWidget(pushButton, 0, 0, 1, 1);

        horizontalSlider = new QSlider(centralwidget);
        horizontalSlider->setObjectName("horizontalSlider");
        sizePolicy.setHeightForWidth(horizontalSlider->sizePolicy().hasHeightForWidth());
        horizontalSlider->setSizePolicy(sizePolicy);
        horizontalSlider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(horizontalSlider, 5, 5, 1, 2);

        label_9 = new QLabel(centralwidget);
        label_9->setObjectName("label_9");
        QSizePolicy sizePolicy4(QSizePolicy::Ignored, QSizePolicy::Ignored);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(label_9->sizePolicy().hasHeightForWidth());
        label_9->setSizePolicy(sizePolicy4);

        gridLayout->addWidget(label_9, 9, 0, 1, 1);

        widget = new miwidget(centralwidget);
        widget->setObjectName("widget");

        gridLayout->addWidget(widget, 2, 0, 1, 7);

        label_7 = new QLabel(centralwidget);
        label_7->setObjectName("label_7");

        gridLayout->addWidget(label_7, 9, 2, 1, 1);

        horizontalSlider_5 = new QSlider(centralwidget);
        horizontalSlider_5->setObjectName("horizontalSlider_5");
        sizePolicy.setHeightForWidth(horizontalSlider_5->sizePolicy().hasHeightForWidth());
        horizontalSlider_5->setSizePolicy(sizePolicy);
        horizontalSlider_5->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(horizontalSlider_5, 9, 3, 1, 1);

        label_6 = new QLabel(centralwidget);
        label_6->setObjectName("label_6");

        gridLayout->addWidget(label_6, 8, 2, 1, 1);

        horizontalSlider_4 = new QSlider(centralwidget);
        horizontalSlider_4->setObjectName("horizontalSlider_4");
        sizePolicy.setHeightForWidth(horizontalSlider_4->sizePolicy().hasHeightForWidth());
        horizontalSlider_4->setSizePolicy(sizePolicy);
        horizontalSlider_4->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(horizontalSlider_4, 8, 3, 1, 1);

        bZoom_it = new QPushButton(centralwidget);
        bZoom_it->setObjectName("bZoom_it");
        bZoom_it->setStyleSheet(QString::fromUtf8("background-color: rgb(222, 221, 218);\n"
"color: rgb(0, 0, 0);"));

        gridLayout->addWidget(bZoom_it, 5, 3, 1, 1);

        bZoom_out = new QPushButton(centralwidget);
        bZoom_out->setObjectName("bZoom_out");
        bZoom_out->setStyleSheet(QString::fromUtf8("background-color: rgb(222, 221, 218);\n"
"color: rgb(0, 0, 0);"));

        gridLayout->addWidget(bZoom_out, 6, 3, 1, 1);

        pushButton_3 = new QPushButton(centralwidget);
        pushButton_3->setObjectName("pushButton_3");

        gridLayout->addWidget(pushButton_3, 5, 0, 1, 1);

        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName("pushButton_2");

        gridLayout->addWidget(pushButton_2, 5, 2, 1, 1);

        comboBox_2 = new QComboBox(centralwidget);
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->setObjectName("comboBox_2");

        gridLayout->addWidget(comboBox_2, 7, 0, 1, 1);

        comboBox_3 = new QComboBox(centralwidget);
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->setObjectName("comboBox_3");

        gridLayout->addWidget(comboBox_3, 7, 1, 1, 1);

        btn_settings = new QPushButton(centralwidget);
        btn_settings->setObjectName("btn_settings");

        gridLayout->addWidget(btn_settings, 8, 6, 1, 1);

        label_11 = new QLabel(centralwidget);
        label_11->setObjectName("label_11");

        gridLayout->addWidget(label_11, 8, 5, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 685, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "Up", nullptr));
        comboBox_5->setItemText(0, QCoreApplication::translate("MainWindow", "Central", nullptr));
        comboBox_5->setItemText(1, QCoreApplication::translate("MainWindow", "Parallel", nullptr));

        comboBox->setItemText(0, QCoreApplication::translate("MainWindow", ".jpg", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("MainWindow", ".bmp", nullptr));

        comboBox_4->setItemText(0, QCoreApplication::translate("MainWindow", "Edges", nullptr));
        comboBox_4->setItemText(1, QCoreApplication::translate("MainWindow", "Vertexes", nullptr));

        label_10->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\">Edit mode:</p></body></html>", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Y:", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\">Line size</p></body></html>", nullptr));
        pushButton_6->setText(QCoreApplication::translate("MainWindow", "Screenshot", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "X:", nullptr));
        pushButton_7->setText(QCoreApplication::translate("MainWindow", "Screencast", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Z:", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\">Polygons:</p></body></html>", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\">Vertexes:</p></body></html>", nullptr));
        pushButton_5->setText(QCoreApplication::translate("MainWindow", "Down", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Open", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\">Vertex size:</p></body></html>", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\">Object color:</p></body></html>", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\">BG color:</p></body></html>", nullptr));
        bZoom_it->setText(QCoreApplication::translate("MainWindow", "Zoom in", nullptr));
        bZoom_out->setText(QCoreApplication::translate("MainWindow", "Zoom out", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "Left", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "Right", nullptr));
        comboBox_2->setItemText(0, QCoreApplication::translate("MainWindow", "Solid lines", nullptr));
        comboBox_2->setItemText(1, QCoreApplication::translate("MainWindow", "Dotted lines", nullptr));

        comboBox_3->setItemText(0, QCoreApplication::translate("MainWindow", "Point", nullptr));
        comboBox_3->setItemText(1, QCoreApplication::translate("MainWindow", "Circle", nullptr));
        comboBox_3->setItemText(2, QCoreApplication::translate("MainWindow", "Square", nullptr));

        btn_settings->setText(QCoreApplication::translate("MainWindow", "Load", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "Last settings:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
