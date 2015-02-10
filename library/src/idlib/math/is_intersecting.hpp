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

/// @file idlib/math/is_intersecting.hpp
/// @brief "is_intersecting" functor and function
/// @author Michael Heilmann

#pragma once

namespace id {

/// @ingroup math
/// @brief A functor determinating wether two geometries intersect each other.
/// @details
/// Consider geometries as sets of points. A geometry \f$a\f$ and a geometry \f$b\f$ intersect if \f$a \cap b \neq \emptyset\f$.
/// @tparam A, B the types of the geometries
/// @remark The intersects relation is commutative.
template <typename ... T>
struct is_intersecting_functor;

template <typename A, typename B>
auto is_intersecting(const A& a, const B& b) -> decltype(is_intersecting_functor<A, B>()(a, b))
{
	return is_intersecting_functor<A, B>()(a, b);
}

} // namespace id
