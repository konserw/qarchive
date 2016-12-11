#ifndef Q_XML_OARCHIVE_HPP
#define Q_XML_OARCHIVE_HPP

#define BOOST_ARCHIVE_SOURCE
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/impl/xml_oarchive_impl.ipp>
#include <boost/archive/impl/basic_xml_oarchive.ipp>

#include <boost/archive/detail/register_archive.hpp>

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

#endif // Q_XML_OARCHIVE_HPP
