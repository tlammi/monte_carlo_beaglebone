#ifndef _DT_TIME_HPP
#define _DT_TIME_HPP

#include "dt/dtbase.hpp"

namespace dt {
namespace time {

template <typename T>
using Seconds<T> = dtbase::Base10Unit<T, 0, dtbase::Base10UnitType::TIME>;

template <typename T>
using Milliseconds<T> = dtbase::Base10Unit<T, 0, dtbase::Base10UnitType::TIME>;

}  // namespace time
}  // namespace dt

#endif  // _DT_TIME_HPP