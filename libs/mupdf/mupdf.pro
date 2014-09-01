#-------------------------------------------------
#
# Project created by QtCreator 2014-08-23T23:58:54
#
#-------------------------------------------------

QT       -= core gui

TARGET = mupdf
TEMPLATE = lib
CONFIG += staticlib

INCLUDEPATH += $$PWD/../../3party/mupdf-git/include

SOURCES +=

HEADERS +=
unix {
    target.path = /usr/lib
    INSTALLS += target
}
