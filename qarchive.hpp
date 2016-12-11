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

} // namespace serialization
} // namespace boost

#endif
