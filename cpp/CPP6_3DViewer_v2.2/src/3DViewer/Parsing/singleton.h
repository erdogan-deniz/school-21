/**
 * @file singleton.h
 * @brief Wavefront OBJ parser (@ref s21::Parse) — Meyers singleton
 *        owning the parsed vertex / normal / UV / index buffers.
 *
 * The parser is the data layer of `CPP6_3DViewer_v2.2` and feeds the
 * @ref s21::Controller facade. Supports the OBJ subset used by School
 * 21's test models: `v`, `vn`, `vt`, `f` (triangulated and quad faces).
 */

#ifndef PARSE_H
#define PARSE_H

#include <QFile>
#include <QVector3D>
#include <QVector>
#include <QWidget>
using GLfloat = float;     ///< Alias for OpenGL float without pulling `<GL/gl.h>`.
using GLuint = unsigned int;  ///< Alias for OpenGL unsigned int.

namespace s21 {

/**
 * @brief Single-instance Wavefront OBJ parser.
 *
 * Mutates its owned buffers in place. Each `ParseVertex_3D` call
 * starts with @ref clear so consumers always see a fresh model.
 */
class Parse {
 public:
  /** @brief Returns the process-wide singleton instance. */
  static Parse& GetInstance() {
    static Parse instance;
    return instance;
  }
  /**
   * @brief Parse a Wavefront OBJ file into the owned buffers.
   * @param path_to_file Absolute or working-dir-relative `.obj` path.
   */
  void ParseVertex_3D(QString path_to_file);
  /** @brief Parse one `f ...` face line, splitting on whitespace. */
  void ParseF(QStringList str);
  /**
   * @brief Push one parsed face token (`v/vt/vn`) into the index buffer.
   * @param tmp Three-element C-string array { vertex, uv, normal }.
   */
  void pushArr(const char** tmp);
  /** @brief Quick scan for `vn` / `vt` flags before the full parse. */
  void CheckFlags(QString path_to_file);
  /** @brief Reset all owned buffers and flags. */
  void clear();

  /** @brief Parsed vertex positions. */
  QVector<QVector3D>& getVertexArr() { return vertex_; }
  /** @brief Parsed vertex normals. */
  QVector<QVector3D>& getNormalsArr() { return normals_; }
  /** @brief Parsed UV coordinates. */
  QVector<QVector2D>& getUVsArr() { return uvs_; }
  /** @brief Flat interleaved float buffer suitable for `glBufferData`. */
  QVector<GLfloat>& getFacetsArr() { return facets_array_; }
  /** @brief Element-index buffer for `glDrawElements`. */
  QVector<GLuint>& getIndicesArr() { return indices_; }

  bool vn_used;  ///< True iff the OBJ file declared `vn` lines.
  bool vt_used;  ///< True iff the OBJ file declared `vt` lines.

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
