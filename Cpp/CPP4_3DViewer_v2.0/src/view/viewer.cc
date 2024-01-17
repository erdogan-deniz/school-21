#include "viewer.h"

#include "ui_viewer.h"

Viewer::Viewer(s21::Controller* control, QWidget* parent)
    : QMainWindow(parent), ui(new Ui::Viewer) {
  ui->setupUi(this);
  setFixedSize(size());
  loadSettings();
  ui->GLwidget->setControll(control);
  connect(&gifTimer_, SIGNAL(timeout()), this, SLOT(CreatGif()));
}

Viewer::~Viewer() {
  saveSettings();
  delete ui;
}

void Viewer::on_pushButtonFile_clicked() {
  QString fileName =
      QFileDialog::getOpenFileName(this, "Выбрать файл", "", "OBJ (*.obj)");
  if (fileName != "") {
    clear();
    // fileNameFlag = 1;
    ui->GLwidget->setFileName(fileName);
    ui->countVertexes->setText(QString::number(ui->GLwidget->countVertexes));
    ui->countLines->setText(QString::number(ui->GLwidget->countLines));
    ui->fileName->setText(QFileInfo(fileName).fileName());
    if (ui->GLwidget->countVertexes == 0) {
      ShowMessage("Wrong model!");
    }
  }
}

void Viewer::clear() {
  ui->moveX->setText("0");
  ui->moveY->setText("0");
  ui->moveZ->setText("0");
  ui->rotationX->setText("0");
  ui->rotationY->setText("0");
  ui->rotationZ->setText("0");
  ui->labelSize->setText("1");
}

void Viewer::on_chooseBackColor_clicked() {
  ui->GLwidget->colorWidget = QColorDialog::getColor(Qt::gray);
}

void Viewer::on_chooseLineColor_clicked() {
  ui->GLwidget->colorLines = QColorDialog::getColor(Qt::gray);
}

void Viewer::on_choosePointColor_clicked() {
  ui->GLwidget->colorVertices = QColorDialog::getColor(Qt::gray);
}

void Viewer::on_buttonMoveX1_clicked() {
  double num = ui->moveX->text().toDouble() - 0.1;
  ui->moveX->setText(QString::number(num));
  ui->GLwidget->moveX_ = num;
}

void Viewer::on_buttonMoveX2_clicked() {
  double num = ui->moveX->text().toDouble() + 0.1;
  ui->moveX->setText(QString::number(num));
  ui->GLwidget->moveX_ = num;
}

void Viewer::on_buttonMoveY1_clicked() {
  double num = ui->moveY->text().toDouble() - 0.1;
  ui->moveY->setText(QString::number(num));
  ui->GLwidget->moveY_ = num;
}

void Viewer::on_buttonMoveY2_clicked() {
  double num = ui->moveY->text().toDouble() + 0.1;
  ui->moveY->setText(QString::number(num));
  ui->GLwidget->moveY_ = num;
}

void Viewer::on_buttonMoveZ1_clicked() {
  double num = ui->moveZ->text().toDouble() - 0.1;
  ui->moveZ->setText(QString::number(num));
  ui->GLwidget->moveZ_ = num;
}

void Viewer::on_buttonMoveZ2_clicked() {
  double num = ui->moveZ->text().toDouble() + 0.1;
  ui->moveZ->setText(QString::number(num));
  ui->GLwidget->moveZ_ = num;
}

void Viewer::on_buttonRotX1_clicked() {
  double num = ui->rotationX->text().toDouble() - 0.1;
  ui->rotationX->setText(QString::number(num));
  ui->GLwidget->rotationX_ = num;
}

void Viewer::on_buttonRotX2_clicked() {
  double num = ui->rotationX->text().toDouble() + 0.1;
  ui->rotationX->setText(QString::number(num));
  ui->GLwidget->rotationX_ = num;
}

void Viewer::on_buttonRotY1_clicked() {
  double num = ui->rotationY->text().toDouble() - 0.1;
  ui->rotationY->setText(QString::number(num));
  ui->GLwidget->rotationY_ = num;
}

void Viewer::on_buttonRotY2_clicked() {
  double num = ui->rotationY->text().toDouble() + 0.1;
  ui->rotationY->setText(QString::number(num));
  ui->GLwidget->rotationY_ = num;
}

void Viewer::on_buttonRotZ1_clicked() {
  double num = ui->rotationZ->text().toDouble() - 0.1;
  ui->rotationZ->setText(QString::number(num));
  ui->GLwidget->rotationZ_ = num;
}

void Viewer::on_buttonRotZ2_clicked() {
  double num = ui->rotationZ->text().toDouble() + 0.1;
  ui->rotationZ->setText(QString::number(num));
  ui->GLwidget->rotationZ_ = num;
}

void Viewer::on_buttonSizeMin_clicked() {
  double num = ui->labelSize->text().toDouble() - 0.1;
  if (num > 0) {
    ui->labelSize->setText(QString::number(num));
    ui->GLwidget->size_ = num;
  }
}

void Viewer::on_buttonSizeMax_clicked() {
  double num = ui->labelSize->text().toDouble() + 0.1;
  ui->labelSize->setText(QString::number(num));
  ui->GLwidget->size_ = num;
}

void Viewer::on_radioButtonCentrall_clicked() { ui->GLwidget->typeProect = 1; }

void Viewer::on_radioButtonParallel_clicked() { ui->GLwidget->typeProect = 2; }

void Viewer::on_radioButtonNoPoint_clicked() { ui->GLwidget->typeP = 1; }

void Viewer::on_radioButtonSquare_clicked() { ui->GLwidget->typeP = 2; }

void Viewer::on_radioButtonRound_clicked() { ui->GLwidget->typeP = 3; }

void Viewer::on_radioButtonNoLine_clicked() { ui->GLwidget->typeL = 1; }

void Viewer::on_radioButtonDotted_clicked() { ui->GLwidget->typeL = 2; }

void Viewer::on_radioButtonSolid_clicked() { ui->GLwidget->typeL = 3; }

void Viewer::on_buttonLineSize1_clicked() {
  double num = ui->sizeLine->text().toDouble() - 1;
  if (num > 0) {
    ui->sizeLine->setText(QString::number(num));
    ui->GLwidget->sizeL_ = num;
  }
}

void Viewer::on_buttonLineSize2_clicked() {
  double num = ui->sizeLine->text().toDouble() + 1;
  ui->sizeLine->setText(QString::number(num));
  ui->GLwidget->sizeL_ = num;
}

void Viewer::on_buttonPointSize1_clicked() {
  double num = ui->sizePoint->text().toDouble() - 1;
  if (num > 0) {
    ui->sizePoint->setText(QString::number(num));
    ui->GLwidget->sizeP_ = num;
  }
}

void Viewer::on_buttonPointSize2_clicked() {
  double num = ui->sizePoint->text().toDouble() + 1;
  ui->sizePoint->setText(QString::number(num));
  ui->GLwidget->sizeP_ = num;
}

void Viewer::ShowMessage(QString message) {
  QMessageBox messageBox;
  messageBox.setFixedSize(500, 200);
  messageBox.information(0, "Info", message);
}

void Viewer::on_buttonGif_clicked() {
  if (ui->countVertexes->text() != "0") {
    gifFileName_ = QFileDialog::getSaveFileName(this, tr("Save GIF"), "gif",
                                                tr("Gif Files (*.gif)"));
    if (!gifFileName_.isEmpty()) {
      ui->buttonGif->setDisabled(true);
      gifImage_ = new QGifImage;
      gifImage_->setDefaultDelay(100);
      gifTimer_.setInterval(100);
      gifTimer_.start();
    }
  } else {
    ShowMessage("No model selected.");
  }
}

void Viewer::CreatGif() {
  if (!startTime_.isValid()) {
    startTime_ = QTime::currentTime();
  }

  QImage image_ = ui->GLwidget->grabFramebuffer();
  gifImage_->addFrame(image_);

  if (startTime_.msecsTo(QTime::currentTime()) >= 5000) {
    gifTimer_.stop();
    gifImage_->save(gifFileName_);
    ShowMessage("Gif saved.");
    delete gifImage_;
    ui->buttonGif->setEnabled(true);
  }
  ui->buttonGif->setText("GIF");
}

void Viewer::on_buttonSnapshot_clicked() {
  if (ui->countVertexes->text() != "0") {
    QFileDialog dialog_photo(this);
    QString picture_name = dialog_photo.getSaveFileName(
        this, "Save as ...", QDir::currentPath(), "*.bmp;; *.jpeg");
    ui->GLwidget->grabFramebuffer().save(picture_name);
  } else {
    ShowMessage("No model selected.");
  }
}

void Viewer::saveSettings() {
  QSettings settings("School21", "Viewer");
  settings.setValue("backColor", ui->GLwidget->colorWidget);
  settings.setValue("lineColor", ui->GLwidget->colorLines);
  settings.setValue("pointColor", ui->GLwidget->colorVertices);
  settings.setValue("typeProect", ui->GLwidget->typeProect);
  settings.setValue("typeP", ui->GLwidget->typeP);
  settings.setValue("typeL", ui->GLwidget->typeL);

  settings.sync();
}

void Viewer::loadSettings() {
  QSettings settings("School21", "Viewer");
  ui->GLwidget->colorWidget =
      settings.value("backColor", QColor(Qt::black)).value<QColor>();
  ui->GLwidget->colorLines =
      settings.value("lineColor", QColor(Qt::green)).value<QColor>();
  ui->GLwidget->colorVertices =
      settings.value("pointColor", QColor(Qt::blue)).value<QColor>();

  ui->GLwidget->typeProect = settings.value("typeProect", 2).toInt();
  if (ui->GLwidget->typeProect == 1) {
    ui->radioButtonCentrall->setChecked(true);
  } else if (ui->GLwidget->typeProect == 2) {
    ui->radioButtonParallel->setChecked(true);
  }

  ui->GLwidget->typeP = settings.value("typeP", 3).toInt();
  if (ui->GLwidget->typeP == 1) {
    ui->radioButtonNoPoint->setChecked(true);
  } else if (ui->GLwidget->typeP == 2) {
    ui->radioButtonSquare->setChecked(true);
  } else if (ui->GLwidget->typeP == 3) {
    ui->radioButtonRound->setChecked(true);
  }

  ui->GLwidget->typeL = settings.value("typeL", 3).toInt();
  if (ui->GLwidget->typeL == 1) {
    ui->radioButtonNoLine->setChecked(true);
  } else if (ui->GLwidget->typeL == 2) {
    ui->radioButtonDotted->setChecked(true);
  } else if (ui->GLwidget->typeL == 3) {
    ui->radioButtonSolid->setChecked(true);
  }
}
