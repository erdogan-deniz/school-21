#ifndef VIEWER_H
#define VIEWER_H

#include <QColorDialog>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QGraphicsScene>
#include <QMainWindow>
#include <QMessageBox>
#include <QSettings>
#include <QString>
#include <QTime>
#include <QTimer>

#include "../controller/controller.h"
#include "./QtGifImage/gifimage/qgifimage.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Viewer;
}
QT_END_NAMESPACE

class Viewer : public QMainWindow {
  Q_OBJECT

 public:
  Viewer(s21::Controller *contr, QWidget *parent = nullptr);
  ~Viewer();
  QSettings settings;

 private slots:
  void on_pushButtonFile_clicked();
  void on_chooseBackColor_clicked();
  void on_chooseLineColor_clicked();
  void on_choosePointColor_clicked();
  void on_buttonMoveX1_clicked();
  void on_buttonMoveX2_clicked();
  void on_buttonMoveY1_clicked();
  void on_buttonMoveY2_clicked();
  void on_buttonMoveZ1_clicked();
  void on_buttonMoveZ2_clicked();
  void on_buttonRotX1_clicked();
  void on_buttonRotX2_clicked();
  void on_buttonRotY1_clicked();
  void on_buttonRotY2_clicked();
  void on_buttonRotZ1_clicked();
  void on_buttonRotZ2_clicked();
  void on_buttonSizeMin_clicked();
  void on_buttonSizeMax_clicked();
  void on_radioButtonCentrall_clicked();
  void on_radioButtonParallel_clicked();
  void on_radioButtonNoPoint_clicked();
  void on_radioButtonSquare_clicked();
  void on_radioButtonRound_clicked();
  void on_radioButtonNoLine_clicked();
  void on_radioButtonDotted_clicked();
  void on_radioButtonSolid_clicked();
  void on_buttonLineSize1_clicked();
  void on_buttonLineSize2_clicked();
  void on_buttonPointSize1_clicked();
  void on_buttonPointSize2_clicked();
  void clear();

  void CreatGif();
  void ShowMessage(QString message);
  void on_buttonGif_clicked();
  void on_buttonSnapshot_clicked();

  void saveSettings();
  void loadSettings();

 private:
  Ui::Viewer *ui;
  QString nameFile_;
  // int fileNameFlag{};
  QTimer gifTimer_;
  QTime startTime_;
  QGifImage *gifImage_;
  QString gifFileName_;
};
#endif  // VIEWER_H
