#-------------------------------------------------
#
# Project created by QtCreator 2018-04-26T11:50:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test_qt
TEMPLATE = app

SOURCES += main.cpp \
    widget.cpp \
    camwidget.cpp
HEADERS += widget.h \
    camwidget.h
FORMS   += widget.ui

# v4l2cam
INCLUDEPATH += ../src
LIBS += -L../../build -lv4l2cam
