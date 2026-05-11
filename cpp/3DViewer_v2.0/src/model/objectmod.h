/**
 * @file objectmod.h
 * @brief 3D model representation (@ref s21::Object) and Wavefront OBJ
 *        parser (@ref s21::ReadFile).
 *
 * The model stores vertices as a flat `vector<double>` (x, y, z
 * triples) and polygon edges as a flat `vector<int>` index buffer —
 * the layout the OpenGL view consumes directly. The parser is a
 * Meyers singleton that mutates a borrowed @ref Object in place.
 */

#ifndef CPP_3DVIEWER_V2_SRC_MODEL_OBJECTMOD_H_
#define CPP_3DVIEWER_V2_SRC_MODEL_OBJECTMOD_H_

#include <fstream>
#include <sstream>
#include <vector>

namespace s21 {

/**
 * @brief POD container backing @ref Object: vertex and polygon-index
 *        buffers plus their counts.
 */
struct Points {
  int count_vertex_;                ///< Number of vertices (`v` lines in OBJ).
  int count_poligons_;              ///< Number of polygon faces (`f` lines).
  std::vector<double> vertexes_;    ///< Flat (x, y, z, x, y, z, ...) buffer.
  std::vector<int> poligons_;       ///< Flat edge-index buffer for line drawing.
};

/**
 * @brief Geometry container — the **M** of `3DViewer_v2.0`'s MVC.
 *
 * Non-copyable / non-movable: lifetime is owned by the application
 * entry point and a raw pointer is handed to @ref Controller and
 * @ref ReadFile.
 */
class Object {
 public:
  Object() = default;
  Object(const Object&) = delete;
  Object(Object&&) = delete;
  ~Object() = default;

  /** @brief Set the vertex count (called by the parser). */
  void setCountVertex(int count) { points_.count_vertex_ = count; };
  /** @brief Set the polygon-face count (called by the parser). */
  void setCountPoligons(int count) { points_.count_poligons_ = count; };
  /** @brief Drop all geometry and reset counts to zero. */
  void clear();
  /**
   * @brief Append one (x, y, z) vertex to the flat buffer.
   *
   * Three `push_back`s into @ref Points::vertexes_ — keeping vertex
   * storage contiguous for direct OpenGL upload.
   */
  void pushVetrexesPoint(double x, double y, double z) {
    points_.vertexes_.push_back(x);
    points_.vertexes_.push_back(y);
    points_.vertexes_.push_back(z);
  };
  /** @brief Append a single polygon-vertex index to the index buffer. */
  void pushPoligonsPoint(int num) { points_.poligons_.push_back(num); };
  /**
   * @brief Center the model on the origin and normalize its bounding
   *        box to the unit cube.
   *
   * Called after parsing so different models render at a comparable
   * on-screen size regardless of their authoring units.
   */
  void normalization();
  /** @brief Borrowed pointer to the underlying @ref Points buffer. */
  Points* getPoints() { return &points_; };
  /** @brief Number of edge lines derived from the polygon index buffer. */
  int getCountLines();
  /** @brief Number of vertices in the model. */
  int getCountVertexes() { return points_.count_vertex_; };

 private:
  Points points_;
};

/**
 * @brief Wavefront OBJ parser — Meyers singleton, single-shot per file.
 *
 * Reads the whole file into @ref str_ then walks it character-by-
 * character through @ref it_, dispatching `v ...` lines to vertex
 * accumulation and `f ...` lines to @ref strToPoligons. On any
 * unexpected token @ref correct_ flips to false and the rest of the
 * file is still consumed but ignored.
 */
class ReadFile {
 public:
  ReadFile() = default;
  ReadFile(const ReadFile&) = delete;
  ReadFile(ReadFile&&) = delete;
  ~ReadFile() = default;

  /** @brief Process-wide singleton instance. */
  static ReadFile* getInstance();
  /**
   * @brief Parse @p file into @p obj.
   * @param file Path to a Wavefront `.obj` file.
   * @param obj  Borrowed @ref Object to be filled. Reset first.
   */
  void setObj(std::string file, Object* obj);
  /** @brief True iff the last @ref setObj call succeeded. */
  bool getCorrect() { return correct_; };

 private:
  Object* obj_;
  bool correct_ = true;
  std::string str_;
  std::string::iterator it_;
  std::vector<int> points_to_sections;
  void strToPoligons(int count);
  int strToInt();
};

}  // namespace s21

#endif  // CPP_3DVIEWER_V2_SRC_MODEL_OBJECTMOD_H_
