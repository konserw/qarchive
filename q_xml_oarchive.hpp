#ifndef Q_XML_OARCHIVE_HPP
#define Q_XML_OARCHIVE_HPP

#include <QList>
#include <list>
#include <QString>
#include <string>

#define BOOST_ARCHIVE_SOURCE
#include <boost/archive/detail/register_archive.hpp>
#include <boost/archive/xml_oarchive.hpp>

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
    void save_override(T & t){
        base_t::save_override(t);
    }
    // catch QString
    void save_override(const nvp<QString> & t){
        std::string str = t.value().toStdString();
        base_t::save_override(make_nvp(t.name(), str));
    }
    // catch QList
    template<class T>
    void save_override(const nvp<QList<T> > & t){
        std::list<T> list = t.value().toStdList();
        base_t::save_override(make_nvp(t.name(), list));
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
