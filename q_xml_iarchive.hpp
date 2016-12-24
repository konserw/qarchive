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

#ifndef Q_XML_IARCHIVE_HPP
#define Q_XML_IARCHIVE_HPP

#include <QList>
#include <list>
#include <QString>
#include <string>

#define BOOST_ARCHIVE_SOURCE
#include <boost/archive/detail/register_archive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/version.hpp>

using namespace boost::archive;
using boost::serialization::nvp;

class q_xml_iarchive :
public xml_iarchive_impl<q_xml_iarchive>
{
    typedef xml_iarchive_impl<q_xml_iarchive>  base_t;
public:
    // pass on most types to normal handling in the base class xml_oarchive
    template<class T>
#if ((BOOST_VERSION / 100) % 1000) > 58
    void load_override(T & t){
        base_t::load_override(t);
#else
    void load_override(T & t, BOOST_PFTO int pfto){
        base_t::save_override(t, pfto);
#endif
    }

    // catch QString
#if ((BOOST_VERSION / 100) % 1000) > 58
    void load_override(const nvp<QString> & t)
#else
    void load_override(const nvp<QString> & t, BOOST_PFTO int pfto)
#endif
    {
        this->This()->load_start(t.name());
        std::string str;
#if ((BOOST_VERSION / 100) % 1000) > 58
        this->detail_common_iarchive::load_override(str);
#else
        this->detail_common_iarchive::load_override(str, pfto);
#endif
        t.value() = QString::fromStdString(str);
        this->This()->load_end(t.name());
    }

    // catch QList
    template<class T>
#if ((BOOST_VERSION / 100) % 1000) > 58
    void load_override(const nvp<QList<T> > & t)
#else
    void load_override(const nvp<QList<T> > & t, BOOST_PFTO int pfto)
#endif
    {
        this->This()->load_start(t.name());
        std::list<T> list;
#if ((BOOST_VERSION / 100) % 1000) > 58
        this->detail_common_iarchive::load_override(list);
#else
        this->detail_common_iarchive::load_override(list, pfto);
#endif
        t.value() = QList<T>::fromStdList(list);
        this->This()->load_end(t.name());
    }

    //stuff needed by boost
    q_xml_iarchive(std::istream & is, unsigned int flags = 0) : base_t(is, flags){}
    ~q_xml_iarchive(){}
    friend class detail::interface_iarchive<q_xml_iarchive>;
    friend class detail::common_iarchive<q_xml_iarchive>;
    friend class basic_xml_iarchive<q_xml_iarchive>;
    friend class save_access;
};

// required by export
BOOST_SERIALIZATION_REGISTER_ARCHIVE(q_xml_iarchive)

#endif // Q_XML_IARCHIVE_HPP
