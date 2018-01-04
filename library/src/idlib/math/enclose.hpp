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

/// @file idlib/math/enclose.hpp
/// @brief "enclose" functor and function
/// @author Michael Heilmann

#pragma once

namespace id {

/// @ingroup math
/// @brief A functor enclosing geometry in other geometry.
/// @details
/// Consider geometries as sets of points. A geometry \f$b\f$ encloses a geometry \f$a\f$ if \f$a \subseteq b\f$.
/// @details
/// Specializations of this functor provide a constant operator() taking a single argument \f$a\f$ of type \f$S\f$
/// and returning a single value \f$b\f$ of type \f$T\f$ both of which are geometries. \f$b\f$ is a geometry enclosing the geometry \f$a\f$.
/// @detail
/// Consider geometries as sets of points. \f$b\f$ is a geometry enclosing \f$a\f$ if \f$a \subseteq b\f$.
/// @details
/// Specializations provide two member types:
/// - @a source_type which is \f$S\f$
/// - @a target_type which is \f$T\f$
/// @tparam S the type of the enclosed geometries
/// @tparam T the type of the enclosing geometries.
/// @remark Feel free to provide your own implementation.
template <typename T, typename S>
struct enclose_functor;

template <typename T, typename S>
auto enclose(const S& s) -> decltype(enclose_functor<T, S>()(s))
{
	return enclose_functor<T, S>()(s);
}

} // namespace id
