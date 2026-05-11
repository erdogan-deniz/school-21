/**
 * @file window_one.h
 * @brief Calculator panel — number pad, expression entry, and 2-D plot.
 *
 * Wraps the C entry point @ref s21_calculator from
 * `s21_calculator.h` behind Qt slots. The widget also hosts an
 * animated GIF banner, sound effects via `QMediaPlayer`, and a
 * `qcustomplot` chart for `y = f(x)`.
 */

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

/**
 * @brief Calculator panel widget.
 *
 * Holds Qt media objects, an `int` graph counter to disambiguate
 * overlaid plots, and the auto-generated `Ui::Window_One` form.
 */
class Window_One : public QWidget {
  Q_OBJECT

 public:
  explicit Window_One(QWidget* parent = nullptr);
  ~Window_One();
  QMovie* gif;                  ///< Animated banner.
  QLabel* label;                ///< Banner host widget.
  QMediaPlayer* player;         ///< Sound-effect player.
  QAudioOutput* audioOutput;    ///< Audio sink for @ref player.
  int graph_count;              ///< Number of plotted graphs (for legend).

 private:
  Ui ::Window_One* ui;

 private slots:
  /** @brief Append the clicked button's digit / operator to the expression. */
  void add_digit();
  /**
   * @brief Sample @p formula across `[xBegin, xEnd]` and plot the
   *        resulting curve via qcustomplot.
   * @param formula Infix expression containing `x`.
   * @param X       Out-array of x-values (length defined by the UI).
   */
  void draw_graph(char* formula, double xBegin, double xEnd, double yBegin,
                  double yEnd, long double* X, Ui ::Window_One* sx);
};

#endif  // WINDOW_ONE_H
