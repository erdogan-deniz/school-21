#ifndef FILESBROWS_H
#define FILESBROWS_H

#include <QWidget>
#include <QFileSystemModel>
#include <QDir>
#include "miwidget.h"



namespace Ui {
class FilesBrows;
}

class FilesBrows : public QWidget
{
    Q_OBJECT

public:
    explicit FilesBrows(QWidget *parent = nullptr);
    ~FilesBrows();

public slots:
    void on_listView_doubleClicked(const QModelIndex &index);

signals:
    void nameChanged(const QString&);
    void objFile(obj_data);

private:
    Ui::FilesBrows *ui;

    QFileSystemModel* model;

    miwidget pathToFile;
};

#endif // FILESBROWS_H
