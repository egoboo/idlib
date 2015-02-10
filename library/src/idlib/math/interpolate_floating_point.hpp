// Copyright Michael Heilmann 2016, 2017.
//
// This file is part of Idlib.
//
// Idlib is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Idlib is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Idlib. If not, see <http://www.gnu.org/licenses/>.

/// @file id/math/interpolate.hpp
/// @brief Functionality to interpolate between floating point values.
/// @author Michael Heilmann

#pragma once

#include "idlib/math/interpolate.hpp"
#include "idlib/math/mu.hpp"
#include "idlib/math/one_zero.hpp"

namespace id {

/// @brief Interpolate functor specialization for floating point types.
template <typename T>
struct interpolate_functor<T, interpolation_method::LINEAR, std::enable_if_t<std::is_floating_point<T>::value>>
{
    /// @brief Interpolate between to floating point values.
    /// @param x, y the values to interpolate between
    /// @param t the parameter. Must be within the bounds of @a 0 (inclusive) and @a 1 (inclusive).
    /// @return the interpolated value
    /// @throw out_of_bounds_error @a t is not within the bounds of @a 0 (inclusive) and @a 1 (inclusive)
    T operator()(T x, T y, T t) const
    {
        return (*this)(x, y, mu<T>(t));
    }

    /// @brief Interpolate between to floating point values.
    /// @param x, y the values to interpolate between
    /// @param t the parameter
    /// @return the interpolated value
    T operator()(T x, T y, const mu<T>& mu) const
    {
        return x * mu.getOneMinusValue() + y * mu.getValue();
    }

}; // struct interpolate_functor

} // namespace id
