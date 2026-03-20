#include "viewer.h"

#include "ui_viewer.h"

viewer::viewer(QWidget *parent) : QMainWindow(parent), ui(new Ui::viewer) {
  ui->setupUi(this);
  this->setWindowTitle("3DViewer 2.1");
  ui->horizontalSlider_lineWidth->setValue(ui->widget->line_width);
  ui->lcdNumber_lineWidth->display((int)ui->widget->line_width);
  ui->horizontalSlider_versize->setValue(ui->widget->vertex_size);
  ui->lcdNumber_versize->display((int)ui->widget->vertex_size);

  ui->pushButton_apply_texture->setDisabled(true);
  ui->pushButton_unload_texture->setDisabled(true);
  ui->pushButton_save_uvmap->setDisabled(true);

  SetFrameColor_();

  hiden_ = false, is_recording_ = false;
  time_ = 0.0;
  record_time_ = new QTimer(this);
  connect(record_time_, &QTimer::timeout, this, &viewer::Recording_);
}

viewer::~viewer() {
  ui->widget->makeCurrent();
  s21::Controller::GetInstance().clearArrays();
  ui->widget->vbo.destroy();
  ui->widget->ebo.destroy();
  ui->widget->vao.destroy();
  ui->widget->vao_light.destroy();
  on_pushButton_unload_texture_clicked();
  delete ui;
}

void viewer::on_actionOpen_triggered() {
  QString fname = QFileDialog::getOpenFileName(
      this, "Choose File", QDir::homePath(), tr("OBJ (*.obj)"));
  if (fname != "") {
    filename_ = fname;
    s21::Controller::GetInstance().clearArrays();
    s21::Controller::GetInstance().ParseVertex_3D(fname);
    ui->widget->InitModel(s21::Controller::GetInstance().GetPolygonsArray(),
                          s21::Controller::GetInstance().GetIndices());

    on_pushButton_unload_texture_clicked();
    if ((ui->widget->has_normals =
             s21::Controller::GetInstance().NormalsUsage()))
      ui->actionLight->setDisabled(false);
    else
      ui->actionLight->setDisabled(true), ui->actionLight->setChecked(false);

    if ((ui->widget->has_texture =
             s21::Controller::GetInstance().TextureUsage()) &&
        !ui->widget->wireframe)
      ui->pushButton_apply_texture->setDisabled(false);
    else
      ui->pushButton_apply_texture->setDisabled(true);

    ui->widget->update();
  }
}

void viewer::on_actionClose_triggered() {
  s21::Controller::GetInstance().clearArrays();
  on_pushButton_unload_texture_clicked();
  ui->pushButton_apply_texture->setDisabled(true);
  ui->widget->has_texture = false;
  ui->widget->has_normals = false;
  ui->widget->update();
  filename_ = "";
}

void viewer::on_actionInfo_triggered() {
  QMessageBox::information(
      this, "Information",
      "Filename: " + filename_ + "\nVertices: " +
          QString::number(
              !s21::Controller::GetInstance().GetVertices().size()
                  ? 0
                  : s21::Controller::GetInstance().GetVertices().size() - 1) +
          "\nLines: " +
          QString::number(s21::Controller::GetInstance().GetIndices().size()));
}

void viewer::keyPressEvent(QKeyEvent *event) {
  switch (event->key()) {
    case Qt::Key_R:
      ui->spinBox_x_rot->setValue(0), ui->spinBox_y_rot->setValue(0),
          ui->spinBox_z_rot->setValue(0);
      ui->doubleSpinBox_x_move->setValue(0.0f),
          ui->doubleSpinBox_y_move->setValue(0.0f),
          ui->doubleSpinBox_z_move->setValue(0.0f);
  }
  ui->widget->keyPressEvent(event);
}

void viewer::SetFrameColor_() {
  this->setStyleSheet("QMainWindow{ background-color: rgb(" +
                      QString::number(ui->widget->background.red()) + ", " +
                      QString::number(ui->widget->background.green()) + ", " +
                      QString::number(ui->widget->background.blue()) + ");}");
}

void viewer::on_pushButton_bg_clicked() {
  ui->widget->background = QColorDialog::getColor();
  SetFrameColor_();
}

void viewer::on_pushButton_vertex_clicked() {
  ui->widget->vertices_color = QColorDialog::getColor();
}

void viewer::on_pushButton_lines_clicked() {
  ui->widget->lines_color = QColorDialog::getColor();
}

void viewer::on_horizontalSlider_lineWidth_sliderMoved(int position) {
  ui->widget->line_width = position;
  ui->lcdNumber_lineWidth->display(position);
  ui->widget->update();
}

void viewer::on_horizontalSlider_lineWidth_sliderPressed() {
  on_horizontalSlider_lineWidth_sliderMoved(
      ui->horizontalSlider_lineWidth->value());
}

void viewer::on_horizontalSlider_versize_sliderMoved(int position) {
  ui->widget->is_none = false;
  ui->widget->vertex_size = position;
  ui->lcdNumber_versize->display(position);
  ui->widget->update();
}

void viewer::on_horizontalSlider_versize_sliderPressed() {
  on_horizontalSlider_versize_sliderMoved(
      ui->horizontalSlider_versize->value());
}

void viewer::on_pushButton_line_solid_clicked() {
  ui->widget->dashed_solid = false;
  ui->widget->update();
}

void viewer::on_pushButton_line_dashed_clicked() {
  ui->widget->dashed_solid = true;
  ui->widget->update();
}

void viewer::on_pushButton_ver_circle_clicked() {
  ui->widget->is_none = false;
  ui->widget->circle_square = false;
  ui->widget->update();
}

void viewer::on_pushButton_ver_square_clicked() {
  ui->widget->is_none = false;
  ui->widget->circle_square = true;
  ui->widget->update();
}

void viewer::on_pushButton_ver_none_clicked() {
  ui->widget->is_none = true;
  ui->horizontalSlider_versize->setValue(1);
  ui->lcdNumber_versize->display(1);
  ui->widget->update();
}

void viewer::on_horizontalSlider_scale_sliderMoved(int position) {
  if (position > 0) {
    ui->widget->scale_factor = position;
  } else {
    ui->widget->scale_factor = float(1.0f - abs(position) / 100.0f);
  }
  ui->lcdNumber_scale->display(position);
  ui->widget->update();
}

void viewer::on_horizontalSlider_scale_sliderPressed() {
  on_horizontalSlider_scale_sliderMoved(ui->horizontalSlider_scale->value());
}

void viewer::on_doubleSpinBox_x_move_valueChanged() {
  ui->widget->move_object[0] = ui->doubleSpinBox_x_move->value();
  ui->widget->move_object[1] = ui->doubleSpinBox_y_move->value();
  ui->widget->move_object[2] = ui->doubleSpinBox_z_move->value();
  ui->widget->update();
}

void viewer::on_doubleSpinBox_y_move_valueChanged() {
  on_doubleSpinBox_x_move_valueChanged();
}

void viewer::on_doubleSpinBox_z_move_valueChanged() {
  on_doubleSpinBox_x_move_valueChanged();
}

void viewer::on_spinBox_x_rot_valueChanged(int arg1) {
  ui->widget->RotateModel(arg1, ui->widget->r_y, ui->widget->r_z);
  ui->widget->update();
}

void viewer::on_spinBox_y_rot_valueChanged(int arg1) {
  ui->widget->RotateModel(ui->widget->r_x, arg1, ui->widget->r_z);
  ui->widget->update();
}

void viewer::on_spinBox_z_rot_valueChanged(int arg1) {
  ui->widget->RotateModel(ui->widget->r_x, ui->widget->r_y, arg1);
  ui->widget->update();
}

void viewer::on_actionOrthographic_Perspective_triggered() {
  QKeyEvent *key = new QKeyEvent(
      QEvent::KeyPress, ui->widget->projection_type ? Qt::Key_O : Qt::Key_P,
      Qt::NoModifier);
  ui->widget->keyPressEvent(key);
  delete key;
}

void viewer::on_actionHide_triggered() {
  if (hiden_) {
    ui->dockWidget_main->show();
    ui->dockWidget_3->show();
    hiden_ = false;
  } else {
    ui->dockWidget_main->hide();
    ui->dockWidget_3->hide();
    hiden_ = true;
  }
}

void viewer::on_actionLight_triggered() {
  if (ui->actionLight->isChecked())
    ui->widget->is_light_enabled = true;
  else
    ui->widget->is_light_enabled = false;
  ui->widget->update();
}

void viewer::SaveImage_(QString format) {
  QString str = QFileDialog::getSaveFileName(this, "Save file as",
                                             QDir::homePath(), format);
  if (str != "") ui->widget->grabFramebuffer().save(str);
}

void viewer::on_actionJPEG_triggered() { SaveImage_("*.jpeg"); }

void viewer::on_actionBMP_triggered() { SaveImage_("*.bmp"); }

void viewer::on_actionGIF_triggered() {
  if (!is_recording_) {
    is_recording_ = true;
    this->setStyleSheet("QMainWindow{ background-color: red;}");
    record_time_->start(100);
  }
}

void viewer::Recording_() {
  if (is_recording_ && time_ <= 5.0) {
    GIF_.push_back(ui->widget->grab().toImage());
    time_ += 0.1;
  } else {
    SaveGIF_();
    record_time_->stop();
  }
}

void viewer::SaveGIF_() {
  QString str = QFileDialog::getSaveFileName(
      this, tr("Save GIF"), QDir::homePath(), tr("GIF (*.gif)"));
  if (str != "") {
    QGifImage gif(QSize(640, 480));

    gif.setDefaultTransparentColor(Qt::black);
    gif.setDefaultDelay(100);

    for (QVector<QImage>::Iterator frame = GIF_.begin(); frame != GIF_.end();
         frame++) {
      gif.addFrame(*frame);
    }

    gif.save(str);
    GIF_.clear();
  }
  time_ = 0.0;
  is_recording_ = false;

  SetFrameColor_();
}

void viewer::on_pushButton_wireframe_clicked() {
  if (!ui->widget->wireframe) ui->widget->wireframe = true;
  ui->pushButton_apply_texture->setDisabled(true);
  on_pushButton_unload_texture_clicked();
  ui->widget->update();
}

void viewer::on_pushButton_flat_shading_clicked() {
  if (ui->widget->wireframe) ui->widget->wireframe = false;
  if (ui->widget->has_texture) ui->pushButton_apply_texture->setDisabled(false);
  ui->widget->flat_shading = true;
  ui->widget->update();
}

void viewer::on_pushButton_smooth_shading_clicked() {
  if (ui->widget->wireframe) ui->widget->wireframe = false;
  if (ui->widget->has_texture) ui->pushButton_apply_texture->setDisabled(false);
  ui->widget->flat_shading = false;
  ui->widget->update();
}

void viewer::on_pushButton_apply_texture_clicked() {
  ui->widget->wireframe = false;
  fname_texture_ = QFileDialog::getOpenFileName(
      this, "Choose File", QDir::homePath(), tr("BMP (*.bmp)"));

  if (fname_texture_ != "") {
    texture_image_ = QImage(fname_texture_);
    if (!ui->widget->texture) delete ui->widget->texture;
    ui->widget->texture = new QOpenGLTexture(texture_image_);
    ui->widget->texture->setMinificationFilter(QOpenGLTexture::Nearest);
    ui->widget->texture->setMagnificationFilter(QOpenGLTexture::Linear);
    ui->widget->texture->setWrapMode(QOpenGLTexture::Repeat);
    ui->pushButton_unload_texture->setDisabled(false);
    ui->pushButton_save_uvmap->setDisabled(false);
  }
  ui->widget->update();
}

void viewer::on_pushButton_unload_texture_clicked() {
  if (ui->widget->texture) delete ui->widget->texture;
  ui->widget->texture = nullptr;
  ui->pushButton_unload_texture->setDisabled(true);
  ui->pushButton_save_uvmap->setDisabled(true);
  ui->widget->update();
}

void viewer::on_doubleSpinBox_x_light_pos_valueChanged(double arg1) {
  ui->widget->light_pos[0] = arg1;
  ui->widget->update();
}

void viewer::on_doubleSpinBox_y_light_pos_valueChanged(double arg1) {
  ui->widget->light_pos[1] = arg1;
  ui->widget->update();
}

void viewer::on_doubleSpinBox_z_light_pos_valueChanged(double arg1) {
  ui->widget->light_pos[2] = arg1;
  ui->widget->update();
}

void viewer::on_pushButton_save_uvmap_clicked() {
  QPixmap map(fname_texture_);
  QPainter painter(&map);

  QList<QLine> parser_x_y = ui->widget->GetLines(map);
  painter.setPen(QColorDialog::getColor());
  painter.drawLines(parser_x_y);

  QString str = QFileDialog::getSaveFileName(
      this, tr("Save GIF"), QDir::homePath(), tr("BMP (*.bmp)"));
  map.save(str);
}

void viewer::on_doubleSpinBox_r_light_intens_valueChanged(double arg1) {
  ui->widget->light_color[0] = arg1;
  ui->widget->update();
}

void viewer::on_doubleSpinBox_g_light_intens_valueChanged(double arg1) {
  ui->widget->light_color[1] = arg1;
  ui->widget->update();
}

void viewer::on_doubleSpinBox_b_light_intens_valueChanged(double arg1) {
  ui->widget->light_color[2] = arg1;
  ui->widget->update();
}
