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

/// @file idlib/math_geometry/enclose_axis_aligned_box_in_sphere.hpp
/// @brief Enclose axis aligned boxes in spheres.
/// @author Michael Heilmann

#pragma once

#include "idlib/math_geometry/axis_aligned_box.hpp"
#include "idlib/math_geometry/sphere.hpp"

namespace idlib {

/// @brief Specialization of idlib::enclose_functor.
/// Encloses an axis aligned box in a sphere.
/// @detail A sphere \f$b\f$ enclosing an axis aligned box \f$a\f$ has the center \f$c\f$
/// of the axis aligned box. Its radius is given by \f$r:=|x - c|\f$ where \x\f$ is the
/// minimum point of the axis aligned box and \f$|.|\f$ is the Euclidean length of a vector.
/// @tparam P the point type of the geometries
template <typename P>
struct enclose_functor<sphere<P>, axis_aligned_box<P>>
{
    auto operator()(const axis_aligned_box<P>& source) const
    {
        const auto center = source.get_center();
        const auto radius = euclidean_norm(source.get_min() - center);
        return sphere<P>(center, radius);
    }
}; // struct enclose_functor

} // namespace idlib
