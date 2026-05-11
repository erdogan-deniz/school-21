/**
 * @file transform.h
 * @brief Affine-transform helper applying translation, rotation, and
 *        uniform scaling to an @ref s21::Object's vertex buffer.
 *
 * Transformations are accumulated as delta state (`moveX_`,
 * `rotateX_`, `size_`, …) and applied in-place against the model's
 * flat vertex buffer. There is no separate model matrix — the
 * geometry itself is mutated.
 */

#ifndef CPP_3DVIEWER_V2_SRC_MODEL_TRANSFORM_H_
#define CPP_3DVIEWER_V2_SRC_MODEL_TRANSFORM_H_

#include <cmath>

#include "objectmod.h"

#define ACCURACY 10e-6  ///< Floating-point tolerance for rotation maths.

namespace s21 {

/**
 * @brief Per-axis affine-transform helper. Mutates the borrowed
 *        @ref Object's vertex buffer in place.
 *
 * Non-copyable / non-movable — the application owns one instance and
 * shares it with @ref Controller via raw pointer.
 */
class Transform {
 public:
  Transform() = default;
  Transform(const Transform&) = delete;
  Transform(Transform&&) = delete;
  /** @brief Construct already bound to @p obj. */
  Transform(Object* obj) : object_(obj) {};
  ~Transform() = default;

  /** @brief Re-target the helper at a different (or freshly loaded) model. */
  void setObj(Object* obj) { object_ = obj; };
  /** @brief Translate every vertex by @p x along the X axis. */
  void moveX(double x);
  /** @brief Translate every vertex by @p y along the Y axis. */
  void moveY(double y);
  /** @brief Translate every vertex by @p z along the Z axis. */
  void moveZ(double z);
  /** @brief Rotate every vertex around the X axis by @p rotate radians. */
  void rotationX(double rotate);
  /** @brief Rotate every vertex around the Y axis by @p rotate radians. */
  void rotationY(double rotate);
  /** @brief Rotate every vertex around the Z axis by @p rotate radians. */
  void rotationZ(double rotate);
  /** @brief Uniformly scale every vertex by @p size (1.0 = identity). */
  void changeSize(double size);
  /** @brief Reset accumulated translation / rotation / scale state. */
  void clear();

 private:
  Object* object_;
  double moveX_ = 0;
  double moveY_ = 0;
  double moveZ_ = 0;
  double rotateX_ = 0;
  double rotateY_ = 0;
  double rotateZ_ = 0;
  double size_ = 1;
};

}  // namespace s21

#endif  // CPP_3DVIEWER_V2_SRC_MODEL_TRANSFORM_H_
