#-------------------------------------------------
#
# Project created by QtCreator 2020-08-11T20:55:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BlockGame
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    onebox.cpp \
    boxgroup.cpp \
    gameview.cpp

HEADERS  += mainwindow.h \
    onebox.h \
    boxgroup.h \
    gameview.h

FORMS    += mainwindow.ui

RESOURCES += \
    myimage.qrc
