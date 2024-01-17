#include "graphwindow.h"

GraphWindow::GraphWindow(QWidget* parent)
    : QDialog(parent), ui(new Ui::GraphWindow) {
  ui->setupUi(this);
  setFixedSize(549, 366);
}

GraphWindow::~GraphWindow() { delete ui; }

void GraphWindow::EditWidget() {
  ui->widget->addGraph();
  ui->widget->graph(0)->addData(x_, y_);
  ui->widget->replot();
  ui->widget->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
  x_.clear();
  y_.clear();
}

void GraphWindow::DrawFinalGraph(double& x_max, double& x_min,
                                 std::string& problem, std::string& value) {
  ui->widget->clearGraphs();

  std::string str_clone = problem;
  std::string x_clone = value;

  double x_begin_ = x_min;
  double x_end_ = x_max;
  double step = (abs(x_min) + abs(x_max)) / (2 * 100000);

  ui->widget->xAxis->setRange(x_min - step, x_max + step);
  ui->widget->yAxis->setRange(x_min - step, x_max + step);

  for (double x_draw_ = x_begin_; x_draw_ <= x_end_; x_draw_ += step) {
    x_.push_back(x_draw_);
    graph_controller_.Run(problem, std::to_string(x_draw_));
    y_.push_back(graph_controller_.GetResult());
  }

  EditWidget();
}
