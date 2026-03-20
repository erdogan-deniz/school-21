#include "glwidget.h"

GLWidget::GLWidget(QWidget* parent) : QOpenGLWidget{parent} {}

void GLWidget::initializeGL() { glEnable(GL_DEPTH_TEST); }

void GLWidget::resizeGL(int w, int h) { glViewport(0, 0, w, h); }

void GLWidget::paintGL() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(colorWidget.redF(), colorWidget.greenF(), colorWidget.blueF(),
               0);
  glMatrixMode(GL_MODELVIEW);
  if (controller_->getCorrect()) {
    glLoadIdentity();
    proectionType();
    glTranslated(0, 0, -3);
    glRotatef(xRot, 1, 0, 0);
    glRotatef(yRot, 0, 1, 0);
    position();
    drawObject();
    glEnd();
    update();
  }
}

void GLWidget::proectionType() {
  if (typeProect == 1) {
    glFrustum(-1, 1, -1, 1, 1, 99999);
  } else {
    glOrtho(-1, 1, -1, 1, 1, 99999);
  }
}

void GLWidget::position() {
  controller_->moveX(moveX_);
  controller_->moveY(moveY_);
  controller_->moveZ(moveZ_);
  controller_->rotationX(rotationX_);
  controller_->rotationY(rotationY_);
  controller_->rotationZ(rotationZ_);
  controller_->changeSize(size_);
}

void GLWidget::drawObject() {
  glVertexPointer(3, GL_DOUBLE, 0,
                  controller_->getObject()->getPoints()->vertexes_.data());
  glEnableClientState(GL_VERTEX_ARRAY);

  if (typeP != 1) {
    vertexesType();
  }
  if (typeL != 1) {
    lineType();
  }
  glDisableClientState(GL_VERTEX_ARRAY);
}

void GLWidget::vertexesType() {
  if (typeP == 3) {
    glEnable(GL_POINT_SMOOTH);
  } else {
    glDisable(GL_POINT_SMOOTH);
  }
  glPointSize(sizeP_);
  glColor3f(colorVertices.redF(), colorVertices.greenF(),
            colorVertices.blueF());
  glDrawArrays(GL_POINTS, 0,
               controller_->getObject()->getPoints()->count_vertex_);
}

void GLWidget::lineType() {
  if (typeL == 2) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(4, 0x00FF);
  } else {
    glDisable(GL_LINE_STIPPLE);
  }
  glColor3f(colorLines.redF(), colorLines.greenF(), colorLines.blueF());
  glLineWidth(sizeL_);
  glDrawElements(
      GL_LINES, controller_->getObject()->getPoints()->poligons_.size(),
      GL_UNSIGNED_INT, controller_->getObject()->getPoints()->poligons_.data());
}

void GLWidget::mousePressEvent(QMouseEvent* mo) { mPos = mo->pos(); }

void GLWidget::mouseMoveEvent(QMouseEvent* mo) {
  xRot = 1 / M_PI * (mo->pos().y() - mPos.y());
  yRot = 1 / M_PI * (mo->pos().x() - mPos.x());
  update();
}
