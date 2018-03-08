#pragma once

#if !defined(IDLIB_PRIVATE) || IDLIB_PRIVATE != 1
#error(do not include directly, include `idlib/numeric.hpp` instead)
#endif

#pragma push_macro("IDLIB_PRIVATE")
#undef IDLIB_PRIVATE
#define IDLIB_PRIVATE (1)

#include "idlib/numeric/is_positive.hpp"
#include "idlib/numeric/zero_integer.hpp"

#undef IDLIB_PRIVATE
#pragma pop_macro("IDLIB_PRIVATE")

namespace idlib {

/// @internal
template <typename T>
struct is_positive_functor<T, std::enable_if_t<std::is_integral<T>::value && !std::is_same<T, bool>::value>>
{
    bool operator()(T x) noexcept
    { return x > zero<T>(); }
}; // struct is_positive_functor

} // namespace idlib
