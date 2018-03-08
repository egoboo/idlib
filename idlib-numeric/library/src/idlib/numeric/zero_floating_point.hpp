#pragma once

#if !defined(IDLIB_PRIVATE) || IDLIB_PRIVATE != 1
#error(do not include directly, include `idlib/numeric.hpp` instead)
#endif

#pragma push_macro("IDLIB_PRIVATE")
#undef IDLIB_PRIVATE
#define IDLIB_PRIVATE (1)

#include "idlib/platform.hpp"
#include "idlib/numeric/zero.hpp"

#undef IDLIB_PRIVATE
#pragma pop_macro("IDLIB_PRIVATE")

namespace idlib {

/// @internal
template <>
struct zero_functor<single, void>
{
    constexpr single operator()() noexcept
    { return 0.0f; }
}; // struct zero_functor

/// @internal
template <>
struct zero_functor<double, void>
{
    constexpr double operator()() noexcept
    { return 0.0; }
}; // struct zero_functor

/// @internal
template <>
struct zero_functor<quadruple, void>
{
    constexpr quadruple operator()() noexcept
    { return 0.0l; }
}; // struct zero_functor 

} // namespace idlib
