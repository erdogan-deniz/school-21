#include "singleton.h"

namespace s21 {

void Parse::CheckFlags(QString path_to_file) {
  QFile file(path_to_file);
  if (file.open(QFile::ReadOnly)) {
    QString str;
    while (!file.atEnd()) {
      str = file.readLine();
      str = str.simplified();
      if (!str.isEmpty()) {
        if (str.at(0) == 'v') {
          if (str.at(1) == 'n') {
            vn_used = true;
          } else if (str[1] == 't') {
            vt_used = true;
          }
        }
        if (str[0] == 'f') {
          int flag_slash = 0;
          for (int i = 2; str[i] != ' '; ++i) {
            if (str[i] == '/') flag_slash += 1;
          }
          if (str.contains("//")) {
            vt_used = false;
            break;
          }
          if (flag_slash == 1) {
            vn_used = false;
            break;
          }
        }
      }
    }
  }
}

void Parse::clear() {
  facets_array_.clear();
  indices_.clear();
  vertex_.clear();
  normals_.clear();
  uvs_.clear();
  vn_used = false;
  vt_used = false;
}

void Parse::pushArr(const char **curr) {
  int vertIndex = std::stoi(*curr);
  if (vertIndex < 0) vertIndex += vertex_.size();
  facets_array_.emplace_back(vertex_[vertIndex].x());
  facets_array_.emplace_back(vertex_[vertIndex].y());
  facets_array_.emplace_back(vertex_[vertIndex].z());
  while (**curr != '/' && **curr) {
    ++*curr;
  }
  ++*curr;

  int textureIndex = 0;
  if (vt_used) textureIndex = std::stoi(*curr);
  if (textureIndex < 0) textureIndex += uvs_.size();
  facets_array_.emplace_back(uvs_[textureIndex].x());
  facets_array_.emplace_back(uvs_[textureIndex].y());
  if (**curr) {
    while (**curr != '/') {
      ++*curr;
    }
    ++*curr;
  }

  int normalIndex = 0;
  if (vn_used) normalIndex = std::stoi(*curr);
  if (normalIndex < 0) normalIndex += normals_.size();
  facets_array_.emplace_back(normals_[normalIndex].x());
  facets_array_.emplace_back(normals_[normalIndex].y());
  facets_array_.emplace_back(normals_[normalIndex].z());
}

void Parse::ParseF(QStringList str_list) {
  int counter = 0;
  QString first_elem = str_list[1];
  const char *first = first_elem.toStdString().c_str();
  const char *copy_curr = first;

  for (const auto &i : str_list) {
    const char *curr = i.toStdString().c_str();
    if (str_list.size() - 1 == 2 && std::isdigit(*curr)) {
      auto tmp = first;
      if (!std::strcmp(curr, first)) {
        pushArr(&tmp);
      }
      pushArr(&curr);
    } else {
      if (counter < 4) {
        if (std::isdigit(*curr) || *curr == '-') {
          pushArr(&curr);
        }
        ++counter;
        copy_curr = i.toStdString().c_str();
      } else {
        auto tmp = first;
        auto tmp_copy = curr;
        pushArr(&tmp);
        pushArr(&copy_curr);
        pushArr(&curr);

        copy_curr = tmp_copy;
      }
    }
  }
}

void Parse::add_pseudo_str_() {
  if (vertex_.empty()) vertex_.push_back({0, 0, 0});
  if (uvs_.empty()) uvs_.push_back({0, 0});
  if (normals_.empty()) normals_.push_back({0, 0, 0});
}

void Parse::ParseVertex_3D(QString path_to_file) {
  CheckFlags(path_to_file);
  QFile file(path_to_file);
  if (file.open(QFile::ReadOnly)) {
    add_pseudo_str_();
    QString current_string;

    while (!file.atEnd()) {
      current_string = file.readLine();
      current_string = current_string.simplified();
      QStringList numbers = current_string.split(" ");
      if (numbers[0] == "v")
        vertex_.push_back(QVector3D(numbers[1].toFloat(), numbers[2].toFloat(),
                                    numbers[3].toFloat()));
      if (numbers[0] == "vt")
        uvs_.push_back(QVector2D(numbers[1].toFloat(), numbers[2].toFloat()));
      if (numbers[0] == "vn")
        normals_.push_back(QVector3D(numbers[1].toFloat(), numbers[2].toFloat(),
                                     numbers[3].toFloat()));
      if (numbers[0] == "f") ParseF(numbers);
    }
  }

  for (int i = 0; i < facets_array_.size() / 8; i++) indices_.push_back(i);
}
}  // namespace s21
