#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ogl = new miwidget();
    ui->setupUi(this);

    connect(&fileBrowser, SIGNAL(nameChanged(const QString&)),
            this, SLOT(on_lineEdit_textChanged(const QString&)));

    connect(&fileBrowser, SIGNAL(objFile(obj_data)),
            this, SLOT(lineEdit_2_setText(obj_data)));

    settings = new QSettings("Config", QSettings::NativeFormat);
//    readSettings();
}

MainWindow::~MainWindow()
{
    delete ogl;
    delete settings;
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    fileBrowser.show();
}

//кнопки вращения

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    ogl->start_rotate(value, 'x');
}


void MainWindow::on_horizontalSlider_2_valueChanged(int value)
{
    ogl->start_rotate(value, 'y');
}


void MainWindow::on_horizontalSlider_3_valueChanged(int value)
{
      ogl->start_rotate(value, 'z');
}

//кнопки перемещения модельки
void MainWindow::on_pushButton_4_clicked()
{   //move up
    double value = 1;
    ogl->start_rotate(value, 'u');
}

void MainWindow::on_pushButton_3_clicked()
{   //move left
    double value = -1;
    ogl->start_rotate(value, 'l');
}

void MainWindow::on_pushButton_2_clicked()
{   //move right
    double value = 1;
    ogl->start_rotate(value, 'r');
}

void MainWindow::on_pushButton_5_clicked()
{   //move down
    double value = -1;
    ogl->start_rotate(value, 'd');
}

//кнопки приближения отдаления
void MainWindow::on_bZoom_it_clicked()
{
    double value = 1.8;
    ogl->start_rotate(value, 's');
}

void MainWindow::on_bZoom_out_clicked()
{
    double value = 0.8;
    ogl->start_rotate(value, 's');
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    ui->lineEdit->setText(arg1);
}

void MainWindow::lineEdit_2_setText(obj_data file)
{
    ui->lineEdit_2->setText(QString::number(file.count_of_vertexes));
    ui->lineEdit_3->setText(QString::number(file.count_of_facets));
}

void MainWindow::on_pushButton_6_clicked()
{
    time_t currTime = time(0);
    tm *time = localtime(&currTime);
    QDir folder = QFileInfo().absoluteDir();
    folder.setPath(QDir::cleanPath(folder.filePath(QStringLiteral(".."))));
    QString path = folder.path();
    QString name = path +  "/screenshots/" + QString::number(time->tm_hour) + "-" +
                   QString::number(time->tm_min) + "-";
    if (ui->comboBox->currentText() == ".jpg") {
        name +=  QString::number(time->tm_sec) + ".jpg";
    } else {
        name +=  QString::number(time->tm_sec) + ".bmp";
    }
    QPixmap pixmap(ogl->size() * 2);
    pixmap.setDevicePixelRatio(2);
    ogl->render(&pixmap);
    if (ui->comboBox->currentText() == ".jpg") {
        pixmap.save(name, "JPG", 100);
    } else {
        pixmap.save(name, "BMP", 100);
    }
}

void MainWindow::on_pushButton_7_clicked()
{
    gif = new QGifImage;
    gif->setDefaultDelay(1000 / GifFps);
    startTime = 0, tmpTime = 1000 / GifFps;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(gifMaking()));
    timer->start(1000 / GifFps);
}

void MainWindow::gifMaking() {
    if (startTime == tmpTime) {
      QPixmap screenGIF(ogl->size());
      ogl->render(&screenGIF);
      QImage image;
      image = screenGIF.toImage();
      gif->addFrame(image, 1000 / GifFps);
      timePrint = (float)startTime / 1e3;
      tmpTime += 1000 / GifFps;
    }
    if (startTime == 1000 * GifLength) {
      time_t currTime = time(0);
      tm *time = localtime(&currTime);
      QDir folder = QFileInfo().absoluteDir();
      folder.setPath(QDir::cleanPath(folder.filePath(QStringLiteral(".."))));
      QString path = folder.path();
      QString name = path + "/gifs/" + QString::number(time->tm_hour) + "-" +
                     QString::number(time->tm_min) + "-" +
                     QString::number(time->tm_sec) + ".gif";
      gif->save(name);
      free(gif);

      timer->stop();
    }
    startTime += 1000 / GifFps;
}


void MainWindow::on_horizontalSlider_4_valueChanged(int value)
{
    ogl->changeColor(value / 10.0);

}


void MainWindow::on_comboBox_2_currentTextChanged(const QString &arg1)
{
    ogl->changeLines(arg1);
}


void MainWindow::on_horizontalSlider_5_valueChanged(int value)
{
    ogl->changeLineColor(value / 10);
}


void MainWindow::on_horizontalSlider_6_valueChanged(int value)
{
    ogl->lineSize(value / 20.0);
}


void MainWindow::on_horizontalSlider_7_valueChanged(int value)
{
    ogl->vertexSize(value / 10.0);
}


void MainWindow::on_comboBox_3_currentTextChanged(const QString &arg1)
{
    ogl->changeVertex(arg1);
}


void MainWindow::on_comboBox_4_currentTextChanged(const QString &arg1)
{
    ogl->editMode(arg1);
}


void MainWindow::on_comboBox_5_currentTextChanged(const QString &arg1)
{
    ogl->perspectiveMode(arg1);
}

void MainWindow::closeEvent(QCloseEvent* event) {
    QMessageBox::StandardButton resBtn =
                 QMessageBox::question(this, "3d_viewer_0.1", tr("Save settings before exit?\n"),
                                       QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
      if (resBtn == QMessageBox::Yes) {
          writeSettings();
          event->accept();
      } else if (resBtn == QMessageBox::No){
          event->accept();
      } else {
          event->ignore();
      }
}

void MainWindow::writeSettings() {
//    QSettings settings("Config", "Settings");
    settings->setValue("background color", ui->horizontalSlider_4->sliderPosition());
    settings->setValue("line color", ui->horizontalSlider_5->sliderPosition());
    settings->setValue("line size", ui->horizontalSlider_6->sliderPosition());
    settings->setValue("vertex size", ui->horizontalSlider_7->sliderPosition());
    settings->setValue("line type", ui->comboBox_2->currentText());
    settings->setValue("vertex type", ui->comboBox_3->currentText());
    settings->setValue("edit mode", ui->comboBox_4->currentText());
    settings->setValue("ortho/perspective", ui->comboBox_5->currentText());
}

void MainWindow::readSettings() {
//    QSettings settings("Config", "Settings");
    on_horizontalSlider_4_valueChanged(settings->value("backcround color").toDouble());
    on_horizontalSlider_5_valueChanged(settings->value("line color").toDouble());
    on_horizontalSlider_6_valueChanged(settings->value("line size").toDouble());
    on_horizontalSlider_7_valueChanged(settings->value("vertex size").toDouble());
    on_comboBox_2_currentTextChanged(settings->value("line type").toString());
    on_comboBox_3_currentTextChanged(settings->value("vertex type").toString());
    on_comboBox_4_currentTextChanged(settings->value("edit mode").toString());
    on_comboBox_5_currentTextChanged(settings->value("ortho/perspective").toString());
}

void MainWindow::on_btn_settings_clicked()
{
    QMessageBox::StandardButton resBtn =
                 QMessageBox::question(this, "3d_viewer_0.1", tr("Load last saved settings?\n"),
                                       QMessageBox::Yes | QMessageBox::No);
      if (resBtn == QMessageBox::Yes) {
          readSettings();
      }

}

