#include "window_three.h"
#include "ui_window_three.h"

// Necassary methods from C:
extern "C" long double s21_get_action_amount(int from, int to, s21_payments* payments);
extern "C" long double s21_interest_rate_to_month_ratio(long double percents);
extern "C" long double s21_calculator(char* string, long double* x);
extern "C" long double s21_percents_to_ratio(long double percents);
extern "C" s21_payments* s21_push_payment(long double sum, int month_duration, int month,
                                          long double percents, s21_payments* payments);
extern "C" long double s21_get_sum(s21_payments* payments);
extern "C" long double s21_get_result_sum(s21_payments* payments);
extern "C" int s21_string_to_int(char* string);
extern "C" int s21_is_int(char* string);
extern "C" s21_payments* s21_push_deposit(long double sum, int month, s21_payments* payments);
extern "C" s21_payments* s21_free_payments(s21_payments* payments);

Window_Three :: Window_Three(QWidget* parent) : QWidget(parent), ui(new Ui :: Window_Three) {
    ui->setupUi(this);

    // Set null lists:
    set_money = NULL;
    get_money = NULL;

    // Close result lines:
    ui->line_accrued_interest->setReadOnly(true);
    ui->line_tax_amount->setReadOnly(true);
    ui->line_deposit_amount_by_the_end->setReadOnly(true);
}

Window_Three :: ~Window_Three() {

    // Clear lists:
    set_money = s21_free_payments(set_money);
    get_money = s21_free_payments(get_money);

    delete ui;
}

QString Window_Three :: s21_long_double_to_QString(long double value) {

    std :: stringstream string_value;
    string_value << value;

    return QString :: fromStdString(string_value.str());
}

long double Window_Three :: s21_QString_to_long_double(QString qstring) {

    QByteArray convert_qstring = qstring.toLocal8Bit();
    char* string_convert_qstring = convert_qstring.data();

    return s21_calculator(string_convert_qstring, NULL);
}

int Window_Three :: s21_QString_to_int(QString qstring) {

    QByteArray convert_qstring = qstring.toLocal8Bit();
    char* string_convert_qstring = convert_qstring.data();

    return s21_is_int(string_convert_qstring)? s21_string_to_int(string_convert_qstring) : -1;
}

void Window_Three :: on_button_calculate_clicked() {

    // Status of calculation:
    int status = true;

    long double deposit_amount = s21_QString_to_long_double(ui->line_deposit_amount->text());
    int deposit_term = s21_QString_to_int(ui->line_deposit_term->text());
    long double interest_rate = s21_QString_to_long_double(ui->line_interest_rate->text());
    long double tax_rate = s21_QString_to_long_double(ui->line_tax_rate->text());
    int periodicity = s21_QString_to_int(ui->line_periodicity_of->text());

    if (isnan(deposit_amount) || deposit_amount < 100 || deposit_amount  > 1000000000) {
        status = false;
        ui->line_deposit_amount->setText("ERROR!");
    }

    if (deposit_term == -1 || deposit_term < 1 || deposit_term > 600) {
        status = false;
        ui->line_deposit_term->setText("ERROR!");
    }

    if (periodicity == -1 || periodicity < 1 || periodicity > 600 || periodicity > deposit_term) {
        status = false;
        ui->line_periodicity_of->setText("ERROR!");
    }

    if (isnan(interest_rate) || interest_rate < 1 || interest_rate > 10000) {
        status = false;
        ui->line_interest_rate->setText("ERROR!");
    }

    if (isnan(tax_rate) || deposit_term > 99) {
        status = false;
        ui->line_tax_rate ->setText("ERROR!");
    }

    if (status) {
        s21_deposit_solution(deposit_amount, deposit_term, interest_rate, tax_rate, periodicity,
                             ui->checkbox_capitalization->isChecked(), set_money, get_money);
    }
}

void Window_Three :: s21_deposit_solution(long double sum, int month_duration, long double percents,
                                         long double tax_percents, int ratio_payments_mounths,
                                         bool capital_percents, s21_payments* set_money,
                                         s21_payments* get_money) {

    if (sum && month_duration && percents) {
        long double payment_sum = sum;
        long double profit = 0;
        long double taxi = 0;
        long double base_profit = 0;
        int months_period = 0;
        long double saves = empty;
//        bool key = true;

        while ((month_duration / ratio_payments_mounths) > 0) {
            long double diff_pay = 0;

            diff_pay += s21_get_action_amount(months_period, months_period + ratio_payments_mounths, set_money);
            diff_pay -= s21_get_action_amount(months_period, months_period + ratio_payments_mounths, get_money);

            months_period += ratio_payments_mounths;
            payment_sum += diff_pay;
            month_duration -= ratio_payments_mounths;
            base_profit = sum * s21_interest_rate_to_month_ratio(percents) * ratio_payments_mounths;

            // Например: делится год по 4 месяца, то за 4 месяца молучим 1/3 от начальной ставки
            base_profit += diff_pay;

//            if (payment_sum < 0) {  // Check that we get not more money then have
//                key = false;
//                break;
//            }

            if (capital_percents)
                sum += base_profit;
            else
                saves += base_profit;
        }

        profit = sum - payment_sum;
        taxi = profit * (tax_percents / 100);
        payment_sum = sum - taxi;

        if (capital_percents)
            ui->line_accrued_interest->setText(s21_long_double_to_QString(profit));
        else
            ui->line_accrued_interest->setText(s21_long_double_to_QString(saves));

        ui->line_tax_amount->setText(s21_long_double_to_QString(taxi));
        ui->line_deposit_amount_by_the_end->setText(s21_long_double_to_QString(payment_sum));
    }
}

void Window_Three :: on_button_plus_clicked() {

    // Status of calculation:
    int status = true;

    long double sum = s21_QString_to_long_double(ui->line_sum->text());
    long double deposit_amount = s21_QString_to_long_double(ui->line_deposit_amount->text());
    int month_number = s21_QString_to_int(ui->line_num_month->text());
    int months = s21_QString_to_int(ui->line_deposit_term->text());

    if (isnan(deposit_amount) || deposit_amount < 100 || deposit_amount  > 1000000000) {
        status = false;
        ui->line_deposit_amount->setText("ERROR!");
    }

    if (isnan(sum) || sum < 100 || sum > deposit_amount) {
        status = false;
        ui->line_sum->setText("ERROR!");
    }

    if (months == -1 || months < 1) {
        status = false;
        ui->line_num_month->setText("ERROR!");
    }

    if (month_number == -1 || month_number < 1 || month_number > months) {
        status = false;
        ui->line_deposit_term->setText("ERROR!");
    }

    if (status) {
        get_money = s21_push_deposit(sum, month_number, get_money);
        ui->list_with->addItem("  ");
        ui->list_with->addItem("  sum:    " + s21_long_double_to_QString(get_money->debt) + "        "
                               + "month number:    " + s21_long_double_to_QString(get_money->month_number));
    }
}

void Window_Three :: on_button_plus2_clicked() {

    // Status of calculation:
    int status = true;

    long double sum = s21_QString_to_long_double(ui->line_sum2->text());
    long double deposit_amount = s21_QString_to_long_double(ui->line_deposit_amount->text());
    int month_number = s21_QString_to_int(ui->line_num_month2->text());
    int months = s21_QString_to_int(ui->line_deposit_term->text());

    if (isnan(deposit_amount) || deposit_amount < 100 || deposit_amount  > 1000000000) {
        status = false;
        ui->line_deposit_amount->setText("ERROR!");
    }

    if (isnan(sum) || sum < 100 || sum > 1000000000) {
    status = false;
    ui->line_sum2->setText("ERROR!");
    }

    if (months == -1 || months < 1) {
        status = false;
        ui->line_deposit_term->setText("ERROR!");
    }

    if (month_number == -1 || month_number < 1 || month_number > months) {
        status = false;
        ui->line_num_month2->setText("ERROR!");
    }

    if (status) {
        set_money = s21_push_deposit(sum, month_number, set_money);
        ui->list_repl->addItem("   ");
        ui->list_repl->addItem("  sum:    " + s21_long_double_to_QString(set_money->debt) + "        "
                             + "month number:    " + s21_long_double_to_QString(set_money->month_number));
    }
}
