#ifndef Q_XML_IARCHIVE_HPP
#define Q_XML_IARCHIVE_HPP

#define BOOST_ARCHIVE_SOURCE
#include <boost/archive/basic_xml_iarchive.hpp>
#include <boost/archive/impl/basic_xml_iarchive.ipp>
#include <boost/archive/impl/xml_iarchive_impl.ipp>

#include <boost/archive/detail/register_archive.hpp>

using namespace boost::archive;

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

#endif // Q_XML_IARCHIVE_HPP
