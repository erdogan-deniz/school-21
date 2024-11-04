#ifndef CPP_3DVIEWER_V2_SRC_CONTROLLER_CONTROLLER_H_
#define CPP_3DVIEWER_V2_SRC_CONTROLLER_CONTROLLER_H_

#include "../model/transform.h"

namespace s21 {
class Controller {
 public:
  Controller(const Controller&) = delete;
  Controller(Controller&&) = delete;
  ~Controller() = default;
  Controller& operator=(const Controller&) = delete;
  Controller& operator=(Controller&&) = delete;
  static Controller* getInstance() {
    static Controller controller;
    return &controller;
  }
  void setData(Object* mod, ReadFile* parser, Transform* transform) {
    model_ = mod;
    parser_ = parser;
    transform_ = transform;
  }
  void setFilepath(const std::string& filepath) {
    parser_->setObj(filepath, model_);
    if (parser_->getCorrect()) {
      transform_->setObj(model_);
      correct_ = true;
    } else {
      correct_ = false;
    }
  }
  Object* getObject() const { return model_; }
  void moveX(double x) { transform_->moveX(x); };
  void moveY(double y) { transform_->moveY(y); };
  void moveZ(double z) { transform_->moveZ(z); };
  void rotationX(double rotate) { transform_->rotationX(rotate); };
  void rotationY(double rotate) { transform_->rotationY(rotate); };
  void rotationZ(double rotate) { transform_->rotationZ(rotate); };
  void changeSize(double size) { transform_->changeSize(size); };
  bool getCorrect() { return correct_; };
  int getCountVertexes() { return model_->getCountVertexes(); };
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
