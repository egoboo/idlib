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

/// @file idlib/math-geometry.hpp
/// @brief Master include file of the Idlib math geometry library.
/// @author Michael Heilmann

#pragma once

#pragma push_macro("IDLIB_PRIVATE")
#undef IDLIB_PRIVATE
#define IDLIB_PRIVATE (1)

#include "idlib/math_geometry/axis_aligned_box.hpp"
#include "idlib/math_geometry/axis_aligned_cube.hpp"
#include "idlib/math_geometry/cone.hpp"
#include "idlib/math_geometry/line.hpp"
#include "idlib/math_geometry/plane.hpp"
#include "idlib/math_geometry/ray.hpp"
#include "idlib/math_geometry/sphere.hpp"

#include "idlib/math_geometry/enclose_axis_aligned_box_in_axis_aligned_cube.hpp"
#include "idlib/math_geometry/enclose_axis_aligned_box_in_sphere.hpp"
#include "idlib/math_geometry/enclose_axis_aligned_cube_in_axis_aligned_box.hpp"
#include "idlib/math_geometry/enclose_sphere_in_axis_aligned_box.hpp"

#include "idlib/math_geometry/is_intersecting_axis_aligned_box_axis_aligned_cube.hpp"

#undef IDLIB_PRIVATE
#pragma pop_macro("IDLIB_PRIVATE")
