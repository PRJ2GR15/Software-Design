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
    editoldentry.cpp \
    removeentry.cpp \
    waitforpin.cpp

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
    editoldentry.h \
    removeentry.h \
    waitforpin.h

FORMS    += mainwindow.ui \
    mainmenu.ui \
    removeunit.ui \
    addunit.ui \
    editentry.ui \
    editunit.ui \
    addentry.ui \
    editoldentry.ui \
    removeentry.ui \
    waitforpin.ui

DISTFILES += \
    newIcon.ico \
    icon.png \
    icon.ico

win32:RC_ICONS += icon.ico

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/./ -lSerialCom
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/./ -lSerialCom
else:unix: LIBS += -L$$PWD/./ -lSerialCom

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.
