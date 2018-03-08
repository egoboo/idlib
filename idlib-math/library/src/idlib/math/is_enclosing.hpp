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

/// @file idlib/math/is_enclosing.hpp
/// @brief "is enclosing" functor and function
/// @author Michael Heilmann

#pragma once

namespace idlib {
	
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

} // namespace idlib
