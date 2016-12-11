#-------------------------------------------------
#
# Project created by QtCreator 2016-12-11T17:01:05
#
#-------------------------------------------------

QT       += testlib
QT       -= gui

TARGET = tst_serializeqstring
CONFIG   += console testcase
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH += $$PWD/../include

unix: LIBS += \
    $$OUT_PWD/../libqarchive/libqarchive.a \
    /usr/lib/libboost_serialization.a

CONFIG += c++11

SOURCES += tst_serializeqstring.cpp \
    main.cpp

DEFINES += SRCDIR=\\\"$$PWD/\\\"
