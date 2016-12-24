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
    void load_override(T & t){
        base_t::load_override(t);
    }

    // catch QString
#if ((BOOST_VERSION / 100) % 1000) > 58
    void load_override(const nvp<QString> & t)
#else
    void load_override(const nvp<QString> & t, BOOST_PFTO int)
#endif
    {
        this->This()->load_start(t.name());
        std::string str;
        this->detail_common_iarchive::load_override(str);
        t.value() = QString::fromStdString(str);
        this->This()->load_end(t.name());
    }

    // catch QList
    template<class T>
#if ((BOOST_VERSION / 100) % 1000) > 58
    void load_override(const nvp<QList<T> > & t)
#else
    void load_override(const nvp<QList<T> > & t, BOOST_PFTO int)
#endif
    {
        this->This()->load_start(t.name());
        std::list<T> list;
        this->detail_common_iarchive::load_override(list);
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
