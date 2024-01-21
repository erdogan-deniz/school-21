#include <QApplication>

#include "viewer.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  s21::Object obj;
  s21::ReadFile parser;
  s21::Transform transform;
  s21::Controller::getInstance()->setData(&obj, &parser, &transform);
  Viewer w(s21::Controller::getInstance());
  w.show();
  return a.exec();
}
