#ifndef CPP_3DVIEWER_V2_SRC_MODEL_OBJECTMOD_H_
#define CPP_3DVIEWER_V2_SRC_MODEL_OBJECTMOD_H_

#include <fstream>
#include <sstream>
#include <vector>

namespace s21 {

struct Points {
  int count_vertex_;
  int count_poligons_;
  std::vector<double> vertexes_;
  std::vector<int> poligons_;
};

class Object {
 public:
  Object() = default;
  Object(const Object&) = delete;
  Object(Object&&) = delete;
  ~Object() = default;
  void setCountVertex(int count) { points_.count_vertex_ = count; };
  void setCountPoligons(int count) { points_.count_poligons_ = count; };
  void clear();
  void pushVetrexesPoint(double x, double y, double z) {
    points_.vertexes_.push_back(x);
    points_.vertexes_.push_back(y);
    points_.vertexes_.push_back(z);
  };
  void pushPoligonsPoint(int num) { points_.poligons_.push_back(num); };
  void normalization();
  Points* getPoints() { return &points_; };
  int getCountLines();
  int getCountVertexes() { return points_.count_vertex_; };

 private:
  Points points_;
};

class ReadFile {
 public:
  ReadFile() = default;
  ReadFile(const ReadFile&) = delete;
  ReadFile(ReadFile&&) = delete;
  ~ReadFile() = default;
  static ReadFile* getInstance();
  void setObj(std::string file, Object* obj);
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
