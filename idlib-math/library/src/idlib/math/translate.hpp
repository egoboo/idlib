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

/// @file idlib/math/translate.hpp
/// @brief "translate" functor and function
/// @author Michael Heilmann

#pragma once

namespace idlib {

/// @ingroup math
/// @brief Functor translating geometries.
/// @details
/// Specializations of this functor provide a constant operator().
/// Its first argument is a geometry \f$a\f$ of type \f$A\f$, its second argument is a translation transformation \f$t\f$ of type \f$T\f$.
/// It returns a single value \f$a'\f$ which is the transformed geometry.
/// @details
/// Specializations provide two member types:
/// - @a translation_type which is \f$T\f$
/// - @a geometry_type which is \f$A\f$
/// @tparam A the type of the translated geometries
/// @tparam T the type of the translation transformation
/// @remark Feel free to provide your own implementation.
template <typename A, typename T>
struct translate_functor;

template <typename A, typename T>
auto translate(const A& a, const T& t) -> decltype(translate_functor<A, T>()(a, t))
{ return translate_functor<A, T>()(a, t); }

} // namespace idlib
