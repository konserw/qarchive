CONFIG += c++11
#boost serialization dependancy
#only static lib has all needed symbols - not sure if it's boost's bug
#please add for example LIBS += /usr/lib/libboost_serialization.a to your project

HEADERS +=			\
    $$PWD/qarchive.hpp		\
    $$PWD/q_xml_iarchive.hpp	\
    $$PWD/q_xml_oarchive.hpp

SOURCES += \
    $$PWD/qarchive.cpp
