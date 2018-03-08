#pragma once

#if !defined(IDLIB_PRIVATE) || IDLIB_PRIVATE != 1
#error(do not include directly, include `idlib/numeric.hpp` instead)
#endif

#pragma push_macro("IDLIB_PRIVATE")
#undef IDLIB_PRIVATE
#define IDLIB_PRIVATE (1)

#include "idlib/numeric/zero.hpp"

#undef IDLIB_PRIVATE
#pragma pop_macro("IDLIB_PRIVATE")

#include <type_traits>

namespace idlib {

/// @internal
template <typename T>
struct zero_functor<T, std::enable_if_t<std::is_integral<T>::value && !std::is_same<T, bool>::value>>
{
    constexpr T operator()() noexcept
    { return 0; }
}; // struct zero_functor
    
} // namespace idlib
