#ifndef SERIALIZATION_QLIST_HPP
#define SERIALIZATION_QLIST_HPP

#include <boost/serialization/nvp.hpp>
#include <boost/serialization/tracking.hpp>

namespace boost {
namespace serialization {

template<class Archive, class T>
inline void serialize( Archive& ar, QList<T*>& list, const unsigned int /*file_version*/ )
{
    ar & make_nvp(NULL, list);
}

} // namespace serialization
} // namespace boost

//BOOST_CLASS_TRACKING(QList, boost::serialization::track_never)

#endif // SERIALIZATION_QLIST_H
