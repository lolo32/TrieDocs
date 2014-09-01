#-------------------------------------------------
#
# Project created by QtCreator 2014-08-31T23:29:00
#
#-------------------------------------------------

QT       -= core gui

TARGET = miniz
TEMPLATE = lib
CONFIG += staticlib

INCLUDEPATH += $$PWD/../../3party/miniz-r63

SOURCES += \
    libminiz.c

HEADERS += \
    libminiz.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
