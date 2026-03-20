QT       += core gui opengl widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += openglwidgets

CONFIG += c++17 warn_off

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include(QtGifImage/gifimage/qtgifimage.pri)

SOURCES += \
    ../model/objectmod.cc \
    ../model/transform.cc \
    glwidget.cc \
    main.cpp \
    viewer.cc

HEADERS += \
    ../controller/controller.h \
    ../model/objectmod.h \
    ../model/transform.h \
    QtGifImage/gifimage/qgifimage.h \
    glwidget.h \
    viewer.h

FORMS += \
    viewer.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
