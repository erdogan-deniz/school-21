#include "start_window.h"
#include "ui_start_window.h"

Start_Window :: Start_Window(QWidget* parent) : QMainWindow(parent), ui(new Ui :: Start_Window) {
    ui->setupUi(this);
}

Start_Window :: ~Start_Window() {
    delete ui;
}

void Start_Window :: on_Calculator_Button_clicked() {
    calculator.showMaximized();
    this->close();    
}


void Start_Window :: on_Credit_Button_clicked() {
    credit_calculator.showMaximized();
    this->close();
}


void Start_Window :: on_Deposit_Button_clicked() {
    deposit_calculator.showMaximized();
    this->close();
}

