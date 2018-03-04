#-------------------------------------------------
#
# Project created by QtCreator 2018-03-02T17:04:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OS-design
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    monitor.cpp \
    filesystem.cpp

HEADERS  += mainwindow.h \
    monitor.h \
    filesystem.h

FORMS    += mainwindow.ui
