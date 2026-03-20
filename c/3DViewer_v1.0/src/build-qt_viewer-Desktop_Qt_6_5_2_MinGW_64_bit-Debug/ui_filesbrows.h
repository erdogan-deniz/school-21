/********************************************************************************
** Form generated from reading UI file 'filesbrows.ui'
**
** Created by: Qt User Interface Compiler version 6.5.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILESBROWS_H
#define UI_FILESBROWS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QListView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FilesBrows
{
public:
    QGridLayout *gridLayout;
    QListView *listView;

    void setupUi(QWidget *FilesBrows)
    {
        if (FilesBrows->objectName().isEmpty())
            FilesBrows->setObjectName("FilesBrows");
        FilesBrows->resize(400, 300);
        gridLayout = new QGridLayout(FilesBrows);
        gridLayout->setObjectName("gridLayout");
        listView = new QListView(FilesBrows);
        listView->setObjectName("listView");

        gridLayout->addWidget(listView, 0, 0, 1, 1);


        retranslateUi(FilesBrows);

        QMetaObject::connectSlotsByName(FilesBrows);
    } // setupUi

    void retranslateUi(QWidget *FilesBrows)
    {
        FilesBrows->setWindowTitle(QCoreApplication::translate("FilesBrows", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FilesBrows: public Ui_FilesBrows {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILESBROWS_H
