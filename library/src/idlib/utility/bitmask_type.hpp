// Copyright Michael Heilmann 2016, 2017.
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
std::enable_if_t<id::enable_bitmask_operators<E>::enable, E>
operator|(E lhs, E rhs)
{
    typedef std::underlying_type_t<E> underlying;
    return static_cast<E>(
        static_cast<underlying>(lhs) | static_cast<underlying>(rhs));
}

// Bitwise &.
template<typename E>
std::enable_if_t<id::enable_bitmask_operators<E>::enable, E>
operator&(E lhs, E rhs)
{
    typedef std::underlying_type_t<E> underlying;
    return static_cast<E>(
        static_cast<underlying>(lhs) & static_cast<underlying>(rhs));
}

// Bitwise ^.
template<typename E>
std::enable_if_t<id::enable_bitmask_operators<E>::enable, E>
operator^(E lhs, E rhs)
{
    typedef std::underlying_type_t<E> underlying;
    return static_cast<E>(
        static_cast<underlying>(lhs) ^ static_cast<underlying>(rhs));
}

// Bitwise ~.
template<typename E>
std::enable_if_t<id::enable_bitmask_operators<E>::enable, E>
operator~(E lhs)
{
    typedef std::underlying_type_t<E> underlying;
    return static_cast<E>(
        ~static_cast<underlying>(lhs));
}

// Bitwise |=.
template<typename E>
std::enable_if_t<id::enable_bitmask_operators<E>::enable, E&>
operator|=(E& lhs, E rhs)
{
    typedef std::underlying_type_t<E> underlying;
    lhs = static_cast<E>(
        static_cast<underlying>(lhs) | static_cast<underlying>(rhs));
    return lhs;
}

// Bitwise &=.
template<typename E>
std::enable_if_t<id::enable_bitmask_operators<E>::enable, E&>
operator&=(E& lhs, E rhs)
{
    typedef std::underlying_type_t<E> underlying;
    lhs = static_cast<E>(
        static_cast<underlying>(lhs) & static_cast<underlying>(rhs));
    return lhs;
}

// Bitwise ^=.
template<typename E>
std::enable_if_t<id::enable_bitmask_operators<E>::enable, E&>
operator^=(E& lhs, E rhs)
{
    typedef std::underlying_type_t<E> underlying;
    lhs = static_cast<E>(
        static_cast<underlying>(lhs) ^ static_cast<underlying>(rhs));
    return lhs;
}
