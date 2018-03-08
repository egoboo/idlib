#define IDLIB_PRIVATE 1
#include "idlib/numeric/interval_integer.hpp"
#undef IDLIB_PRIVATE

template struct idlib::interval<short>;
template struct idlib::interval<int>;
template struct idlib::interval<long>;
