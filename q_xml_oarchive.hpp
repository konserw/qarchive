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

#ifndef Q_XML_OARCHIVE_HPP
#define Q_XML_OARCHIVE_HPP

#include <QList>
#include <list>
#include <QString>
#include <string>

#define BOOST_ARCHIVE_SOURCE
#include <boost/archive/detail/register_archive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/version.hpp>

using namespace boost::archive;
using boost::serialization::make_nvp;
using boost::serialization::nvp;

class q_xml_oarchive :
public xml_oarchive_impl<q_xml_oarchive>
{
    typedef xml_oarchive_impl<q_xml_oarchive>  base_t;
public:
    // pass on most types to normal handling in the base class xml_oarchive
    template<class T>
#if ((BOOST_VERSION / 100) % 1000) > 58
    void save_override(T & t)
#else
    void save_override(T & t, BOOST_PFTO int pfto)
#endif
    {
        base_t::save_override(t);
    }

    // catch QString
#if ((BOOST_VERSION / 100) % 1000) > 58
    void save_override(const nvp<QString> & t)
#else
    void save_override(const nvp<QString> & t, BOOST_PFTO int pfto)
#endif
    {
        std::string str = t.value().toStdString();
#if ((BOOST_VERSION / 100) % 1000) > 58
        base_t::save_override(make_nvp(t.name(), str));
#else
        base_t::save_override(make_nvp(t.name(), str), pfto);
#endif
    }

    // catch QList
    template<class T>
#if ((BOOST_VERSION / 100) % 1000) > 58
    void save_override(const nvp<QList<T> > & t)
#else
    void save_override(const nvp<QList<T> > & t, BOOST_PFTO int pfto)
#endif
    {
        std::list<T> list = t.value().toStdList();
#if ((BOOST_VERSION / 100) % 1000) > 58
        base_t::save_override(make_nvp(t.name(), list));
#else
        base_t::save_override(make_nvp(t.name(), list), pfto);
#endif
    }

    //stuff needed by boost
    q_xml_oarchive(std::ostream & os, unsigned int flags = 0) : base_t(os, flags){}
    ~q_xml_oarchive(){}
    friend class detail::interface_oarchive<q_xml_oarchive>;
    friend class detail::common_oarchive<q_xml_oarchive>;
    friend class basic_xml_oarchive<q_xml_oarchive>;
    friend class save_access;
};

// required by export
BOOST_SERIALIZATION_REGISTER_ARCHIVE(q_xml_oarchive)

#endif // Q_XML_OARCHIVE_HPP
