#ifndef PARSE_H
#define PARSE_H

#include <QFile>
#include <QVector3D>
#include <QVector>
#include <QWidget>
using GLfloat = float;
using GLuint = unsigned int;

namespace s21 {
class Parse {
 public:
  static Parse& GetInstance() {
    static Parse instance;
    return instance;
  }
  void ParseVertex_3D(QString path_to_file);
  void ParseF(QStringList str);
  void pushArr(const char** tmp);
  void CheckFlags(QString path_to_file);
  void clear();

  QVector<QVector3D>& getVertexArr() { return vertex_; }
  QVector<QVector3D>& getNormalsArr() { return normals_; }
  QVector<QVector2D>& getUVsArr() { return uvs_; }
  QVector<GLfloat>& getFacetsArr() { return facets_array_; }
  QVector<GLuint>& getIndicesArr() { return indices_; }

  bool vn_used;
  bool vt_used;

 private:
  Parse() { clear(); }
  Parse(const Parse&);
  void operator=(Parse&);

  void add_pseudo_str_();

  QVector<GLfloat> facets_array_;
  QVector<GLuint> indices_;
  QVector<QVector3D> vertex_;
  QVector<QVector3D> normals_;
  QVector<QVector2D> uvs_;
};
}  // namespace s21

#endif  // PARSE_H
