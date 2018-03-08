#define IDLIB_PRIVATE 1
#include "idlib/numeric/interval_floating_point.hpp"
#undef IDLIB_PRIVATE

template struct idlib::interval<single>;
template struct idlib::interval<double>;
template struct idlib::interval<quadruple>;
