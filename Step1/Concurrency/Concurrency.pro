#-------------------------------------------------
#
# Project created by QtCreator 2018-02-27T09:15:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Concurrency
TEMPLATE = app


SOURCES += main.cpp\
        show_time.cpp \
    show_cpu.cpp \
    show_sum.cpp

HEADERS  += show_time.h \
    show_cpu.h \
    show_sum.h

FORMS    += show_time.ui \
    show_cpu.ui \
    show_sum.ui
