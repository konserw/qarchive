#ifndef SERIALIZATION_QSTRING_HPP
#define SERIALIZATION_QSTRING_HPP

#include <boost/serialization/nvp.hpp>
#include <boost/serialization/tracking.hpp>

namespace boost {
namespace serialization {

template<class Archive>
inline void serialize( Archive& ar, QString& s, const unsigned int /*file_version*/ )
{
    ar & make_nvp(NULL, s);
}

} // namespace serialization
} // namespace boost

BOOST_CLASS_TRACKING(QString, boost::serialization::track_never)

#endif
