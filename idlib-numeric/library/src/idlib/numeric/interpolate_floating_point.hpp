///////////////////////////////////////////////////////////////////////////////////////////////////
//
// Idlib: A C++ utility library
// Copyright (C) 2017-2018 Michael Heilmann
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
///////////////////////////////////////////////////////////////////////////////////////////////////

/// @file idlib/numeric/interpolate_floating_point.hpp
/// @brief Functionality to interpolate between floating point values.
/// @author Michael Heilmann

#pragma once

#if !defined(IDLIB_PRIVATE) || IDLIB_PRIVATE != 1
#error(do not include directly, include `idlib/numeric.hpp` instead)
#endif

#pragma push_macro("IDLIB_PRIVATE")
#undef IDLIB_PRIVATE
#define IDLIB_PRIVATE (1)

#include "idlib/numeric/interpolate.hpp"
#include "idlib/numeric/mu_floating_point.hpp"

#undef IDLIB_PRIVATE
#pragma pop_macro("IDLIB_PRIVATE")

namespace idlib {

/// @ingroup math
/// @brief Interpolate functor specialization for floating point types.
template <typename T>
struct lineary_interpolate_functor<T, T, std::enable_if_t<std::is_floating_point<T>::value>>
{
    using value_type = T;
    using parameter_type = T;
    
    /// @brief Interpolate between to floating point values.
    /// @param x, y the values to interpolate between
    /// @param t the parameter. Must be within the bounds of @a 0 (inclusive) and @a 1 (inclusive).
    /// @return the interpolated value
    /// @throw out_of_bounds_error @a t is not within the bounds of @a 0 (inclusive) and @a 1 (inclusive)
    auto operator()(value_type x, value_type y, parameter_type t) const
    {
        return (*this)(x, y, mu<parameter_type>(t));
    }

    /// @brief Interpolate between to floating point values.
    /// @param x, y the values to interpolate between
    /// @param t the parameter
    /// @return the interpolated value
    auto operator()(value_type x, value_type y, const mu<parameter_type>& mu) const
    {
        return x * mu.get_one_minus_mu() + y * mu.get_mu();
    }

}; // struct lineary_interpolate_functor
    
} // namespace idlib
