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

/// @file idlib/math/translate.hpp
/// @brief "translate" functor and function
/// @author Michael Heilmann

#pragma once

namespace id {

/// @ingroup math
/// @brief Functor translating geometries.
/// @details
/// Consider geometries as sets of points. A geometry \f$a\f$ translated by a translation vector \f$t\f$ is a geometry \f$b\f$ containing all the points of \f$a\f$ translated by \f$t\f$.
/// @details
/// Specializations of this functor provide a constant operator(). Its first argument is a geometry \f$a\f$ of type \f$A\f$,
/// its second argument is a translation vector \f$t\f$ of type \f$T\f$. It returns a
/// its first argument an a translation vector \f$t\f$ of type \f$T\f$ as its second argument. It   returns
/// a single value \f$e'\f$ of type \f$E\f$. Consider entities as set of points: Then \f$e'\f$ consists  of
/// the points of \f$e\f$ translated by \f$\vec{t}\f$.
/// @details
/// Specializations provide two member types:
/// - @a vector_type which is \f$T\f$
/// - @a geometry_type which is \f$A\f$
/// @tparam A the type of the translated geometries
/// @tparam T the type of the translation vectors
/// @remark Feel free to provide your own implementation.
template <typename A, typename T>
struct translate_functor;

template <typename A, typename T>
auto translate(const A& a, const T& t) -> decltype(translate_functor<A, T>()(a, t))
{
	return translate_functor<A, T>()(a, t);
}

} // namespace id
