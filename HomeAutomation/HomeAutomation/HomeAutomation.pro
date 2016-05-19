#-------------------------------------------------
#
# Project created by QtCreator 2016-05-19T14:52:30
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HomeAutomation
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    CommInterface.cpp \
    Entry.cpp \
    Unit.cpp \
    UnitRegister.cpp

HEADERS  += mainwindow.h \
    CommInterface.h \
    Entry.h \
    Unit.h \
    UnitRegister.h

FORMS    += mainwindow.ui

CONFIG += c++11
