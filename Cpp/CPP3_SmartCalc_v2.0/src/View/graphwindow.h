#ifndef SRC_VIEW_GRAPHWINDOW_H
#define SRC_VIEW_GRAPHWINDOW_H

#include <QDialog>
#include <QVector>

#include "ui_graphwindow.h"

namespace Ui {
class GraphWindow;
}

#include "../Controller/calculatorcontroller.h"

class GraphWindow : public QDialog {
  Q_OBJECT

 public:
  // Constructor
  explicit GraphWindow(QWidget* parent = nullptr);
  // Destructor
  ~GraphWindow();
  // Draws Graph
  void DrawFinalGraph(double& x_max, double& x_min, std::string& problem,
                      std::string& value);

 private:
  Ui::GraphWindow* ui;
  QVector<double> x_{}, y_{};
  s21::CalculatorController graph_controller_{};

 private slots:
  // Edits graph widget
  void EditWidget();
};
#endif  // SRC_VIEW_GRAPHWINDOW_H
