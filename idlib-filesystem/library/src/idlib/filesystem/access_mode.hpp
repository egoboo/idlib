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

/// @file idlib/filesystem/access_mode.hpp
/// @brief Access mode for files.
/// @author Michael Heilmann

#pragma once

#include "idlib/platform.hpp"
#include <cstdint>

#include "idlib/filesystem/header.in"

/// @brief Flags which determine how a file is accessed.
/// @remark All bitwise operators (|, ^, &, ~) and their compound-assignment forms are supported between access_mode enum element values.
/// A value of an expression a o b where o is a bitwise operator and a and b are access_mode enum element values is always access_mode enum element value.
enum class access_mode : uint8_t 
{
    none = 0, ///< Neither read nor write access.
    read = (1 << 1), ///< Read access.
    write = (1 << 2), ///< Write access.
    read_write = read | write, ///< Alias for @code{read|write}.
    write_read = write | read, ///< Alias for @code{write|read}.
    all = read_write, ///< Alias for @ode{read_write}. 
};

#include "idlib/filesystem/footer.in"

/// Bitwise |.
inline idlib::file_system::access_mode operator|(idlib::file_system::access_mode lhs, idlib::file_system::access_mode rhs)
{
    return static_cast<idlib::file_system::access_mode>(static_cast<uint8_t>(lhs) | static_cast<uint8_t>(rhs));
}

// Bitwise &.
inline idlib::file_system::access_mode operator&(idlib::file_system::access_mode lhs, idlib::file_system::access_mode rhs)
{
    return static_cast<idlib::file_system::access_mode>(static_cast<uint8_t>(lhs) & static_cast<uint8_t>(rhs));
}

// Bitwise ^.
inline idlib::file_system::access_mode operator^(idlib::file_system::access_mode lhs, idlib::file_system::access_mode rhs)
{
    return static_cast<idlib::file_system::access_mode>((static_cast<uint8_t>(lhs) ^ static_cast<uint8_t>(rhs)) & static_cast<uint8_t>(idlib::file_system::access_mode::all));
}

// Bitwise ~.
inline idlib::file_system::access_mode operator~(idlib::file_system::access_mode lhs)
{
    return static_cast<idlib::file_system::access_mode>((~static_cast<uint8_t>(lhs)) & static_cast<uint8_t>(idlib::file_system::access_mode::all));
}

// Bitwise |=.
inline idlib::file_system::access_mode& operator|=(idlib::file_system::access_mode& lhs, idlib::file_system::access_mode rhs)
{
    lhs = static_cast<idlib::file_system::access_mode>(static_cast<uint8_t>(lhs) | static_cast<uint8_t>(rhs));
    return lhs;
}

// Bitwise &=.
inline idlib::file_system::access_mode& operator&=(idlib::file_system::access_mode& lhs, idlib::file_system::access_mode rhs)
{
    lhs = static_cast<idlib::file_system::access_mode>(static_cast<uint8_t>(lhs) & static_cast<uint8_t>(rhs));
    return lhs;
}

// Bitwise ^=.
inline idlib::file_system::access_mode& operator^=(idlib::file_system::access_mode& lhs, idlib::file_system::access_mode rhs)
{
    lhs = static_cast<idlib::file_system::access_mode>((static_cast<uint8_t>(lhs) ^ static_cast<uint8_t>(rhs))
                                                       & static_cast<uint8_t>(idlib::file_system::access_mode::all));
    return lhs;
}
