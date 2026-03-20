#include "objectmod.h"

namespace s21 {

void Object::normalization() {
  double minMaxX[2] = {points_.vertexes_[0]};
  double minMaxY[2] = {points_.vertexes_[1]};
  double minMaxZ[2] = {points_.vertexes_[2]};
  for (long unsigned int i = 0; i < points_.vertexes_.size(); i++) {
    if (i % 3 == 0) {
      if (points_.vertexes_[i] < minMaxX[0])
        minMaxX[0] = points_.vertexes_[i];
      else if (points_.vertexes_[i] > minMaxX[1])
        minMaxX[1] = points_.vertexes_[i];
    } else if (i % 3 == 1) {
      if (points_.vertexes_[i] < minMaxY[0])
        minMaxY[0] = points_.vertexes_[i];
      else if (points_.vertexes_[i] > minMaxY[1])
        minMaxY[1] = points_.vertexes_[i];
    } else {
      if (points_.vertexes_[i] < minMaxZ[0])
        minMaxZ[0] = points_.vertexes_[i];
      else if (points_.vertexes_[i] > minMaxZ[1])
        minMaxZ[1] = points_.vertexes_[i];
    }
  }
  double max = std::max(minMaxX[1] - minMaxX[0], minMaxY[1] - minMaxY[0]);
  max = std::max(max, minMaxZ[1] - minMaxZ[0]);
  double centrX = (minMaxX[0] + minMaxX[1]) / 2.0;
  double centrY = (minMaxY[0] + minMaxY[1]) / 2.0;
  double centrZ = (minMaxZ[0] + minMaxZ[1]) / 2.0;
  double decrease = 1.0 / max;
  for (long unsigned int i = 0; i < points_.vertexes_.size(); i++) {
    if (i % 3 == 0) {
      points_.vertexes_[i] = (points_.vertexes_[i] - centrX) * decrease;
    } else if (i % 3 == 1) {
      points_.vertexes_[i] = (points_.vertexes_[i] - centrY) * decrease;
    } else {
      points_.vertexes_[i] = (points_.vertexes_[i] - centrZ) * decrease;
    }
  }
}

void Object::clear() {
  points_.vertexes_.clear();
  points_.poligons_.clear();
  points_.count_poligons_ = 0;
  points_.count_vertex_ = 0;
}

int Object::getCountLines() {
  int countLines = points_.count_poligons_ + points_.count_vertex_ - 2;
  return countLines < 0 ? 0 : countLines;
}

void ReadFile::setObj(std::string file, Object *obj) {
  correct_ = true;
  int count_g_ = 0, count_v_ = 0, count_f_ = 0;
  points_to_sections.clear();
  obj_ = obj;
  obj_->clear();
  std::ifstream file_(file);
  if (!file_.is_open()) {
    correct_ = false;
    return;
  }
  while (std::getline(file_, str_)) {
    std::istringstream iss(str_);
    std::string prefix;
    iss >> prefix;
    if (prefix == "g") {
      count_g_++;
      if (count_v_) {
        if (points_to_sections.size()) {
          count_v_ += *(points_to_sections.end() - 1);
        }
        points_to_sections.push_back(count_v_);
        count_v_ = 0;
      }
    } else if (prefix == "v")
      count_v_++;
  }
  if (points_to_sections.size()) {
    count_v_ += *(points_to_sections.end() - 1);
  }
  points_to_sections.push_back(count_v_);
  count_v_ = 0;
  std::ifstream file2_(file);
  int it = 0;
  while (std::getline(file2_, str_)) {
    std::istringstream iss(str_);
    std::string prefix;
    iss >> prefix;

    if (prefix == "g") {
      it++;
    } else if (prefix == "v") {  // Обработка вершин
      double x, y, z;
      iss >> x >> y >> z;
      obj_->pushVetrexesPoint(x, y, z);
    } else if (prefix == "f") {  // Обработка граней
      count_f_++;
      strToPoligons(it == 0 ? 1 : it);
    }
  }
  if (!count_f_ || !points_to_sections.size()) {
    correct_ = false;
    return;
  }
  obj_->setCountPoligons(count_f_);
  obj->setCountVertex(points_to_sections[points_to_sections.size() - 1]);
  obj->normalization();
}

void ReadFile::strToPoligons(int count) {
  char ch = 0;
  std::vector<int> dop;
  int number =
      points_to_sections.size() ? points_to_sections[count - 1] + 1 : 1;
  int x = 0;
  for (it_ = str_.begin(); it_ != str_.end(); ++it_) {
    ch = (*it_);
    if ((isdigit(ch) || ch == '-') && *(it_ - 1) == ' ') {
      x = strToInt() - 1;
      if (x < 0) x += number;
      dop.push_back(x);
    }
  }
  for (auto i = dop.begin(); i != dop.end(); i++) {
    if (i != dop.begin()) {
      obj_->pushPoligonsPoint(*i);
    }
    obj_->pushPoligonsPoint(*i);
  }
  if (dop.size()) {
    obj_->pushPoligonsPoint(*dop.begin());
  }
}

int ReadFile::strToInt() {
  int res = 0;
  int i = 0;
  sscanf(&it_[0], "%d%n", &res, &i);
  it_ += (i - 1);
  return res;
}

ReadFile *ReadFile::getInstance() {
  static ReadFile parser;
  return &parser;
}

}  // namespace s21
