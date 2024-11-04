#include "window_two.h"
#include "ui_window_two.h"

//Necessary methods from C:
extern "C" long double s21_calculator(char* string, long double* x);
extern "C" long double s21_interest_rate_to_month_ratio(long double percents);
extern "C" s21_payments* s21_push_payment(long double sum, int month_duration, int month,
                                          long double percents, s21_payments* payments);
extern "C" long double s21_get_total_amount(s21_payments* payments);
extern "C" long double s21_get_total_debt(s21_payments* payments);
extern "C" int s21_string_to_int(char* string);
extern "C" int s21_is_int(char* string);
extern "C" s21_payments* s21_free_payments(s21_payments* payments);

Window_Two :: Window_Two(QWidget* parent) : QWidget(parent), ui(new Ui :: Window_Two) {
    ui->setupUi(this);

    // Hide list of payments:
    ui->list_payments->hide();
    ui->label_payments->hide();

    // Hide correction:
    ui->label_bigger_then->hide();
    ui->label_bigger_then2->hide();
    ui->label_bigger_then3->hide();

    // Close lines:
    ui->line_monthly_payments->setReadOnly(true);
    ui->line_overpayment_on_credit->setReadOnly(true);
    ui->line_total_payment->setReadOnly(true);

    // Set from start type of calculating:
    ui->box_annuity->setChecked(true);
}

Window_Two :: ~Window_Two() {
    delete ui;
}

void Window_Two :: on_line_total_credit_amount_textEdited() {
    ui->label_bigger_then->show();
}

void Window_Two :: on_line_term_textEdited() {
    ui->label_bigger_then2->show();
}

void Window_Two :: on_line_interest_rate_textEdited() {
    ui->label_bigger_then3->show();
}


QString Window_Two :: s21_long_double_to_QString(long double value) {

    std::stringstream string_value;
    string_value << value;

    return QString::fromStdString(string_value.str());
}

long double Window_Two :: s21_QString_to_long_double(QString qstring) {

    QByteArray convert_qstring = qstring.toLocal8Bit();
    char* string_convert_qstring = convert_qstring.data();

    return s21_calculator(string_convert_qstring, NULL);
}

int Window_Two :: s21_QString_to_int(QString qstring) {

    QByteArray convert_qstring = qstring.toLocal8Bit();
    char* string_convert_qstring = convert_qstring.data();

    return s21_is_int(string_convert_qstring)? s21_string_to_int(string_convert_qstring) : -1;
}

void Window_Two :: on_annuity_box_clicked() {
    ui->box_annuity->setChecked(true);
    ui->box_differentiated->setChecked(false);
}

void Window_Two :: on_box_differentiated_clicked() {
    ui->box_differentiated->setChecked(true);
    ui->box_annuity->setChecked(false);
}

void Window_Two :: on_button_calculate_clicked() {

    // Hide all corrections:
    ui->label_bigger_then->hide();
    ui->label_bigger_then2->hide();
    ui->label_bigger_then3->hide();

    // Status of calculation:
    int status = true;

    long double total_credit_amount = s21_QString_to_long_double(ui->line_total_credit_amount->text());
    int term = s21_QString_to_int(ui->line_term->text());
    long double interest_rate = s21_QString_to_long_double(ui->line_interest_rate->text());

    if (isnan(total_credit_amount) || total_credit_amount < 10 || total_credit_amount > 1000000000) {
        status = false;
        ui->line_total_credit_amount->setText("ERROR!");
    }

    if (term == -1 || term < 1 || term > 600) {
        status = false;
        ui->line_term->setText("ERROR!");
    }

    if (isnan(interest_rate) || term < 1 || term > 1000000000) {
        status = false;
        ui->line_interest_rate->setText("ERROR!");
    }

    if (status) {
        if (ui->box_annuity->isChecked() == true) {
            s21_annuity_solution(total_credit_amount, term, interest_rate);
        } else if (ui->box_differentiated->isChecked() == true) {
            s21_differtial_solution(total_credit_amount, term, interest_rate);
        }
    }
}

void Window_Two :: s21_annuity_solution(long double total_amount, int term, long double percents) {

    // Hide list:
    ui->list_payments->hide();
    ui->label_payments->hide();

    if (total_amount && term && percents) {
        long double month_payment = empty;
        long double overpay = empty;
        long double total_sum = empty;
        long double rate = pow((1 + s21_interest_rate_to_month_ratio(percents)), term);

        // Calculate:
        month_payment = total_amount * s21_interest_rate_to_month_ratio(percents) * rate/ (rate - 1);
        total_sum = month_payment * term;
        overpay = total_sum - total_amount;

        // Set lines value:
        ui->line_monthly_payments->setText(s21_long_double_to_QString(month_payment));
        ui->line_overpayment_on_credit->setText(s21_long_double_to_QString(overpay));
        ui->line_total_payment->setText(s21_long_double_to_QString(total_sum));
    }
}

void Window_Two :: s21_differtial_solution(long double total_amount, int month_duration, long double percents) {

    s21_payments* payments = NULL;

    // Hide list of payments:
    ui->list_payments->show();
    ui->label_payments->show();

    long double overpay = empty;
    long double total_sum = empty;
    int month = empty;

    if (total_amount && month_duration && percents) {
        // Clear list content:
        ui->list_payments->clear();

        // Add payments:
        while (month_duration > 0) {
            payments = s21_push_payment(total_amount, month_duration, month, percents, payments);
            --month_duration;
            ++month;
            total_amount -= payments->debt;
        }

        // Calculate result:
        total_sum = s21_get_total_amount(payments);
        overpay = total_sum - s21_get_total_debt(payments);

        // Set answers:
        ui->line_monthly_payments->setText(s21_long_double_to_QString(total_sum/month));

        ui->line_overpayment_on_credit->setText(s21_long_double_to_QString(overpay));
        ui->line_total_payment->setText(s21_long_double_to_QString(total_sum));
    }

    // Move to the last payment:
    while (payments->next)
        payments = payments->next;

    // Show payments:
    while (payments->prev) {
        ui->list_payments->addItem("  debt:    " + s21_long_double_to_QString(payments->debt) + "          "
                                   + "percents:    " + s21_long_double_to_QString(payments->percents));
        payments = payments->prev;
    }

    // Show last payment:
    ui->list_payments->addItem("  debt:    " + s21_long_double_to_QString(payments->debt) + "          "
                               + "percents:    " + s21_long_double_to_QString(payments->percents));

    payments = s21_free_payments(payments);
}
