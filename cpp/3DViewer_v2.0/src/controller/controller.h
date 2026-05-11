/**
 * @file controller.h
 * @brief Singleton controller binding the @ref s21::Object model, the
 *        @ref s21::ReadFile parser, and the @ref s21::Transform helper
 *        to the Qt OpenGL view.
 *
 * The controller owns no state of its own beyond three borrowed
 * pointers (model / parser / transform). Every public method either
 * forwards to one of them or exposes a derived flag (`correct_`)
 * computed at the moment the file was loaded.
 */

#ifndef CPP_3DVIEWER_V2_SRC_CONTROLLER_CONTROLLER_H_
#define CPP_3DVIEWER_V2_SRC_CONTROLLER_CONTROLLER_H_

#include "../model/transform.h"

namespace s21 {

/**
 * @brief Meyers-singleton facade over @ref Object + @ref ReadFile +
 *        @ref Transform.
 *
 * Copy / move are deleted so the only access path is
 * @ref getInstance. Lifetimes of the three borrowed pointers are owned
 * by the caller that built them and passed them in via @ref setData.
 */
class Controller {
 public:
  Controller(const Controller&) = delete;
  Controller(Controller&&) = delete;
  ~Controller() = default;
  Controller& operator=(const Controller&) = delete;
  Controller& operator=(Controller&&) = delete;

  /** @brief Returns the process-wide singleton instance. */
  static Controller* getInstance() {
    static Controller controller;
    return &controller;
  }

  /**
   * @brief Wire up the borrowed model / parser / transform.
   *
   * Must be called once before any other API. The pointers are kept
   * raw — ownership stays with the caller.
   */
  void setData(Object* mod, ReadFile* parser, Transform* transform) {
    model_ = mod;
    parser_ = parser;
    transform_ = transform;
  }

  /**
   * @brief Parse an OBJ file into the model and reset the transform.
   * @param filepath Path to a Wavefront `.obj` file.
   *
   * On parse success @ref getCorrect returns true. On failure the
   * model is left in whatever state the parser produced and
   * @ref getCorrect returns false.
   */
  void setFilepath(const std::string& filepath) {
    parser_->setObj(filepath, model_);
    if (parser_->getCorrect()) {
      transform_->setObj(model_);
      correct_ = true;
    } else {
      correct_ = false;
    }
  }

  /** @brief Borrowed pointer to the loaded model (may be empty). */
  Object* getObject() const { return model_; }
  /** @brief Translate the model along the X axis by @p x units. */
  void moveX(double x) { transform_->moveX(x); };
  /** @brief Translate the model along the Y axis by @p y units. */
  void moveY(double y) { transform_->moveY(y); };
  /** @brief Translate the model along the Z axis by @p z units. */
  void moveZ(double z) { transform_->moveZ(z); };
  /** @brief Rotate the model around the X axis (radians). */
  void rotationX(double rotate) { transform_->rotationX(rotate); };
  /** @brief Rotate the model around the Y axis (radians). */
  void rotationY(double rotate) { transform_->rotationY(rotate); };
  /** @brief Rotate the model around the Z axis (radians). */
  void rotationZ(double rotate) { transform_->rotationZ(rotate); };
  /** @brief Uniform scale by @p size (1.0 = identity). */
  void changeSize(double size) { transform_->changeSize(size); };
  /** @brief True iff the last @ref setFilepath parse succeeded. */
  bool getCorrect() { return correct_; };
  /** @brief Number of vertices in the loaded model. */
  int getCountVertexes() { return model_->getCountVertexes(); };
  /** @brief Number of edge lines (computed from polygons) in the model. */
  int getCountLines() { return model_->getCountLines(); };

 private:
  Controller() = default;
  static Controller* controller_;

  Object* model_ = nullptr;
  ReadFile* parser_ = nullptr;
  Transform* transform_ = nullptr;
  bool correct_ = false;
};
}  // namespace s21

#endif  //  CPP_3DVIEWER_V2_SRC_CONTROLLER_CONTROLLER_H_
