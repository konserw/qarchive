
#ifndef QARCHIVE_H
#define QARCHIVE_H

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <QDebug>
#include <QString>
#include <string>

#define BOOST_ARCHIVE_SOURCE
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_archive_exception.hpp>
#include <boost/archive/basic_xml_archive.hpp>
#include <boost/archive/basic_xml_oarchive.hpp>
#include <boost/archive/basic_xml_iarchive.hpp>

#include <boost/archive/impl/xml_iarchive_impl.ipp>
#include <boost/archive/impl/xml_oarchive_impl.ipp>
#include <boost/archive/impl/basic_xml_grammar.hpp>
#include <boost/archive/impl/basic_xml_oarchive.ipp>
#include <boost/archive/impl/basic_xml_iarchive.ipp>
#include <boost/archive/impl/archive_serializer_map.ipp>

#include <boost/serialization/serialization.hpp>
#include <boost/serialization/string.hpp>
#include <boost/archive/detail/register_archive.hpp>
#include <boost/archive/detail/oserializer.hpp>


// explicitly instantiate for this type of binary stream
#include <boost/archive/impl/basic_binary_oprimitive.ipp>
#include <boost/archive/impl/basic_binary_iprimitive.ipp>

namespace boost {
    namespace archive {
        namespace detail {
            template<class Archive> class interface_oarchive;
        } // namespace detail
    } // namespace archive
} // boost

//namespace boost {
//namespace archive {

using namespace boost::archive;

class q_xml_oarchive :
public xml_oarchive_impl<q_xml_oarchive>
{
    typedef xml_oarchive_impl<q_xml_oarchive>  base_t;
public:
    template<class T>
    void save_override(T & t){
        base_t::save_override(t);
    }
    void save_override(const boost::serialization::nvp<QString> & t){
        std::string str = t.value().toStdString();
        base_t::save_override(boost::serialization::make_nvp(t.name(), str)); //str; // s.toStdString();
    }

    // pass on most types to normal handling in the base class xml_oarchive
    /*
    template<class T>
    void save(const T & t){
        xml_oarchive_impl<q_xml_oarchive>::save(t);
    }
    void save(const QString &s){
        os << s.toStdString();
    }
*/
    q_xml_oarchive(std::ostream & os, unsigned int flags = 0) : base_t(os, flags){}
  //  q_xml_oarchive(std::streambuf & bsb, unsigned int flags = 0) : base_t(bsb, flags){}
    //~q_xml_oarchive(){}

    friend class boost::archive::detail::interface_oarchive<q_xml_oarchive>;
    friend class detail::common_oarchive<q_xml_oarchive>;
    friend class basic_xml_oarchive<q_xml_oarchive>;
    friend class save_access;
};

// required by export
BOOST_SERIALIZATION_REGISTER_ARCHIVE(q_xml_oarchive)

class q_xml_iarchive :
public xml_iarchive_impl<q_xml_iarchive>
{
    typedef xml_iarchive_impl<q_xml_iarchive>  base_t;
public:
    template<class T>
    void load_override(T & t){
        qDebug() << "Loading type" << typeid(T).name();
        base_t::load_override(t);
    }
    void load_override(const boost::serialization::nvp<QString> & t){
        qDebug() << "load override for:" << t.name() << "element";
        this->This()->load_start(t.name());
        std::string str;

        this->detail_common_iarchive::load_override(str);
        qDebug() << "str:" << QString::fromStdString(str);
        this->This()->load_end(t.name());

        t.value() = QString::fromStdString(str);
        qDebug() << t.value(); //.toStdString();
        //base_t::load_override(boost::serialization::make_nvp(t.name(), str)); //str; // s.toStdString();
    }
    // pass on most types to normal handling in the base class xml_oarchive
  /*
    template<class T>
    void load(T & t){
        xml_iarchive_impl<q_xml_iarchive>::load(t);
    }
    void load(QString &s){
        std::string buff;
        is >> buff;
        s = QString::fromStdString(buff);
    }
*/
    q_xml_iarchive(std::istream & stream, unsigned int flags = 0) : xml_iarchive_impl<q_xml_iarchive>(stream, flags){}
    ~q_xml_iarchive(){}

    friend class detail::common_iarchive<q_xml_iarchive>;
    friend class basic_xml_iarchive<q_xml_iarchive>;
    friend class save_access;
};
//} // namespace archive
//} // namespace boost

// required by export
BOOST_SERIALIZATION_REGISTER_ARCHIVE(q_xml_iarchive)
//BOOST_CLASS_TRACKING(QString, track_never)

#endif
