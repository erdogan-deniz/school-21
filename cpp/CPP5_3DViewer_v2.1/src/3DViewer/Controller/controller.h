/**
 * @file controller.h
 * @brief Singleton Facade between the @ref s21::Parse parser
 *        singleton and the Qt view layer (`viewer` + `scene`).
 *
 * Re-exposes the parser's read-only buffers (vertices / normals / UVs /
 * polygon facet array / index array) as references and forwards the
 * `ParseVertex_3D` entry point. The pattern is **Facade over a
 * Singleton** — the view never talks to @ref s21::Parse directly.
 */

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../Parsing/singleton.h"

//  Facade
namespace s21 {

/**
 * @brief Meyers-singleton facade over @ref Parse.
 *
 * Non-copyable; the only access path is @ref GetInstance. All getters
 * return references into the parser's owned buffers — do not retain
 * across a subsequent @ref ParseVertex_3D call as the buffers are
 * reused.
 */
class Controller {
 public:
  /** @brief Returns the process-wide singleton instance. */
  static Controller& GetInstance() {
    static Controller controller_;
    return controller_;
  }

  /** @brief Flat (x, y, z) vertex array suitable for OpenGL VBO upload. */
  QVector<GLfloat>& GetPolygonsArray();
  /** @brief Element-index array for `glDrawElements`. */
  QVector<GLuint>& GetIndices();

  /** @brief Raw vertex positions as `QVector3D`. */
  QVector<QVector3D>& GetVertices();
  /** @brief Vertex normals (if the OBJ supplied `vn` lines). */
  QVector<QVector3D>& GetNormals();
  /** @brief UV coordinates (if the OBJ supplied `vt` lines). */
  QVector<QVector2D>& GetUV();

  /** @brief True iff the last parse produced normal data. */
  bool NormalsUsage();
  /** @brief True iff the last parse produced UV data. */
  bool TextureUsage();

  /** @brief Reset all parser buffers (called before reloading a file). */
  void clearArrays();
  /** @brief Parse the Wavefront OBJ at @p path_to_file. */
  void ParseVertex_3D(QString path_to_file);

 private:
  Controller() {}
  Controller(const Controller&);
  void operator=(Controller&);
};

}  //  namespace s21

#endif
