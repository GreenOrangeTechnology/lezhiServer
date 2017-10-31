#-------------------------------------------------
#
# Project created by QtCreator 2017-05-17T14:09:43
#
#-------------------------------------------------

QT       += core gui network testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = lezhiServer
TEMPLATE = app

SOURCES += main.cpp\
        view\mainwindow.cpp \
        view\globalwidget.cpp \
        view\componentwidget.cpp
        view\weatherlabel.cpp

HEADERS  += mainwindow.h \
        view\globalwidget.h \
        view\componentwidget.h
        view\weatherlabel.h

FORMS    += mainwindow.ui
            weatherlabel.ui
