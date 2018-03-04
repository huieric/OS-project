#-------------------------------------------------
#
# Project created by QtCreator 2018-02-28T10:22:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = lab1
TEMPLATE = app


SOURCES += main.cpp\
        showtime.cpp \
    showsum.cpp \
    showcpu.cpp \
    controller.cpp \
    monitor.cpp

HEADERS  += showtime.h \
    showsum.h \
    showcpu.h \
    controller.h \
    monitor.h

FORMS    += showtime.ui \
    showsum.ui \
    showcpu.ui \
    controller.ui \
    monitor.ui
