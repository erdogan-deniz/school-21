#include "transform.h"

namespace s21 {
void Transform::clear() {
  moveX_ = moveY_ = moveZ_ = 0;
  rotateX_ = rotateY_ = rotateZ_ = 0;
  size_ = 1;
}

void Transform::moveX(double x) {
  if (fabs(x - moveX_) <= ACCURACY) return;
  for (long unsigned int i = 0; i < object_->getPoints()->vertexes_.size(); ++i) {
    if (i % 3 == 0) object_->getPoints()->vertexes_[i] += (x - moveX_);
  }
  moveX_ = x;
}

void Transform::moveY(double y) {
  if (fabs(y - moveY_) <= ACCURACY) return;
  for (long unsigned int i = 0; i < object_->getPoints()->vertexes_.size(); ++i) {
    if (i % 3 == 1) object_->getPoints()->vertexes_[i] += (y - moveY_);
  }
  moveY_ = y;
}

void Transform::moveZ(double z) {
  if (fabs(z - moveZ_) <= ACCURACY) return;
  for (long unsigned int i = 0; i < object_->getPoints()->vertexes_.size(); ++i) {
    if (i % 3 == 2) object_->getPoints()->vertexes_[i] += (z - moveZ_);
  }
  moveZ_ = z;
}

void Transform::rotationX(double rotate) {
  if (fabs(rotate - rotateX_) <= ACCURACY) return;
  double Y = 0;
  double Z = 0;
  for (long unsigned int i = 0; i < object_->getPoints()->vertexes_.size(); i++) {
    if (i % 3 == 0) {
      Y = object_->getPoints()->vertexes_[i + 1];
      Z = object_->getPoints()->vertexes_[i + 2];
      object_->getPoints()->vertexes_[i + 1] =
          Y * cos(rotate - rotateX_) + Z * sin(rotate - rotateX_);
      object_->getPoints()->vertexes_[i + 2] =
          (-Y) * sin(rotate - rotateX_) + Z * cos(rotate - rotateX_);
    }
  }
  rotateX_ = rotate;
}

void Transform::rotationY(double rotate) {
  if (fabs(rotate - rotateY_) <= ACCURACY) return;
  double X = 0;
  double Z = 0;
  for (long unsigned int i = 0; i < object_->getPoints()->vertexes_.size(); i++) {
    if (i % 3 == 0) {
      X = object_->getPoints()->vertexes_[i];
      Z = object_->getPoints()->vertexes_[i + 2];
      object_->getPoints()->vertexes_[i] =
          X * cos(rotate - rotateY_) + Z * sin(rotate - rotateY_);
      object_->getPoints()->vertexes_[i + 2] =
          (-X) * sin(rotate - rotateY_) + Z * cos(rotate - rotateY_);
    }
  }
  rotateY_ = rotate;
}

void Transform::rotationZ(double rotate) {
  if (fabs(rotate - rotateZ_) <= ACCURACY) return;
  double X = 0;
  double Y = 0;
  for (long unsigned int i = 0; i < object_->getPoints()->vertexes_.size(); i++) {
    if (i % 3 == 0) {
      X = object_->getPoints()->vertexes_[i];
      Y = object_->getPoints()->vertexes_[i + 1];
      object_->getPoints()->vertexes_[i] =
          X * cos(rotate - rotateZ_) + Y * sin(rotate - rotateZ_);
      object_->getPoints()->vertexes_[i + 1] =
          (-X) * sin(rotate - rotateZ_) + Y * cos(rotate - rotateZ_);
    }
  }
  rotateZ_ = rotate;
}

void Transform::changeSize(double size) {
  if (size <= 0.1) return;
  for (long unsigned int i = 0; i < object_->getPoints()->vertexes_.size(); i++) {
    object_->getPoints()->vertexes_[i] =
        object_->getPoints()->vertexes_[i] / size_ * size;
  }
  size_ = size;
}

}  // namespace s21
