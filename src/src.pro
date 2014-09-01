#-------------------------------------------------
#
# Project created by QtCreator 2014-08-04T18:37:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LibreDoc
TEMPLATE = app

INCLUDEPATH += $$PWD/../../3party/sqlite-3.8.6 \
            $$PWD/../../3party/mupdf-git/include \
            $$PWD/../../3party/miniz-r63

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

SUBDIRS += \
    libs/mupdf.pro

RESOURCES += \
    resources.qrc

# Dépendance avec sqlite3
# Dépendance avec mupdf
# Dépendance avec miniz

win32 {
    CONFIG(release, debug|release) {
        LIBS += \
             -L$$OUT_PWD/../libs/mupdf/release/ -lmupdf \
             -L$$OUT_PWD/../libs/miniz/release/ -lminiz \
             -L$$OUT_PWD/../libs/sqlite3/release/ -lsqlite3
    } else:CONFIG(debug, debug|release) {
        LIBS += \
             -L$$OUT_PWD/../libs/mupdf/debug/ -lmupdf \
             -L$$OUT_PWD/../libs/miniz/debug/ -lminiz \
             -L$$OUT_PWD/../libs/sqlite3/debug/ -lsqlite3
    }
} else:unix {
    LIBS += \
        -L$$OUT_PWD/../libs/mupdf/ -lmupdf \
        -L$$OUT_PWD/../libs/miniz/ -lminiz \
        -L$$OUT_PWD/../libs/sqlite3/ -lsqlite3
}

INCLUDEPATH += \
    $$PWD/../libs/mupdf \
    $$PWD/../libs/miniz \
    $$PWD/../libs/sqlite3

DEPENDPATH += \
    $$PWD/../libs/mupdf \
    $$PWD/../libs/miniz \
    $$PWD/../libs/sqlite3

win32 {
    g++ {
        CONFIG(release, debug|release) {
            PRE_TARGETDEPS += \
                            $$OUT_PWD/../libs/mupdf/release/libmupdf.a \
                            $$OUT_PWD/../libs/miniz/release/libsminiz.a \
                            $$OUT_PWD/../libs/sqlite3/release/libsqlite3.a
        } else:CONFIG(debug, debug|release) {
            PRE_TARGETDEPS += \
                            $$OUT_PWD/../libs/mupdf/debug/libmupdf.a \
                            $$OUT_PWD/../libs/miniz/debug/libsminiz.a \
                            $$OUT_PWD/../libs/sqlite3/debug/libsqlite3.a
        }
    } else {
        CONFIG(release, debug|release) {
            PRE_TARGETDEPS += \
                            $$OUT_PWD/../libs/mupdf/release/mupdf.lib \
                            $$OUT_PWD/../libs/miniz/release/miniz.lib \
                            $$OUT_PWD/../libs/sqlite3/release/sqlite3.lib
        } else:CONFIG(debug, debug|release) {
            PRE_TARGETDEPS += \
                            $$OUT_PWD/../libs/mupdf/debug/mupdf.lib \
                            $$OUT_PWD/../libs/miniz/debug/miniz.lib \
                            $$OUT_PWD/../libs/sqlite3/debug/sqlite3.lib
        }
    }
} else:unix {
    PRE_TARGETDEPS += \
                    $$OUT_PWD/../libs/mupdf/libmupdf.a \
                    $$OUT_PWD/../libs/miniz/libminiz.a \
                    $$OUT_PWD/../libs/sqlite3/libsqlite3.a
}


OTHER_FILES +=
