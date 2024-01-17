QT       += core gui
QT += openglwidgets
include(../QtGifImage-master/src/gifimage/qtgifimage.pri)


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

TARGET = opengl
TEMPLATE = app

SOURCES += \
    filesbrows.cpp \
    main.cpp \
    mainwindow.cpp \
    miwidget.cpp \
    ../3d_viewer.c

HEADERS += \
    filesbrows.h \
    mainwindow.h \
    miwidget.h \
    ../3d_viewer.h

FORMS += \
    filesbrows.ui \
    mainwindow.ui

#LIBS  += -lopengl32

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

