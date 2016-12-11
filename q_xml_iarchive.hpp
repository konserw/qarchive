#ifndef Q_XML_IARCHIVE_HPP
#define Q_XML_IARCHIVE_HPP
#include <QList>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/impl/basic_xml_iarchive.ipp>
#include <boost/archive/impl/xml_iarchive_impl.ipp>
using namespace boost::archive;

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
    void load_override(const boost::serialization::nvp<QString> & t){
        this->This()->load_start(t.name());
        std::string str;
        this->detail_common_iarchive::load_override(str);
        t.value() = QString::fromStdString(str);
        this->This()->load_end(t.name());
    }
    // catch QList
    template<class T>
    void load_override(const boost::serialization::nvp<QList<T> > & t){
        this->This()->load_start(t.name());
        std::list<T> list;
        this->detail_common_iarchive::load_override(list);
        t.value() = QList<T>::fromStdList(list);
        this->This()->load_end(t.name());
    }
    /*
    template<class T>
    void load_override(const boost::serialization::nvp<QList<T*> > & t){
        this->This()->load_start(t.name());
        std::list<T*> list;
        this->detail_common_iarchive::load_override(list);
        t.value() = QList<T*>::fromStdList(list);
        this->This()->load_end(t.name());
    }
*/
    //stuff needed by boost
    q_xml_iarchive(std::istream & is, unsigned int flags = 0) : base_t(is, flags){}
    ~q_xml_iarchive(){}
    friend class boost::archive::detail::interface_iarchive<q_xml_iarchive>;
    friend class detail::common_iarchive<q_xml_iarchive>;
    friend class basic_xml_iarchive<q_xml_iarchive>;
    friend class save_access;
};

// required by export
BOOST_SERIALIZATION_REGISTER_ARCHIVE(q_xml_iarchive)

#endif // Q_XML_IARCHIVE_HPP
