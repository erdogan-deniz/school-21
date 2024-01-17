#ifndef CPP_3DVIEWER_V2_SRC_MODEL_TRANSFORM_H_
#define CPP_3DVIEWER_V2_SRC_MODEL_TRANSFORM_H_

#include <cmath>

#include "objectmod.h"

#define ACCURACY 10e-6

namespace s21 {

class Transform {
 public:
  Transform() = default;
  Transform(const Transform&) = delete;
  Transform(Transform&&) = delete;
  Transform(Object* obj) : object_(obj){};
  ~Transform() = default;
  void setObj(Object* obj) { object_ = obj; };
  void moveX(double x);
  void moveY(double y);
  void moveZ(double z);
  void rotationX(double rotate);
  void rotationY(double rotate);
  void rotationZ(double rotate);
  void changeSize(double size);
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
