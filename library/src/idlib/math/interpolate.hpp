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
