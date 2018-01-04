// Copyright Michael Heilmann 2016, 2017, 2018.
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

/// @file idlib/math/is_enclosing.hpp
/// @brief "is enclosing" functor and function
/// @author Michael Heilmann

#pragma once

namespace id {
	
/// @ingroup math
/// @brief A functor determinating wether a geometry is enclosed in another geometry.
/// @details
/// Consider geometries as sets of points. A geometry \f$b\f$ is contained in another geometry \f$a\f$ if \f$b \subseteq a\f$.
/// @details
/// Specializations of this functor provide a constant operator() which receives two geometry \f$a\f$ of type \f$A\f$ and
/// \f$b\f$ of type \f$B\f$. It returns an @a bool value.
/// The return value @a true indicates that \f$a\f$ is enclosing \f$b\f$,
/// the return value @a false indicates that \f$a\f$ is not enclosing \f$b\f$.
/// @tparam A the type of the first geometry checked for containing other geometry
/// @tparam B the type of the second geometry which is checked wether it is contained
/// @remark The "is enclosing" relation is <em>not necessarily</em> commutative.
template <typename A, typename B>
struct is_enclosing_functor;

template <typename A, typename B>
auto is_enclosing(const A& a, const B& b) -> decltype(is_enclosing_functor<A, B>()(a, b))
{
	return is_enclosing_functor<A, B>()(a, b);
}

} // namespace id
