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

/// @file idlib/math_geometry/enclose_sphere_in_axis_aligned_box.hpp
/// @brief Enclose spheres in axis aligned boxes.
/// @author Michael Heilmann

#pragma once

#include "idlib/math_geometry/axis_aligned_box.hpp"
#include "idlib/math_geometry/sphere.hpp"

namespace idlib {

/// @brief Specialization of idlib::enclose_functor.
/// Encloses a sphere in an axis aligned box.
/// @detail The axis aligned box \f$b\f$ enclosing a sphere \f$a\f$ with
/// center \f$c\f$ and radius \f$r\f$ has the minimal point \f$min = c -
/// \vec{1} \cdot r\f$ and the maximal point \f$c + \vec{1} \cdot  r\f$.
/// @tparam P the point type of the geometry types
template <typename P>
struct enclose_functor<axis_aligned_box<P>, sphere<P>>
{
    auto operator()(const sphere<P>& source) const
    {
        const auto center = source.get_center();
        const auto radius = source.get_radius();
        const auto extend = one<typename P::vector_type>() * radius;
        return axis_aligned_box<P>(center - extend, center + extend);
    }
}; // struct enclose_functor

} // namespace idlib
