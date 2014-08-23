#-------------------------------------------------
#
# Project created by QtCreator 2014-08-04T18:37:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LibreDoc
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

SUBDIRS += \
    libs/mupdf.pro

RESOURCES += \
    resources.qrc

# Dépendance avec mupdf
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../libs/mupdf/release/ -lmupdf
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../libs/mupdf/debug/ -lmupdf
else:unix: LIBS += -L$$OUT_PWD/../libs/mupdf/ -lmupdf

INCLUDEPATH += $$PWD/../libs/mupdf
DEPENDPATH += $$PWD/../libs/mupdf

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../libs/mupdf/release/libmupdf.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../libs/mupdf/debug/libmupdf.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../libs/mupdf/release/mupdf.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../libs/mupdf/debug/mupdf.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../libs/mupdf/libmupdf.a

# Dépendance avec sqlite3
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../libs/sqlite3/release/ -lsqlite3
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../libs/sqlite3/debug/ -lsqlite3
else:unix: LIBS += -L$$OUT_PWD/../libs/sqlite3/ -lsqlite3

INCLUDEPATH += $$PWD/../libs/sqlite3
DEPENDPATH += $$PWD/../libs/sqlite3

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../libs/sqlite3/release/libsqlite3.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../libs/sqlite3/debug/libsqlite3.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../libs/sqlite3/release/sqlite3.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../libs/sqlite3/debug/sqlite3.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../libs/sqlite3/libsqlite3.a
