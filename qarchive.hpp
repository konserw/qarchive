/**
    qarchive - XML Archive class for boost serialization of Qt classes
    Copyright (C) 2016  Kamil 'konserw' Strzempowicz, konserw@gmail.com

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
**/

#ifndef QARCHIVE_HPP
#define QARCHIVE_HPP

#include "q_xml_iarchive.hpp"
#include "q_xml_oarchive.hpp"

#include <boost/serialization/nvp.hpp>
#include <boost/archive/impl/archive_serializer_map.ipp>

namespace boost {
namespace serialization {

template<class Archive>
inline void serialize( Archive& ar, QString& s, const unsigned int /*file_version*/ )
{
    ar & make_nvp(NULL, s);
}

template<class Archive, class T>
inline void serialize( Archive& ar, QList<T>& list, const unsigned int /*file_version*/ )
{
    ar & make_nvp(NULL, list);
}

template<class Archive>
inline void serialize( Archive& ar, QStringList& stringList, const unsigned int /*file_version*/ )
{
    QList<QString> list = stringList;
    ar & make_nvp(NULL, list);
    stringList = list;
}

} // namespace serialization
} // namespace boost

#endif
