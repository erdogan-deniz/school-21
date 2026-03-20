#ifndef WINDOW_ONE_H
#define WINDOW_ONE_H

#include <QAudioOutput>
#include <QLabel>
#include <QMovie>
#include <QUrl>
#include <QVector>
#include <QWidget>
#include <QtMultimedia/QMediaPlayer>

namespace Ui {
    class Window_One;
}

class Window_One : public QWidget {
  Q_OBJECT

 public:
  explicit Window_One(QWidget* parent = nullptr);
  ~Window_One();
  QMovie* gif;
  QLabel* label;
  QMediaPlayer* player;
  QAudioOutput* audioOutput;
  int graph_count;

 private:
  Ui ::Window_One* ui;

 private slots:
  void add_digit();
  void draw_graph(char* formula, double xBegin, double xEnd, double yBegin,
                  double yEnd, long double* X, Ui :: Window_One* sx);
};

#endif  // WINDOW_ONE_H
