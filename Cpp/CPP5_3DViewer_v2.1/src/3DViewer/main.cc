#include <QApplication>

#include "GLWidget/scene.h"
#include "Viewer/viewer.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  viewer w;
  w.show();
  return a.exec();
}
