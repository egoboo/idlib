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

/// @file idlib/math_geometry/enclose_axis_aligned_cube_in_axis_aligned_box.hpp
/// @brief Enclose a axis aligned cube in an axis aligned cube.
/// @author Michael Heilmann

#pragma once

#include "idlib/math_geometry/axis_aligned_box.hpp"
#include "idlib/math_geometry/axis_aligned_cube.hpp"

namespace idlib {

/// @brief Specialization of idlib::enclose_functor.
/// Encloses an axis aligned cube in an axis aligned box.
/// @detail Let \$a\f$ be an axis aligned cube and \f$min\f$ its minimal point and \f$max\f$ its maximal point.
/// The axis aligned box \f$b\f$ enclosing \f$a\f$ has the same minimal and maximal and maximal point.
/// @tparam P the point type of the geometry types
template <typename P>
struct enclose_functor<axis_aligned_box<P>, axis_aligned_cube<P>>
{
    auto operator()(const axis_aligned_cube<P>& source) const
    { return axis_aligned_box<P>(source.get_min(), source.get_max()); }
}; // struct enclose_functor

} // namespace idlib
