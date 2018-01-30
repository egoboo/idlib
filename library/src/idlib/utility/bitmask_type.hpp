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

/// @file idlib/utility/bitmask_type.hpp
/// @brief Functionality to make an enum class a bitmask type.
/// @author Michael Heilmann

#pragma once

#include <type_traits>

#if !defined(IDLIB_PRIVATE) || IDLIB_PRIVATE != 1
#error(do not include directly, include `idlib/idlib.hpp` instead)
#endif

#include "idlib/utility/header.in"

/// 17.5.2.1.3 [bitmask.types] of the C++ Standard: 
/// Bitmask types shall provide definitions for the operators |, &, ^, ~, |=, &= and ^= with the expected semantics.
/// For scoped enums to be used as bitmasks, simply define
/// @code
/// template<>
/// struct enable_bitmask_operators<T> { static constexpr bool enable = true; }
/// @endcode
template<typename E>
struct enable_bitmask_operators
{
    static constexpr bool enable = false;
};

#include "idlib/utility/footer.in"

/// Bitwise |.
template<typename E>
std::enable_if_t<idlib::enable_bitmask_operators<E>::enable, E>
operator|(E lhs, E rhs)
{
    typedef std::underlying_type_t<E> underlying;
    return static_cast<E>(
        static_cast<underlying>(lhs) | static_cast<underlying>(rhs));
}

// Bitwise &.
template<typename E>
std::enable_if_t<idlib::enable_bitmask_operators<E>::enable, E>
operator&(E lhs, E rhs)
{
    typedef std::underlying_type_t<E> underlying;
    return static_cast<E>(
        static_cast<underlying>(lhs) & static_cast<underlying>(rhs));
}

// Bitwise ^.
template<typename E>
std::enable_if_t<idlib::enable_bitmask_operators<E>::enable, E>
operator^(E lhs, E rhs)
{
    typedef std::underlying_type_t<E> underlying;
    return static_cast<E>(
        static_cast<underlying>(lhs) ^ static_cast<underlying>(rhs));
}

// Bitwise ~.
template<typename E>
std::enable_if_t<idlib::enable_bitmask_operators<E>::enable, E>
operator~(E lhs)
{
    typedef std::underlying_type_t<E> underlying;
    return static_cast<E>(
        ~static_cast<underlying>(lhs));
}

// Bitwise |=.
template<typename E>
std::enable_if_t<idlib::enable_bitmask_operators<E>::enable, E&>
operator|=(E& lhs, E rhs)
{
    typedef std::underlying_type_t<E> underlying;
    lhs = static_cast<E>(
        static_cast<underlying>(lhs) | static_cast<underlying>(rhs));
    return lhs;
}

// Bitwise &=.
template<typename E>
std::enable_if_t<idlib::enable_bitmask_operators<E>::enable, E&>
operator&=(E& lhs, E rhs)
{
    typedef std::underlying_type_t<E> underlying;
    lhs = static_cast<E>(
        static_cast<underlying>(lhs) & static_cast<underlying>(rhs));
    return lhs;
}

// Bitwise ^=.
template<typename E>
std::enable_if_t<idlib::enable_bitmask_operators<E>::enable, E&>
operator^=(E& lhs, E rhs)
{
    typedef std::underlying_type_t<E> underlying;
    lhs = static_cast<E>(
        static_cast<underlying>(lhs) ^ static_cast<underlying>(rhs));
    return lhs;
}
