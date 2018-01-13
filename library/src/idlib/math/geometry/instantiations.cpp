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

/// @file egolib/math/geometry/instantiations.cpp
/// @brief Spheres.
/// @author Michael Heilmann

#define IDLIB_PRIVATE 1
#include "idlib/math/geometry/include.hpp"
#undef IDLIB_PRIVATE

#define INSTANTIATE(A) \
	template struct id::A<id::point<id::vector<single, 2>>>; \
	template struct id::A<id::point<id::vector<single, 3>>>; \
	template struct id::A<id::point<id::vector<single, 4>>>; \
	template struct id::A<id::point<id::vector<double, 2>>>; \
	template struct id::A<id::point<id::vector<double, 3>>>; \
	template struct id::A<id::point<id::vector<double, 4>>>; \
	template struct id::A<id::point<id::vector<quadruple, 2>>>; \
	template struct id::A<id::point<id::vector<quadruple, 3>>>; \
	template struct id::A<id::point<id::vector<quadruple, 4>>>;
	
INSTANTIATE(axis_aligned_box)
INSTANTIATE(axis_aligned_cube)
INSTANTIATE(line)
INSTANTIATE(ray)
INSTANTIATE(sphere)

#undef INSTANTIATE

#define INSTANTIATE(A) \
	template struct id::A<id::point<id::vector<single, 3>>>; \
	template struct id::A<id::point<id::vector<double, 3>>>; \
	template struct id::A<id::point<id::vector<quadruple, 3>>>;

INSTANTIATE(plane)

#undef INSTANTIATION
