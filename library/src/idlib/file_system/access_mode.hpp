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

/// @file idlib/file_system/access_mode.hpp
/// @brief Access mode for files.
/// @author Michael Heilmann

#pragma once

#include "idlib/utility/platform.hpp"
#include "idlib/utility/bitmask_type.hpp"

#include "idlib/file_system/header.in"

enum class access_mode : uint8_t 
{
    none = 0, ///< Neither read nor write access.
    read = (1 << 1), ///< Read access.
    write = (1 << 2), ///< Write acccess.
    read_write = read | write, ///< Alias for @code{read|write}.
    write_read = write | read, ///< Alias for @code{write|read}.
    all = read_write, ///< Alias for @ode{read_write}. 
};

#include "idlib/file_system/footer.in"

/// Bitwise |.
inline id::file_system::access_mode operator|(id::file_system::access_mode lhs, id::file_system::access_mode rhs)
{
    return static_cast<id::file_system::access_mode>(static_cast<uint8_t>(lhs) | static_cast<uint8_t>(rhs));
}

// Bitwise &.
inline id::file_system::access_mode operator&(id::file_system::access_mode lhs, id::file_system::access_mode rhs)
{
    return static_cast<id::file_system::access_mode>(static_cast<uint8_t>(lhs) & static_cast<uint8_t>(rhs));
}

// Bitwise ^.
inline id::file_system::access_mode operator^(id::file_system::access_mode lhs, id::file_system::access_mode rhs)
{
    return static_cast<id::file_system::access_mode>((static_cast<uint8_t>(lhs) ^ static_cast<uint8_t>(rhs)) & static_cast<uint8_t>(id::file_system::access_mode::all));
}

// Bitwise ~.
inline id::file_system::access_mode operator~(id::file_system::access_mode lhs)
{
    return static_cast<id::file_system::access_mode>((~static_cast<uint8_t>(lhs)) & static_cast<uint8_t>(id::file_system::access_mode::all));
}

// Bitwise |=.
inline id::file_system::access_mode& operator|=(id::file_system::access_mode& lhs, id::file_system::access_mode rhs)
{
    lhs = static_cast<id::file_system::access_mode>(static_cast<uint8_t>(lhs) | static_cast<uint8_t>(rhs));
    return lhs;
}

// Bitwise &=.
inline id::file_system::access_mode& operator&=(id::file_system::access_mode& lhs, id::file_system::access_mode rhs)
{
    lhs = static_cast<id::file_system::access_mode>(static_cast<uint8_t>(lhs) & static_cast<uint8_t>(rhs));
    return lhs;
}

// Bitwise ^=.
inline id::file_system::access_mode& operator^=(id::file_system::access_mode& lhs, id::file_system::access_mode rhs)
{
    lhs = static_cast<id::file_system::access_mode>((static_cast<uint8_t>(lhs) ^ static_cast<uint8_t>(rhs))
                                                    & static_cast<uint8_t>(id::file_system::access_mode::all));
    return lhs;
}
