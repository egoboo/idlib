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

/// @file idlib/numeric/zero.hpp
/// @brief Functionality to determine the zero value of set of values.
/// @detail Further reading "Why Not Specialize Function Templates?"
/// (http://www.gotw.ca/publications/mill17.htm).
/// @author Michael Heilmann

#pragma once

#if !defined(IDLIB_PRIVATE) || IDLIB_PRIVATE != 1
#error(do not include directly, include `idlib/numeric.hpp` instead)
#endif

#include <type_traits>

namespace idlib {

/// @ingroup math
/// @brief The zero element of a domain of values (e.g. int, float, user-defined types, ...)
/// over which the operations addition and subtraction are defined has the properties
/// - \f$0 + x = x\f$
/// - \f$x + 0 = x\f$
/// - \f$0 \cdot x = 0\f$
/// - \f$x \cdot 0 = 0\f$
/// If in addition the negation operation is defined then in addition the property
/// - \f$-0 = 0\f$
/// holds.
/// @tparam T the type of the values
/// @tparam E SFINAE support
/// @remark Feel free to provide your own implementation.
/// Specialization for all integral types excluding @a bool are provided.
/// Specializations for @a float and @a double are provided.
template <typename T, typename E = void>
struct zero_functor;

/// @brief Get the zero value the type @a T.
/// @tparam T the type
/// @return the zero value of the type @a T
template <typename T>
decltype(auto) zero()
{ return zero_functor<T>()(); }

} // namespace idlib
