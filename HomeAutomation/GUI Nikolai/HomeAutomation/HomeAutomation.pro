#-------------------------------------------------
#
# Project created by QtCreator 2016-05-18T13:31:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HomeAutomation
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    EnhedsRegister.cpp \
    unit.cpp

HEADERS  += mainwindow.h \
    EnhedsRegister.h \
    unit.h \
    CommInterface.h

FORMS    += mainwindow.ui

CONFIG  += c++11
