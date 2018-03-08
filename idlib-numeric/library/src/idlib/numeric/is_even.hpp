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

/// @file idlib/numeric/is_even.hpp
/// @brief Functionality to determine wether a value is even or odd.
/// @detail Further reading "Why Not Specialize Function Templates?"
/// (http://www.gotw.ca/publications/mill17.htm).
/// @author Michael Heilmann

#pragma once

#if !defined(IDLIB_PRIVATE) || IDLIB_PRIVATE != 1
#error(do not include directly, include `idlib/numeric.hpp` instead)
#endif

namespace idlib {
    
/// @ingroup math
/// @brief Functor which determines wether a value is even.
/// It defines an operator
/// @code{constexpr bool operator()(T x) const noexcept}
/// which returns @a true if the value @a x is even and returns @a false if the value is odd.
/// @tparam T the type of the value
/// @tparam Enabled SFINAE support
/// @remark Feel free to provide your own implementation.
/// Specialization for all integral types excluding @a bool are provided.
/// Implementations for built-in types work regardless of the machine representation and are as fast as any bit hack.
template <typename T, typename Enabled = void>
class is_even_functor;

/// @brief Get if the specified value is odd.
/// @param x the value
/// @return @a true if @a x is odd, @a false otherwise
/// @remark This is a forwarding function forwarding to idlib::is_even_functor.
/// To support your custom type, add a specialization of the idlib::is_even_functor.
template <typename T>
constexpr bool is_even(T&& x) noexcept
{ return is_even_functor<T>()(std::forward<T>(x)); }
    
} // namespace idlib
