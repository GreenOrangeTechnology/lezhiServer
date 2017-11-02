#-------------------------------------------------
#
# Project created by QtCreator 2017-05-17T14:09:43
#
#-------------------------------------------------

QT       += core gui network testlib sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = lezhiServer
TEMPLATE = app

SOURCES += main.cpp\
        model\globaldata.cpp\
        view\mainwindow.cpp \
        view\globalwidget.cpp \
        view\componentwidget.cpp \
    view/devicelist.cpp \
    configpage.cpp \
    bluetoothlight.cpp \
        view\weatherlabel.cpp \
    datacenter.cpp


HEADERS  += view\mainwindow.h \
        model\globaldata.h\
        view\globalwidget.h \
        view\componentwidget.h \
    view/devicelist.h \
    configpage.h \
    bluetoothlight.h \
        view\weatherlabel.h \
    datacenter.h

FORMS    += view\mainwindow.ui \
    bluetoothlight.ui \
            view\weatherlabel.ui \
    datacenter.ui
