#define BOOST_ARCHIVE_SOURCE
#include <boost/serialization/config.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/detail/archive_serializer_map.hpp>

#include "q_xml_iarchive.hpp"
#include "q_xml_oarchive.hpp"

// explicitly instantiate for this type of xml stream
#include <boost/archive/impl/archive_serializer_map.ipp>
#include <boost/archive/impl/basic_xml_oarchive.ipp>
#include <boost/archive/impl/xml_oarchive_impl.ipp>
#include <boost/archive/impl/basic_xml_iarchive.ipp>
#include <boost/archive/impl/xml_iarchive_impl.ipp>

namespace boost {
namespace archive {

template class detail::archive_serializer_map<q_xml_oarchive>;
template class basic_xml_oarchive<q_xml_oarchive> ;
template class xml_oarchive_impl<q_xml_oarchive>;

template class detail::archive_serializer_map<q_xml_iarchive>;
template class basic_xml_iarchive<q_xml_iarchive> ;
template class xml_iarchive_impl<q_xml_iarchive>;
} // namespace archive
} // namespace boost
