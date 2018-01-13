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
