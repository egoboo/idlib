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

/// @file idlib/math_geometry/enclose_axis_aligned_box_in_axis_aligned_cube.hpp
/// @brief Enclose an axis aligned cubes in an axis aligned boxes.
/// @author Michael Heilmann

#pragma once

#include "idlib/math_geometry/axis_aligned_box.hpp"
#include "idlib/math_geometry/axis_aligned_cube.hpp"

namespace idlib {

/// @brief Specialization of idlib::enclose_functor.
/// Encloses an axis aligned box in an axis aligned cube.
/// @detail Given an axis aligned box \f$a\f$ with edge lengths \f$l_0, \ldots, l_{n-1}\f$ and
/// a center \f$c\f$, an axis aligned cube \f$b\f$ enclosing the axis aligned box can be
/// computed as follows:
/// - The center \f$c'\f$ of the cube is the center of the box i.e. \f$c' := c\f$.
/// - The edge length of the cube \f$l'\f$ is the maximum edge length of the box i.e. \f$l' := \max_{i=0}^{n-1} l_i\f$
template <typename P>
struct enclose_functor<axis_aligned_cube<P>, axis_aligned_box<P>>
{
    auto operator()(const axis_aligned_box<P>& source) const
    {
        // Get the edge lengths of the box.
        auto edge_lengths = source.get_size();
        // Get the center of the box.
        auto center = source.get_center();
        // Get the maximal edge length of the box.
        auto maximal_edge_length = max_element(edge_lengths);
        // Create the cube.
        return axis_aligned_cube<P>(center, maximal_edge_length);
    }
}; // struct enclose_functor

} // namespace idlib
