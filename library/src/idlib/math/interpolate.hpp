// Copyright Michael Heilmann 2016, 2017, 2018.
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
/// @brief Functionality to interpolate between values.
/// @author Michael Heilmann

#pragma once

#include "idlib/math/mu.hpp"
#include "idlib/math/one_zero.hpp"

namespace id {

/// @ingroup math
/// @brief Functor which lineary interpolates between values.
/// @tparam V the type of the values to interpolate between
/// @tparam T the type of the parameter
/// @tparam M the interpolation method
/// @tparam E for SFINAE
/// @remark
/// Provides the member typedefs @a value_type and @a parameter_type.
/// @a value_type is the type of the values to lineary interpolate between and @a parameter_type is the type of the parameter.
/// @remark
/// Provides a constant operator() which takes the values @a x and @a y both of type @a value_type to interpolate between as its first two arguments.
/// Its third argument is the parameter @a t of type @a parameter_type.
/// The parameter is supposed to be within the bounds of id::zero<T>() (inclusive) and id::one<T>() (inclusive).
/// If the third argument is not within these bounds, implementations of this functor are supposed to raise an id::domain_error.
/// @remarks
/// Provides a constant operator() which takes the values @a x and @a y both of type @a value_type to interpolate between as its first two arguments.
/// Its third argument is the parameter @a mu of type id::mu<T>.
template <typename V, typename T, typename E = void>
struct lineary_interpolate_functor;

template <typename V, typename T>
auto lineary_interpolate(const V& x, const V& y, const T& t)
{ return lineary_interpolate_functor<V, T>()(x, y, mu<T>(t)); }

template <typename V, typename T>
auto lineary_interpolate(const V& x, const V& y, const mu<T>& t)
{ return lineary_interpolate_functor<V, T>()(x, y, t); }

} // namespace id
