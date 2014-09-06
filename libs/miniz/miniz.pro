#-------------------------------------------------
#
# Project created by QtCreator 2014-08-31T23:29:00
#
#-------------------------------------------------

QT       -= core gui

TARGET = myminiz
TEMPLATE = lib
CONFIG += staticlib

INCLUDEPATH += $$PWD/../../3party/miniz-r63

SOURCES += \
    libmyminiz.c

HEADERS += \
    libmyminiz.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
