#include "start_window.h"
#include <QApplication>

int main(int argc, char *argv[]) {

    QApplication application(argc, argv);
    Start_Window window;

    window.showMaximized();

    return application.exec();
}
