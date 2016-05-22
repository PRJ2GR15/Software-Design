#-------------------------------------------------
#
# Project created by QtCreator 2016-05-19T22:33:59
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
    UnitRegister.cpp \
    mainmenu.cpp \
    removeunit.cpp \
    basemenu.cpp \
    addunit.cpp \
    editentry.cpp \
    editunit.cpp \
    addentry.cpp \
    editoldentry.cpp

HEADERS  += mainwindow.h \
    CommInterface.h \
    Entry.h \
    Unit.h \
    UnitRegister.h \
    mainmenu.h \
    removeunit.h \
    basemenu.h \
    addunit.h \
    editentry.h \
    editunit.h \
    addentry.h \
    editoldentry.h

FORMS    += mainwindow.ui \
    mainmenu.ui \
    removeunit.ui \
    addunit.ui \
    editentry.ui \
    editunit.ui \
    addentry.ui \
    editoldentry.ui

DISTFILES += \
    icon.ico

win32:RC_ICONS += icon.ico
