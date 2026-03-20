#include "filesbrows.h"
#include "ui_filesbrows.h"

FilesBrows::FilesBrows(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FilesBrows)
{
    ui->setupUi(this);
    model = new QFileSystemModel(this);
    model->setFilter(QDir::QDir::AllEntries);
    model->setRootPath("");
    ui->listView->setModel(model);
}

FilesBrows::~FilesBrows()
{
    delete ui;
}

void FilesBrows::on_listView_doubleClicked(const QModelIndex &index)
{
    QListView* list = (QListView*) sender();
    QFileInfo fileInfo = model->fileInfo(index);
    if (fileInfo.fileName() == "..") {
        QDir dir = fileInfo.dir();
        dir.cdUp();
        list->setRootIndex(model->index(dir.absolutePath()));
    } else if (fileInfo.fileName() == "/" || fileInfo.fileName() == ".") {
        list->setRootIndex(model->index(""));
    } else if (fileInfo.isDir()) {
        list->setRootIndex(index);
    } else if (fileInfo.fileName().right(4) == ".obj") {
        emit objFile(pathToFile.parse_file(fileInfo.absoluteFilePath()));
        emit nameChanged(fileInfo.fileName());
        this->close();
    }
}
