/**
 * @file mainwindow.h
 * @brief `QMainWindow` for the `3DViewer_v1.0` Qt front end.
 *
 * Hosts the @ref miwidget OpenGL viewport, the @ref FilesBrows file
 * picker, a `QSettings` store for cross-session UI persistence, and a
 * `QGifImage` recorder for 5-second 10-FPS GIF capture.
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QCloseEvent>
#include <QMainWindow>
#include <QMessageBox>
#include <QSettings>
#include <QTimer>

#include "filesbrows.h"
#include "miwidget.h"
#include "qgifimage.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

/**
 * @brief Top-level Qt window of `3DViewer_v1.0`.
 *
 * Owns the GL widget, the file browser, settings storage, and the GIF
 * recorder timer. Most slots follow Qt's auto-connect naming, so the
 * semantics are documented at the slot declarations rather than the
 * `Ui::MainWindow` form.
 */
class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = 0);
  //    MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow *ui;

  //    miwidget;
  miwidget *ogl;              ///< Embedded OpenGL viewport.
  FilesBrows fileBrowser;     ///< Embedded file picker widget.
  QSettings *settings;        ///< Persists UI state across launches.

  // для гифок
  const int GifFps = 10, GifLength = 5;  ///< GIF parameters: 10 fps × 5 s = 50 frames.
  int startTime, tmpTime;                ///< Monotonic time markers during recording.
  float timePrint;                       ///< Time printed on the GIF overlay.
  QTimer *timer;                         ///< Per-frame capture tick.
  QGifImage *gif;                        ///< GIF encoder accumulator.

 public slots:

  /** @brief "Open file" button — delegates to @ref FilesBrows. */
  void on_pushButton_clicked();

  /** @brief Text-change handler for the file-path edit. */
  void on_lineEdit_textChanged(const QString &arg1);
  /** @brief Update the read-only info line with parsed model stats. */
  void lineEdit_2_setText(obj_data);

 private slots:

  void on_pushButton_4_clicked();    ///< Rotate / move / scale (decoded via UI form).
  void on_pushButton_3_clicked();    ///< Rotate / move / scale.
  void on_pushButton_2_clicked();    ///< Rotate / move / scale.
  void on_pushButton_5_clicked();    ///< Rotate / move / scale.
  void on_bZoom_it_clicked();        ///< Zoom in.
  void on_bZoom_out_clicked();       ///< Zoom out.

  void on_horizontalSlider_valueChanged(int value);    ///< X rotation slider.
  void on_horizontalSlider_2_valueChanged(int value);  ///< Y rotation slider.
  void on_horizontalSlider_3_valueChanged(int value);  ///< Z rotation slider.

  // save settings
  /** @brief Persist UI state to @ref settings on window close. */
  void closeEvent(QCloseEvent *);
  /** @brief Save @ref settings (called from @ref closeEvent). */
  void writeSettings();
  /** @brief Restore @ref settings on startup. */
  void readSettings();

  // screenshot
  /** @brief Save a single-frame PNG screenshot of the GL viewport. */
  void on_pushButton_6_clicked();
  // gif
  /** @brief Start GIF capture: arm @ref timer for 50 ticks. */
  void on_pushButton_7_clicked();
  /** @brief Per-tick callback that captures one frame into @ref gif. */
  void gifMaking();
  void on_horizontalSlider_4_valueChanged(int value);  ///< Background color slider.
  void on_comboBox_2_currentTextChanged(const QString &arg1);  ///< Line-style combo.
  void on_horizontalSlider_5_valueChanged(int value);  ///< Line width slider.
  void on_horizontalSlider_6_valueChanged(int value);  ///< Vertex size slider.
  void on_horizontalSlider_7_valueChanged(int value);  ///< Line color slider.
  void on_comboBox_3_currentTextChanged(const QString &arg1);  ///< Vertex shape combo.
  void on_comboBox_4_currentTextChanged(const QString &arg1);  ///< Edit mode combo.
  void on_comboBox_5_currentTextChanged(const QString &arg1);  ///< Projection combo.
  void on_btn_settings_clicked();    ///< Open the settings dialog.
};
#endif  // MAINWINDOW_H
