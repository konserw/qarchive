// \file qstring_serialization.h
//  Enables serialization of Qt QString
//
//  Copyright (c) 2010 Florian Muecke. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// downloaded from http://flo.mueckeimnetz.de/2010/01/boostserialization-und-qstring/
// with changes by Kamil Strzempowicz

#ifndef QSTRING_SERIALIZATION_H
#define QSTRING_SERIALIZATION_H
#include <QDebug>
#include "qarchive.hpp"
/*
#include <QString>
#include <string>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/array.hpp>
*/
namespace boost {
namespace serialization {

using boost::serialization::make_nvp;
#ifdef xcsfcs
template<class Archive>
inline void save( Archive& ar, const QString& s, const unsigned int /*version*/ )
{
    std::string stdStr = s.toStdString();
    ar << make_nvp("value", stdStr);
}

template<class Archive>
inline void load( Archive& ar, QString& s, const unsigned int /*version*/ )
{
    std::string stdStr;
    ar >> make_nvp("value", stdStr);
    s = QString::fromStdString(stdStr);
    /*
    size_t size;
    ar >> size;
    char * buff = new char[size];
    ar >> boost::serialization::make_array(buff, size);
    s = QString::fromLocal8Bit(buff);
    delete[] buff;
    */
}
#endif

template<class Archive>
inline void serialize( Archive& ar, QString& s, const unsigned int file_version )
{
    Q_UNUSED(file_version)
    qDebug() << "serialize:" << s;
    ar & make_nvp(NULL, s);
    //boost::serialization::split_free(ar, s, file_version);
}

} // namespace serialization
} // namespace boost


//BOOST_CLASS_TRACKING(QString, track_never)

#endif // QSTRING_SERIALIZATION_H
