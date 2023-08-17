#include "window_one.h"
#include "ui_window_one.h"

// Necessary methods from C:
extern "C" int s21_validation (char* string);
extern "C" long double s21_calculator(char* string, long double* x);
extern "C" int s21_have_x(char* string);

Window_One :: Window_One(QWidget* parent) : QWidget(parent), ui(new Ui :: Window_One) {
    ui->setupUi(this);

    // Music:
    player = new QMediaPlayer;
    audioOutput = new QAudioOutput;
    player->setAudioOutput(audioOutput);
    player->setSource(QUrl::fromLocalFile("sounds/uzi.mp3"));
    audioOutput->setVolume(30);
    player->play();

    // Gif:
    label = new QLabel(this);
    gif = new QMovie("gifs/waiting.gif");
    label->setMovie(gif);
    label->resize(150, 150);
    label->setGeometry(1455, 15, 120, 95);
    label->show();
    gif->start();

    // At start hide plot:
    ui->plot->hide();

    // Numbers buttons:
    connect(ui->button_0, SIGNAL(clicked()), this, SLOT(add_digit()));
    connect(ui->button_1, SIGNAL(clicked()), this, SLOT(add_digit()));
    connect(ui->button_2, SIGNAL(clicked()), this, SLOT(add_digit()));
    connect(ui->button_3, SIGNAL(clicked()), this, SLOT(add_digit()));
    connect(ui->button_4, SIGNAL(clicked()), this, SLOT(add_digit()));
    connect(ui->button_5, SIGNAL(clicked()), this, SLOT(add_digit()));
    connect(ui->button_6, SIGNAL(clicked()), this, SLOT(add_digit()));
    connect(ui->button_7, SIGNAL(clicked()), this, SLOT(add_digit()));
    connect(ui->button_8, SIGNAL(clicked()), this, SLOT(add_digit()));
    connect(ui->button_9, SIGNAL(clicked()), this, SLOT(add_digit()));

    // X button:
    connect(ui->button_x, SIGNAL(clicked()), this, SLOT(add_digit()));

    // Point button:
    connect(ui->button_point, SIGNAL(clicked()), this, SLOT(add_digit()));

    // Brackets buttons:
    connect(ui->button_lb, SIGNAL(clicked()), this, SLOT(add_digit()));
    connect(ui->button_rb, SIGNAL(clicked()), this, SLOT(add_digit()));

    // Operations buttons:
    connect(ui->button_plus, SIGNAL(clicked()), this, SLOT(add_digit()));
    connect(ui->button_minus, SIGNAL(clicked()), this, SLOT(add_digit()));
    connect(ui->button_mult, SIGNAL(clicked()), this, SLOT(add_digit()));
    connect(ui->button_div, SIGNAL(clicked()), this, SLOT(add_digit()));
    connect(ui->button_pow, SIGNAL(clicked()), this, SLOT(add_digit()));
    connect(ui->button_mod, SIGNAL(clicked()), this, SLOT(add_digit()));

    // Functions buttons:
    connect(ui->button_sin, SIGNAL(clicked()), this, SLOT(add_digit()));
    connect(ui->button_cos, SIGNAL(clicked()), this, SLOT(add_digit()));
    connect(ui->button_tan, SIGNAL(clicked()), this, SLOT(add_digit()));
    connect(ui->button_log, SIGNAL(clicked()), this, SLOT(add_digit()));
    connect(ui->button_ln, SIGNAL(clicked()), this, SLOT(add_digit()));
    connect(ui->button_asin, SIGNAL(clicked()), this, SLOT(add_digit()));
    connect(ui->button_acos, SIGNAL(clicked()), this, SLOT(add_digit()));
    connect(ui->button_atan, SIGNAL(clicked()), this, SLOT(add_digit()));
    connect(ui->button_sqrt, SIGNAL(clicked()), this, SLOT(add_digit()));

    // Clear button:
    connect(ui->button_clear, SIGNAL(clicked()), this, SLOT(add_digit()));

    // Equal button:
    connect(ui->button_eq, SIGNAL(clicked()), this, SLOT(add_digit()));
}

Window_One :: ~Window_One() {
    delete ui;
}

void Window_One :: add_digit() {

    // Result:
    long double result = NAN;
    long double x_value = NAN;
    double xBegin = NAN;
    double xEnd = NAN;
    double yBegin = NAN;
    double yEnd = NAN;

    // Hide gif if we press button:
    gif->stop();
    label->hide();

    // Take signal from buttons and convert to Qstring:
    QPushButton* button = (QPushButton*)sender();
    QString input_value = button->text();

    // Chek result:
    QByteArray convert_result = ui->Result->text().toLocal8Bit();
    char* string_value = convert_result.data();
    int input_correct = s21_validation(string_value);

    // Take x value from x live and convert to Qstring:
    QString input_x = ui->line_x->text();
    QByteArray convert_input_x = input_x.toLocal8Bit();
    char* string_x = convert_input_x.data();
    int x_correct = s21_validation(string_x);
    x_value = s21_calculator(string_value, NULL);

    // Take x_from convert to QString:
    QString input_x_from = ui->line_x_from->text();
    QByteArray convert_input_x_from = input_x_from.toLocal8Bit();
    char* string_x_from = convert_input_x_from.data();
    int x_def = s21_validation(string_x_from);

    // Take x_to convert to QString:
    QString input_x_to = ui->line_x_to->text();
    QByteArray convert_input_x_to = input_x_to.toLocal8Bit();
    char* string_x_to = convert_input_x_to.data();
    x_def *= s21_validation(string_x_from);

    // Take y_from convert to QString:
    QString input_y_from = ui->line_y_from->text();
    QByteArray convert_input_y_from = input_y_from.toLocal8Bit();
    char* string_y_from = convert_input_y_from.data();
    int y_def = s21_validation(string_y_from);

    // Take y_to convert to QString:
    QString input_y_to = ui->line_y_to->text();
    QByteArray convert_input_y_to = input_y_to.toLocal8Bit();
    char* string_y_to = convert_input_y_to.data();
    y_def *= s21_validation(string_y_from);

    bool loc = true;

    // Check correction of inputs data for plot:
    if (input_value == "=" && s21_have_x(string_value)) {
        if (!input_x.isEmpty()) {
            if (x_correct)
                x_value = s21_calculator(string_x, &x_value);
            else {
                loc = false;
                ui->line_x->setText("ERROR!");
            }
        }

        if (x_def) {
            xBegin = (double)s21_calculator(string_x_from, NULL);
            xEnd = (double)s21_calculator(string_x_to, NULL);

            if (fabs(xBegin) > 1000000 || fabs(xEnd) > 1000000) {
                loc = false;
                ui->line_x_from->setText("ERROR!");
                ui->line_x_to->setText("ERROR!");
            }
        } else {
            loc = false;
            ui->line_x_from->setText("ERROR!");
            ui->line_x_to->setText("ERROR!");
        }

        if (y_def) {
            yBegin = (double)s21_calculator(string_y_from, NULL);
            yEnd = (double)s21_calculator(string_y_to, NULL);

            if (fabs(yBegin) > 1000000 || fabs(yEnd) > 1000000) {
                loc = false;
                ui->line_y_from->setText("ERROR!");
                ui->line_y_to->setText("ERROR!");
            }
        } else {
            loc = false;
            ui->line_y_from->setText("ERROR!");
            ui->line_y_to->setText("ERROR!");
        }
    }

    // Check all solutions:
    if (input_value == "clear") {
        ui->Result->setText("");
        ui->line_x->setText("");
        label->show();
        gif->start();
        ui->plot->hide();

        if  (!ui->line_x_from->isReadOnly()) {
            ui->line_x_from->setText("");
            ui->line_x_to->setText("");
            ui->line_y_from->setText("");
            ui->line_y_to->setText("");
        }
    } else if (ui->Result->text() == "ERROR!") {
        if (input_value == "clear"){
            ui->Result->setText("");
            ui->line_x->setText("");
            label->show();
            gif->start();
            ui->plot->hide();

            if (!ui->line_x_from->isReadOnly()){
                ui->line_x_from->setText("");
                ui->line_x_to->setText("");
                ui->line_y_from->setText("");
                ui->line_y_to->setText("");
            }
        }
    } else if (input_value == "=") {
        if (input_correct) {
            if (s21_have_x(string_value)) {
                if (input_x.isEmpty() && loc) {
                    ui->line_x_from->setReadOnly(true);
                    ui->line_x_to->setReadOnly(true);
                    ui->line_y_from->setReadOnly(true);
                    ui->line_y_to->setReadOnly(true);
                    draw_graph(string_value, xBegin, xEnd, yBegin, yEnd, NULL, ui);
                    ui->Result->setText("nan");
                } else if (loc) {
                    ui->line_x_from->setReadOnly(true);
                    ui->line_x_to->setReadOnly(true);
                    ui->line_y_from->setReadOnly(true);
                    ui->line_y_to->setReadOnly(true);
                    draw_graph(string_value, xBegin, xEnd, yBegin, yEnd, &x_value, ui);
                    result = s21_calculator(string_value, &x_value);
                    ui->Result->setText(QString :: fromStdString(std::to_string(result)));
                } else {
                    ui->Result->setText("ERROR!");
                }
            } else {
                result = s21_calculator(string_value, NULL);
                ui->Result->setText(QString::fromStdString(std :: to_string(result)));
            }
        } else {
            ui->Result->setText("ERROR!");
        }
    } else {
        QString tmp = ui->Result->text() + input_value;
        ui->Result->setText(tmp);
    }
}

void Window_One :: draw_graph(char* formula, double xBegin, double xEnd, double yBegin,
                              double yEnd, long double* X, Ui :: Window_One* ui) {

    double h = 0.1;
    int N = (xEnd - xBegin) / h + 2;
    QVector <double> x, y;

    // Reset graph:
    ui->plot->clearFocus();
    ui->plot->clearGraphs();
    ui->plot->clearItems();

    // Swap min and max x:
    if (xBegin > xEnd) {
        double tmp = xBegin;
        xBegin = xEnd;
        xEnd = tmp;
    }

    // Swap min and max y:
    if (yBegin > yEnd) {
        double tmp = yBegin;
        yBegin = yEnd;
        yEnd = tmp;
    }

    // Calculate necessary points for plot:
    for (double ix = xBegin; ix <= xEnd; ix += h) {
        x.push_back(ix);

        if (X) {
            y.push_back((double)s21_calculator(formula, X));
        } else {
                long double tmp = (long double) ix;
                y.push_back((double)s21_calculator(formula, &tmp));
            }
        }

    // Draw plot:
    ui->plot->addGraph();
    ui->plot->graph(0)->addData(x, y);
    ui->plot->replot();
    ui->plot->xAxis->setRange(xBegin, xEnd);
    ui->plot->yAxis->setRange(yBegin, yEnd);
    ui->plot->show();
}
