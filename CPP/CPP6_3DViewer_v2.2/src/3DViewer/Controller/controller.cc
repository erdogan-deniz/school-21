#include "controller.h"

namespace s21 {
void Controller::ParseVertex_3D(QString path_to_file) {
  return s21::Parse::GetInstance().ParseVertex_3D(path_to_file);
}

QVector<GLfloat> &Controller::GetPolygonsArray() {
  return s21::Parse::GetInstance().getFacetsArr();
}

QVector<GLuint> &Controller::GetIndices() {
  return s21::Parse::GetInstance().getIndicesArr();
}

QVector<QVector3D> &Controller::GetVertices() {
  return s21::Parse::GetInstance().getVertexArr();
}

QVector<QVector3D> &Controller::GetNormals() {
  return s21::Parse::GetInstance().getNormalsArr();
}

QVector<QVector2D> &Controller::GetUV() {
  return s21::Parse::GetInstance().getUVsArr();
}

bool Controller::NormalsUsage() { return s21::Parse::GetInstance().vn_used; }

bool Controller::TextureUsage() { return s21::Parse::GetInstance().vt_used; }

void Controller::clearArrays() { s21::Parse::GetInstance().clear(); }
}  // namespace s21
