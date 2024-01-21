QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

SOURCES += \
    ../Model/calculatormodel.cc \
    ../Model/creditmodel.cc \
    ../Model/depositmodel.cc \
    creditwindow.cc \
    depositwindow.cc \
    graphwindow.cc \
    main.cc \
    mainwindow.cc \
    qcustomplot.cc \

HEADERS += \
    ../Controller/calculatorcontroller.h \
    ../Controller/creditcontroller.h \
    ../Controller/depositcontroller.h \
    ../Model/calculatormodel.h \
    ../Model/creditmodel.h \
    ../Model/depositmodel.h \
    creditwindow.h \
    depositwindow.h \
    graphwindow.h \
    mainwindow.h \
    qcustomplot.h \

FORMS += \
    creditwindow.ui \
    depositwindow.ui \
    graphwindow.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    View.pro.user
