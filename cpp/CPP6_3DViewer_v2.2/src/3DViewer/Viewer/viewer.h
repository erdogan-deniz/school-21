/**
 * @file viewer.h
 * @brief `QMainWindow` host for `CPP6_3DViewer_v2.2` — UI for the
 *        modern-OpenGL `scene` widget.
 *
 * Adds over `3DViewer_v2.0`: texture upload, UV-map export, flat vs
 * smooth shading, light source positioning + RGB intensity, GIF
 * capture, JPEG/BMP snapshot. UI follows Observer-style wiring: every
 * widget signal calls a `viewer` slot which writes onto the borrowed
 * `scene` knobs and requests a repaint.
 */

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
/**
 * @brief Top-level Qt window of `CPP6_3DViewer_v2.2`.
 *
 * Wires the auto-generated `Ui::viewer` form to slots that mutate the
 * `scene` widget. Supports image / GIF capture and Phong light
 * configuration on top of the v2.0 feature set.
 */
class viewer : public QMainWindow {
  Q_OBJECT

 public:
  viewer(QWidget *parent = nullptr);
  ~viewer();

 protected:
  /** @brief Wireframe / shading hotkeys (delegated to `scene`). */
  void keyPressEvent(QKeyEvent *event) override;

 private slots:
  void on_actionOpen_triggered();                  ///< Open OBJ file via QFileDialog.
  void on_actionClose_triggered();                 ///< Quit the application.
  void on_actionInfo_triggered();                  ///< Show About dialog.
  void on_actionOrthographic_Perspective_triggered();  ///< Toggle projection mode.
  void on_actionHide_triggered();                  ///< Hide / show side panels.
  void on_actionLight_triggered();                 ///< Toggle Phong lighting.

  void on_pushButton_bg_clicked();                 ///< Pick background color.
  void on_pushButton_vertex_clicked();             ///< Pick vertex color.
  void on_pushButton_lines_clicked();              ///< Pick edge color.

  void on_horizontalSlider_lineWidth_sliderMoved(int position);
  void on_horizontalSlider_lineWidth_sliderPressed();
  void on_horizontalSlider_versize_sliderMoved(int position);
  void on_horizontalSlider_versize_sliderPressed();
  void on_horizontalSlider_scale_sliderMoved(int position);
  void on_horizontalSlider_scale_sliderPressed();

  void on_pushButton_line_solid_clicked();         ///< Solid line style.
  void on_pushButton_line_dashed_clicked();        ///< Dashed line style.
  void on_pushButton_ver_circle_clicked();         ///< Circular vertex markers.
  void on_pushButton_ver_square_clicked();         ///< Square vertex markers.
  void on_pushButton_ver_none_clicked();           ///< Hide vertex markers.
  void on_pushButton_wireframe_clicked();          ///< Toggle wireframe.

  void on_doubleSpinBox_x_move_valueChanged();
  void on_doubleSpinBox_y_move_valueChanged();
  void on_doubleSpinBox_z_move_valueChanged();

  void on_spinBox_x_rot_valueChanged(int);
  void on_spinBox_y_rot_valueChanged(int);
  void on_spinBox_z_rot_valueChanged(int);

  void on_actionJPEG_triggered();                  ///< Save current frame as JPEG.
  void on_actionBMP_triggered();                   ///< Save current frame as BMP.

  void on_actionGIF_triggered();                   ///< Start 5-second GIF recording.

  void on_pushButton_apply_texture_clicked();      ///< Load + bind a texture image.
  void on_pushButton_unload_texture_clicked();     ///< Detach the active texture.
  void on_pushButton_save_uvmap_clicked();         ///< Export UV map as PNG.

  void on_pushButton_flat_shading_clicked();       ///< Flat normals.
  void on_pushButton_smooth_shading_clicked();     ///< Smooth normals.

  void on_doubleSpinBox_x_light_pos_valueChanged(double arg1);
  void on_doubleSpinBox_y_light_pos_valueChanged(double arg1);
  void on_doubleSpinBox_z_light_pos_valueChanged(double arg1);

  void on_doubleSpinBox_r_light_intens_valueChanged(double arg1);
  void on_doubleSpinBox_g_light_intens_valueChanged(double arg1);
  void on_doubleSpinBox_b_light_intens_valueChanged(double arg1);

 private:
  /** @brief Save current `scene` framebuffer in @p format (JPEG / BMP). */
  void SaveImage_(QString format);
  /** @brief Append one captured frame to @ref GIF_. */
  void Recording_();
  /** @brief Encode @ref GIF_ to disk via QGifImage. */
  void SaveGIF_();

  /** @brief Apply current background color to surrounding widgets. */
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
