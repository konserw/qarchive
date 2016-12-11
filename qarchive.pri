CONFIG += c++11
#boost serialization dependancy
#only static lib has all needed symbols - not sure if it's boost's bug
unix: LIBS += /usr/lib/libboost_serialization.a
win32 {
    CONFIG += windows release
    INCLUDEPATH += "$(BOOST_ROOT)"
    LIBS += "-L$(BOOST_LIBRARYDIR)"
}

HEADERS +=			\
    $$PWD/qarchive.hpp		\
    $$PWD/q_xml_iarchive.hpp	\
    $$PWD/q_xml_oarchive.hpp	\
    $$PWD/serialization_qstring.hpp
