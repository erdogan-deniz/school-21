QT += core gui printsupport network multimedia

greaterThan(QT_MAJOR_VERSION, 4) : QT += widgets

CONFIG += c++17

SOURCES += \
    ../additional/s21_char_to_int.c \
    ../additional/s21_char_to_string.c \
    ../additional/s21_count_points.c \
    ../additional/s21_get_priority_token.c \
    ../additional/s21_get_value.c \
    ../additional/s21_have_number.c \
    ../additional/s21_have_point.c \
    ../additional/s21_have_x.c \
    ../additional/s21_is_int.c \
    ../additional/s21_is_sign.c \
    ../additional/s21_is_unary_token.c \
    ../additional/s21_is_valid_symbol.c \
    ../additional/s21_set_value.c \
    ../additional/s21_string_to_int.c \
    ../additional/s21_string_to_long_double.c \
    ../bonus/s21_clear_payment.c \
    ../bonus/s21_create_payment.c \
    ../bonus/s21_create_payments.c \
    ../bonus/s21_fiil_deposit.c \
    ../bonus/s21_fiil_payment.c \
    ../bonus/s21_free_payments.c \
    ../bonus/s21_get_action_amount.c \
    ../bonus/s21_get_payment_amount.c \
    ../bonus/s21_get_total_amount.c \
    ../bonus/s21_get_total_debt.c \
    ../bonus/s21_interest_rate_to_month_ratio.c \
    ../bonus/s21_pop_payment.c \
    ../bonus/s21_push_deposit.c \
    ../bonus/s21_push_payment.c \
    ../calculate/s21_calculate.c \
    ../list/s21_clear_node_list.c \
    ../list/s21_create_list.c \
    ../list/s21_create_node_list.c \
    ../list/s21_fill_node_list.c \
    ../list/s21_free_list.c \
    ../list/s21_free_node_list.c \
    ../list/s21_pop_list.c \
    ../list/s21_push_list.c \
    ../list/s21_put_x_value.c \
    ../list/s21_size_list.c \
    ../list/s21_stack_to_list.c \
    ../parser/s21_parser.c \
    ../s21_calculator.c \
    ../stack/s21_clear_node_stack.c \
    ../stack/s21_create_node_stack.c \
    ../stack/s21_create_stack.c \
    ../stack/s21_fill_node_stack.c \
    ../stack/s21_free_stack.c \
    ../stack/s21_get_node_priority.c \
    ../stack/s21_pop_stack.c \
    ../stack/s21_push_stack.c \
    ../transform/s21_delete_spaces.c \
    ../validation/s21_acos_asin_atan_validation.c \
    ../validation/s21_binary_operator_validation.c \
    ../validation/s21_cos_validation.c \
    ../validation/s21_double_number_validation.c \
    ../validation/s21_double_symbol_validation.c \
    ../validation/s21_empty_brackets_validation.c \
    ../validation/s21_glued_values_validation.c \
    ../validation/s21_is_equality_brackets.c \
    ../validation/s21_is_valid_string.c \
    ../validation/s21_ln_log_validation.c \
    ../validation/s21_mod_validation.c \
    ../validation/s21_number_validation.c \
    ../validation/s21_sin_sqrt_validation.c \
    ../validation/s21_tan_validation.c \
    ../validation/s21_unary_operator_validation.c \
    ../validation/s21_validation.c \
    main.cpp \
    qcustomplot.cpp \
    start_window.cpp \
    window_one.cpp \
    window_three.cpp \
    window_two.cpp

HEADERS += \
    ../additional/s21_additional.h \
    ../bonus/s21_bonus.h \
    ../calculate/s21_calculate.h \
    ../list/s21_list.h \
    ../parser/s21_parser.h \
    ../s21_calculator.h \
    ../s21_main.h \
    ../stack/s21_stack.h \
    ../transform/s21_transform.h \
    ../validation/s21_validation.h \
    qcustomplot.h \
    start_window.h \
    ui_start_window.h \
    ui_window_one.h \
    ui_window_three.h \
    ui_window_two.h \
    window_one.h \
    window_three.h \
    window_two.h

TARGET = view

FORMS += \
    start_window.ui \
    window_one.ui \
    window_three.ui \
    window_two.ui



win32:RC_FILE = file.rc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ../Makefile \
    ../Makefilezxc \
    .qmake.stash \
    file.rc \
    images/background.jpg \
    view.pro.user
