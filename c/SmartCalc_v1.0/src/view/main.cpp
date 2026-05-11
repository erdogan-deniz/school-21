#include <QApplication>

#include "start_window.h"

int main(int argc, char *argv[]) {
  QApplication application(argc, argv);
  Start_Window window;

  window.showMaximized();

  return application.exec();
}
