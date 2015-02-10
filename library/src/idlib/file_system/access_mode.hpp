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
