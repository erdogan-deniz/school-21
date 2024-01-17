#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "miwidget.h"
#include "filesbrows.h"
#include "qgifimage.h"
#include <QTimer>
#include <QCloseEvent>
#include <QMessageBox>
#include <QSettings>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget * parent = 0);
//    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

//    miwidget;
    miwidget *ogl;
    FilesBrows fileBrowser;
    QSettings* settings;

    // для гифок
    const int GifFps = 10, GifLength = 5;
    int startTime, tmpTime;
    float timePrint;
    QTimer *timer;
    QGifImage *gif;


public slots:

    void on_pushButton_clicked();

    void on_lineEdit_textChanged(const QString &arg1);
    void lineEdit_2_setText(obj_data);


private slots:

    void on_pushButton_4_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_5_clicked();
    void on_bZoom_it_clicked();
    void on_bZoom_out_clicked();

    void on_horizontalSlider_valueChanged(int value);
    void on_horizontalSlider_2_valueChanged(int value);
    void on_horizontalSlider_3_valueChanged(int value);

    // save settings
    void closeEvent(QCloseEvent*);
    void writeSettings();
    void readSettings();

    // screenshot
    void on_pushButton_6_clicked();
    // gif
    void on_pushButton_7_clicked();
    void gifMaking();
    void on_horizontalSlider_4_valueChanged(int value);
    void on_comboBox_2_currentTextChanged(const QString &arg1);
    void on_horizontalSlider_5_valueChanged(int value);
    void on_horizontalSlider_6_valueChanged(int value);
    void on_horizontalSlider_7_valueChanged(int value);
    void on_comboBox_3_currentTextChanged(const QString &arg1);
    void on_comboBox_4_currentTextChanged(const QString &arg1);
    void on_comboBox_5_currentTextChanged(const QString &arg1);
    void on_btn_settings_clicked();
};
#endif // MAINWINDOW_H
