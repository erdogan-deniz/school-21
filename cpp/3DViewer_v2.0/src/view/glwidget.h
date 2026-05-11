/**
 * @file glwidget.h
 * @brief `QOpenGLWidget` subclass that renders the loaded
 *        @ref s21::Object using legacy fixed-function OpenGL.
 *
 * Holds a borrowed @ref s21::Controller pointer and a snapshot of the
 * UI state (colors, line / point styles, projection type) updated by
 * @ref Viewer slots before each repaint.
 */

#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QMouseEvent>
#include <QOpenGLWidget>
#include <QWidget>
#include <QtOpenGL>

#include "../controller/controller.h"

/**
 * @brief Qt widget hosting the 3D scene.
 *
 * Owns no model state — that lives in @ref s21::Object via
 * @ref controller_. All public fields are UI knobs the @ref Viewer
 * writes directly before triggering an `update()`.
 */
class GLWidget : public QOpenGLWidget {
  Q_OBJECT
 public:
  explicit GLWidget(QWidget *parent = nullptr);
  /** @brief Inject the controller singleton. Must be called before any paint. */
  void setControll(s21::Controller *control) { controller_ = control; };
  /**
   * @brief Load a new OBJ file path; updates vertex / line counts.
   *
   * Forwards to @ref s21::Controller::setFilepath and caches the
   * derived counts for status-bar display in the parent @ref Viewer.
   */
  void setFileName(QString str) {
    fileName_ = str;
    controller_->setFilepath(fileName_.toStdString());
    countVertexes = controller_->getCountVertexes();
    countLines = controller_->getCountLines();
  }
  double moveX_ = 0, moveY_ = 0, moveZ_ = 0;   ///< Camera-space translation.
  double rotationX_ = 0, rotationY_ = 0, rotationZ_ = 0;  ///< Euler-angle rotation (radians).
  double size_ = 1, sizeP_ = 1, sizeL_ = 1;    ///< Uniform scale, point size, line width.
  int countVertexes = 0;                       ///< Cached vertex count for the loaded model.
  int countLines = 0;                          ///< Cached edge-line count.
  int typeP = 3;                               ///< Vertex display style (none / square / round).
  int typeL = 3;                               ///< Line display style (none / dotted / solid).
  int typeProect = 2;                          ///< Projection mode (parallel / central).
  QColor colorWidget;                          ///< Background color.
  QColor colorLines;                           ///< Edge color.
  QColor colorVertices;                        ///< Vertex point color.

 private:
  float xRot, yRot, zRot;
  QPoint mPos;
  void mousePressEvent(QMouseEvent *);
  void mouseMoveEvent(QMouseEvent *);
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;
  void drawObject();
  void position();
  void vertexesType();
  void lineType();
  void proectionType();
  s21::Controller *controller_;
  QString fileName_;
};

#endif  // GLWIDGET_H
