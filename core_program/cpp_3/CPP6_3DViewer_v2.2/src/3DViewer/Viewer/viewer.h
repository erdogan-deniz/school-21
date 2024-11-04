#ifndef VIEWER_H
#define VIEWER_H

#include <QColorDialog>
#include <QFileDialog>
#include <QImage>
#include <QKeyEvent>
#include <QMainWindow>
#include <QMessageBox>
#include <QOpenGLTexture>
#include <QPainter>
#include <QTimer>
#include <QVector>
#include <iostream>

#include "../Controller/controller.h"
#include "../GIFCreation/gifImage/qgifimage.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class viewer;
}
QT_END_NAMESPACE

//  Observer
class viewer : public QMainWindow {
  Q_OBJECT

 public:
  viewer(QWidget *parent = nullptr);
  ~viewer();

 protected:
  void keyPressEvent(QKeyEvent *event) override;

 private slots:
  void on_actionOpen_triggered();
  void on_actionClose_triggered();
  void on_actionInfo_triggered();
  void on_actionOrthographic_Perspective_triggered();
  void on_actionHide_triggered();
  void on_actionLight_triggered();

  void on_pushButton_bg_clicked();
  void on_pushButton_vertex_clicked();
  void on_pushButton_lines_clicked();

  void on_horizontalSlider_lineWidth_sliderMoved(int position);
  void on_horizontalSlider_lineWidth_sliderPressed();
  void on_horizontalSlider_versize_sliderMoved(int position);
  void on_horizontalSlider_versize_sliderPressed();
  void on_horizontalSlider_scale_sliderMoved(int position);
  void on_horizontalSlider_scale_sliderPressed();

  void on_pushButton_line_solid_clicked();
  void on_pushButton_line_dashed_clicked();
  void on_pushButton_ver_circle_clicked();
  void on_pushButton_ver_square_clicked();
  void on_pushButton_ver_none_clicked();
  void on_pushButton_wireframe_clicked();

  void on_doubleSpinBox_x_move_valueChanged();
  void on_doubleSpinBox_y_move_valueChanged();
  void on_doubleSpinBox_z_move_valueChanged();

  void on_spinBox_x_rot_valueChanged(int);
  void on_spinBox_y_rot_valueChanged(int);
  void on_spinBox_z_rot_valueChanged(int);

  void on_actionJPEG_triggered();
  void on_actionBMP_triggered();

  void on_actionGIF_triggered();

  void on_pushButton_apply_texture_clicked();
  void on_pushButton_unload_texture_clicked();
  void on_pushButton_save_uvmap_clicked();

  void on_pushButton_flat_shading_clicked();
  void on_pushButton_smooth_shading_clicked();

  void on_doubleSpinBox_x_light_pos_valueChanged(double arg1);
  void on_doubleSpinBox_y_light_pos_valueChanged(double arg1);
  void on_doubleSpinBox_z_light_pos_valueChanged(double arg1);

  void on_doubleSpinBox_r_light_intens_valueChanged(double arg1);
  void on_doubleSpinBox_g_light_intens_valueChanged(double arg1);
  void on_doubleSpinBox_b_light_intens_valueChanged(double arg1);

 private:
  void SaveImage_(QString format);
  void Recording_();
  void SaveGIF_();

  void SetFrameColor_();

  float time_;
  bool hiden_, is_recording_;
  QString filename_;
  QImage texture_image_;
  QString fname_texture_;
  QTimer *record_time_;
  QVector<QImage> GIF_;

  Ui::viewer *ui;
};
#endif  // VIEWER_H
