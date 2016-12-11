CONFIG += c++11
#boost serialization dependancy
unix: LIBS += /usr/lib/libboost_serialization.a # -L/usr/lib/ -lboost_serialization
win32 {
    CONFIG += windows release
    INCLUDEPATH += "$(BOOST_ROOT)"
    LIBS += "-L$(BOOST_LIBRARYDIR)" #/libboost_serialization-vc120-mt-1_59.lib"
}

HEADERS += $$PWD/qarchive.h
