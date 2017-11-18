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

/// @file egolib/math/geometry/instantiations.cpp
/// @brief Spheres.
/// @author Michael Heilmann

#define IDLIB_PRIVATE 1
#include "idlib/math/geometry/include.hpp"
#undef IDLIB_PRIVATE

#define INSTANTIATE(A) \
	template struct id::A<id::vector<single, 2>>; \
	template struct id::A<id::vector<single, 3>>; \
	template struct id::A<id::vector<single, 4>>; \
	template struct id::A<id::vector<double, 2>>; \
	template struct id::A<id::vector<double, 3>>; \
	template struct id::A<id::vector<double, 4>>; \
	template struct id::A<id::vector<quadruple, 2>>; \
	template struct id::A<id::vector<quadruple, 3>>; \
	template struct id::A<id::vector<quadruple, 4>>;
	
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
