#-------------------------------------------------
#
# Project created by QtCreator 2014-08-24T00:42:47
#
#-------------------------------------------------

QT       -= core gui

TARGET = mysqlite3
TEMPLATE = lib
CONFIG += staticlib

INCLUDEPATH += $$PWD/../../3party/sqlite-3.8.6

SOURCES += \
    libmysqlite3.c

HEADERS += \
    libmysqlite3.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
