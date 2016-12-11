TARGET = qarchive

TEMPLATE = lib
CONFIG += staticlib
QT = core

INCLUDEPATH += $$PWD/../include
CONFIG += c++11

SOURCES += \
    $$PWD/qarchive.cpp
