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

/// @file idlib/math/enclose.hpp
/// @brief "enclose" functor and function
/// @author Michael Heilmann

#pragma once

namespace idlib {

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

} // namespace idlib
