CONFIG += c++11
#boost serialization dependancy
#only static lib has all needed symbols - not sure if it's boost's bug
unix: LIBS += /usr/lib/libboost_serialization.a # -L/usr/lib/ -lboost_serialization
win32 {
    CONFIG += windows release
    INCLUDEPATH += "$(BOOST_ROOT)"
    LIBS += "-L$(BOOST_LIBRARYDIR)" #/libboost_serialization-vc120-mt-1_59.lib"
}

HEADERS +=			\
    $$PWD/qarchive.hpp		\
    $$PWD/q_xml_iarchive.hpp	\
    $$PWD/q_xml_oarchive.hpp	\
    $$PWD/serialization_qstring.hpp \
    $$PWD/q_xml_iarchive.hpp \
    $$PWD/q_xml_oarchive.hpp
