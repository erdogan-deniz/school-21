#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QMouseEvent>
#include <QOpenGLWidget>
#include <QWidget>
#include <QtOpenGL>

#include "../controller/controller.h"

class GLWidget : public QOpenGLWidget {
  Q_OBJECT
 public:
  explicit GLWidget(QWidget *parent = nullptr);
  void setControll(s21::Controller *control) { controller_ = control; };
  void setFileName(QString str) {
    fileName_ = str;
    controller_->setFilepath(fileName_.toStdString());
    countVertexes = controller_->getCountVertexes();
    countLines = controller_->getCountLines();
  }
  double moveX_ = 0, moveY_ = 0, moveZ_ = 0;
  double rotationX_ = 0, rotationY_ = 0, rotationZ_ = 0;
  double size_ = 1, sizeP_ = 1, sizeL_ = 1;
  int countVertexes = 0;
  int countLines = 0;
  int typeP = 3;
  int typeL = 3;
  int typeProect = 2;
  QColor colorWidget;
  QColor colorLines;
  QColor colorVertices;

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
