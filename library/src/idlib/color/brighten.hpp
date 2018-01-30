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
/// @brief Functionality to brighten colors.
/// @author Michael Heilmann

#pragma once

namespace idlib {

/// @brief A functor to brighten a color value.
/// @detail
/// Defines an @code{C operator()(const C& c, F f) const} which brightens the color @a c by the factor @a t.
/// If a brighten functor for some @a C is defined, it shall seek to support @a float and @a double for @a T.
/// @tparam C the color type
/// @tparam E for SFINAE
/// @remark
/// A brighten functor shall not modify the opacity of a color value.
/// @remark
/// The normal approach to brighten a color value can be defined in terms of a brightening a single component value @a c.
/// Given a component value $c$ in the range of $c_min$ (inclusive) and $c_max$ (inclusive) where $c_min \leq c_max$,
/// the brightened component value is usually computed by
/// $clamp(c * (1 + f),c_min, c_max)$.
/// Note that this function can be used to actually darken a color if $f$ is negative,
/// however, using idlib::darken_functor is then preferred.
template <typename C, typename E = void>
struct brighten_functor;

template <typename C>
decltype(auto) brighten(const C& c, float t)
{
    return brighten_functor<C>()(c, t);
}

template <typename C>
decltype(auto) brighten(const C& c, double t)
{
    return brighten_functor<C>()(c, t);
}

} // namespace idlib
