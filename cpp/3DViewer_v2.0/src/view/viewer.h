/**
 * @file viewer.h
 * @brief `QMainWindow` host for `3DViewer_v2.0` — owns the UI form
 *        and dispatches user input to @ref s21::Controller via the
 *        embedded @ref GLWidget.
 *
 * The viewer also implements GIF capture (via the bundled QtGifImage
 * library), single-frame snapshot, and persists UI state to
 * `QSettings` between launches.
 */

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

/**
 * @brief Top-level Qt window.
 *
 * Holds the auto-generated `Ui::Viewer` form, a `QGifImage` recorder,
 * and a `QSettings` instance for cross-session persistence. All
 * user-facing controls (file open, color pickers, move / rotate /
 * scale buttons, projection / line / point radio groups, GIF and
 * snapshot capture) are wired through Qt's auto-connect slot naming.
 */
class Viewer : public QMainWindow {
  Q_OBJECT

 public:
  /**
   * @brief Construct the main window.
   * @param contr Singleton controller instance (already wired to model
   *              and transform).
   * @param parent Optional parent widget.
   */
  Viewer(s21::Controller *contr, QWidget *parent = nullptr);
  ~Viewer();
  QSettings settings;  ///< Persists UI state between launches.

 private slots:
  void on_pushButtonFile_clicked();        ///< Open file dialog and load OBJ.
  void on_chooseBackColor_clicked();       ///< Pick background color.
  void on_chooseLineColor_clicked();       ///< Pick edge color.
  void on_choosePointColor_clicked();      ///< Pick vertex-point color.
  void on_buttonMoveX1_clicked();          ///< Translate −X.
  void on_buttonMoveX2_clicked();          ///< Translate +X.
  void on_buttonMoveY1_clicked();          ///< Translate −Y.
  void on_buttonMoveY2_clicked();          ///< Translate +Y.
  void on_buttonMoveZ1_clicked();          ///< Translate −Z.
  void on_buttonMoveZ2_clicked();          ///< Translate +Z.
  void on_buttonRotX1_clicked();           ///< Rotate −X.
  void on_buttonRotX2_clicked();           ///< Rotate +X.
  void on_buttonRotY1_clicked();           ///< Rotate −Y.
  void on_buttonRotY2_clicked();           ///< Rotate +Y.
  void on_buttonRotZ1_clicked();           ///< Rotate −Z.
  void on_buttonRotZ2_clicked();           ///< Rotate +Z.
  void on_buttonSizeMin_clicked();         ///< Scale down (uniform).
  void on_buttonSizeMax_clicked();         ///< Scale up (uniform).
  void on_radioButtonCentrall_clicked();   ///< Switch to central (perspective) projection.
  void on_radioButtonParallel_clicked();   ///< Switch to parallel (orthographic) projection.
  void on_radioButtonNoPoint_clicked();    ///< Hide vertex points.
  void on_radioButtonSquare_clicked();     ///< Render vertex points as squares.
  void on_radioButtonRound_clicked();      ///< Render vertex points as circles.
  void on_radioButtonNoLine_clicked();     ///< Hide edge lines.
  void on_radioButtonDotted_clicked();     ///< Render edges as dotted lines.
  void on_radioButtonSolid_clicked();      ///< Render edges as solid lines.
  void on_buttonLineSize1_clicked();       ///< Decrease line width.
  void on_buttonLineSize2_clicked();       ///< Increase line width.
  void on_buttonPointSize1_clicked();      ///< Decrease point size.
  void on_buttonPointSize2_clicked();      ///< Increase point size.
  /** @brief Reset transform state and reload the current file. */
  void clear();

  /** @brief Timer tick that captures one GIF frame. */
  void CreatGif();
  /** @brief Show a modal `QMessageBox` with @p message. */
  void ShowMessage(QString message);
  void on_buttonGif_clicked();             ///< Start / stop GIF recording.
  void on_buttonSnapshot_clicked();        ///< Save one PNG / JPG frame.

  /** @brief Persist UI state (colors, sizes, projection) to @ref settings. */
  void saveSettings();
  /** @brief Restore UI state from @ref settings on startup. */
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
