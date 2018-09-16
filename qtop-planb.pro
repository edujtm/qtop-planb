#-------------------------------------------------
#
# Project created by QtCreator 2018-09-15T21:53:16
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = qtop-planb
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
    controller/mainwindow.cpp \
    model/processinfo.cpp \
    helper/processreader.cpp \
    helper/processadapter.cpp

HEADERS += \
    controller/mainwindow.h \
    model/processinfo.h \
    helper/processreader.h \
    helper/processadapter.h

FORMS += \
    view/mainwindow.ui

# TODO remove this if compiling works
# include(controller/controller.pri)
# include(helper/helper.pri)
# include(model/model.pri)
# include(view/view.pri)

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
