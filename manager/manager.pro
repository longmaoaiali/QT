#-------------------------------------------------
#
# Project created by QtCreator 2020-08-24T17:44:41
#
#-------------------------------------------------

QT       += core gui sql xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = manager
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    connectionh.cpp

HEADERS  += widget.h \
    connectionh.h

FORMS    += widget.ui
