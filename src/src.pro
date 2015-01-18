#-------------------------------------------------
#
# Project created by QtCreator 2014-08-04T18:37:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TrieDocs
TEMPLATE = app

INCLUDEPATH += \
            $$PWD/../libs/mupdf   $$PWD/../3party/mupdf-git/include \
            $$PWD/../libs/miniz   $$PWD/../3party/miniz-r63 \
            $$PWD/../libs/sqlite3 $$PWD/../3party/sqlite-3.8.6 \

SOURCES += main.cpp\
        mainwindow.cpp \
        bdd.cpp \
        dlgclient.cpp \
        reseau.cpp

HEADERS  += mainwindow.h \
        bdd.h \
        dlgclient.h \
        reseau.h

FORMS    += \
        mainwindow.ui \
        dlgclient.ui

TRANSLATIONS += \
        i18n/en.ts

QMAKE_RESOURCE_FLAGS += -threshold 0 -compress 9
RESOURCES += \
        resources.qrc

# Dépendance avec mupdf
# Dépendance avec miniz
# Dépendance avec sqlite3

win32 {
    CONFIG(release, debug|release) {
        LIBS += \
             -L$$OUT_PWD/../libs/mupdf/release/ -lmymupdf \
             -L$$OUT_PWD/../libs/miniz/release/ -lmyminiz \
             -L$$OUT_PWD/../libs/sqlite3/release/ -lmysqlite3
        g++ {
            PRE_TARGETDEPS += \
                            $$OUT_PWD/../libs/mupdf/release/libmymupdf.a \
                            $$OUT_PWD/../libs/miniz/release/libmyminiz.a \
                            $$OUT_PWD/../libs/sqlite3/release/libmysqlite3.a
        } else {
            PRE_TARGETDEPS += \
                            $$OUT_PWD/../libs/mupdf/release/mymupdf.lib \
                            $$OUT_PWD/../libs/miniz/release/myminiz.lib \
                            $$OUT_PWD/../libs/sqlite3/release/mysqlite3.lib
        }
    } else:CONFIG(debug, debug|release) {
        LIBS += \
             -L$$OUT_PWD/../libs/mupdf/debug/ -lmymupdf \
             -L$$OUT_PWD/../libs/miniz/debug/ -lmyminiz \
             -L$$OUT_PWD/../libs/sqlite3/debug/ -lmysqlite3
        g++ {
            PRE_TARGETDEPS += \
                            $$OUT_PWD/../libs/mupdf/debug/libmymupdf.a \
                            $$OUT_PWD/../libs/miniz/debug/libmyminiz.a \
                            $$OUT_PWD/../libs/sqlite3/debug/libmysqlite3.a
        } else {
            PRE_TARGETDEPS += \
                            $$OUT_PWD/../libs/mupdf/debug/mymupdf.lib \
                            $$OUT_PWD/../libs/miniz/debug/myminiz.lib \
                            $$OUT_PWD/../libs/sqlite3/debug/mysqlite3.lib
        }
    }
} else:unix {
#        -L$$OUT_PWD/../libs/mupdf/ -lmymupdf \
    LIBS += \
        -L$$OUT_PWD/../libs/miniz/ -lmyminiz \
        -L$$OUT_PWD/../libs/sqlite3/ -lmysqlite3

#                    $$OUT_PWD/../libs/mupdf/libmymupdf.a \
    PRE_TARGETDEPS += \
                    $$OUT_PWD/../libs/miniz/libmyminiz.a \
                    $$OUT_PWD/../libs/sqlite3/libmysqlite3.a
}

#    $$PWD/../libs/mupdf \
DEPENDPATH += \
    $$PWD/../libs/miniz \
    $$PWD/../libs/sqlite3

macx {
    QMAKE_INFO_PLIST = Info.plist
#   RC_FILE = TrieDocicon.icns
}
win32 {
    RC_FILE = win.rc
}

OTHER_FILES += \
