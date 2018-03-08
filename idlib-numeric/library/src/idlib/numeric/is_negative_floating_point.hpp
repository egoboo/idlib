#pragma once

#if !defined(IDLIB_PRIVATE) || IDLIB_PRIVATE != 1
#error(do not include directly, include `idlib/numeric.hpp` instead)
#endif

#pragma push_macro("IDLIB_PRIVATE")
#undef IDLIB_PRIVATE
#define IDLIB_PRIVATE (1)

#include "idlib/numeric/is_negative.hpp"
#include "idlib/numeric/zero_floating_point.hpp"

#pragma pop_macro("IDLIB_PRIVATE")

namespace idlib {
    
/// @internal
template <typename T>
struct is_negative_functor<T, std::enable_if_t<std::is_floating_point<T>::value>>
{
    bool operator()(T x) noexcept
    { return x < zero<T>(); }
}; // struct is_negative_functor

} // namespace idlib
