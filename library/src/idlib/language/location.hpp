// Copyright Michael Heilmann 2016, 2017, 2018.
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

/// @file idlib/language/location.hpp
/// @brief Definition of a location in a text.
/// @author Michael Heilmann

#pragma once

#if !defined(IDLIB_PRIVATE) || IDLIB_PRIVATE != 1
#error(do not include directly, include `idlib/idlib.hpp` instead)
#endif

#include "idlib/crtp.hpp"
#include <type_traits>

namespace id { namespace c {

/// @brief A location is identified by a file name and line number within that file.
class location final
{
private:
    /// @brief The file name of the file.
    std::string m_file_name;

    /// @brief The line number of a line within the file.
    size_t m_line_number;

public:
    /// @brief Construct this location.
    /// @param file_name the file name of the file
    /// @param line_number the line number of a line within the file
    location(const std::string& file_name, const size_t line_number);

    /// @brief Copy-Construct this lociation from another location.
    /// @param other the other location
    location(const location& other);

    /// @brief Move-construct this location from another location.
    /// @param other the other location
    location(location&& other) noexcept(std::is_nothrow_move_constructible<std::string>::value);

    /// @brief Copy assign this location from another location.
    /// @param other the other location
    /// @return this location
    location& operator=(const location& other);

    /// @brief Move assign this location from another location.
    /// @param other the other location
    /// @return this location
    location& operator=(location&& other) noexcept(std::is_nothrow_move_assignable<std::string>::value);

    /// @brief Compare this location to another location.
    /// @param other the other location
    /// @return @a true if this location is equal to the other location, @a false otherwise
    bool operator==(const location& other) const;

    /// @brief Compare this location to another location.
    /// @param other the other location
    /// @return @a true if this location is not equal to the other location, @a false otherwise
    bool operator!=(const location& other) const;
    
    /// @brief Get the file name of the file of this location.
    /// @return the file name of the file
    const std::string& file_name() const noexcept;

    /// @brief Get the line number of a line in the file.
    /// @return the line number of a line in the file
    size_t line_number() const noexcept;

}; // class location

static_assert(std::is_copy_constructible<location>::value, "id::c::location must be copy constructible");

static_assert(std::is_move_constructible<location>::value, "id::location must be move constructible");
static_assert(std::is_nothrow_move_constructible<std::string>::value == std::is_nothrow_move_constructible<location>::value,
              "id::c::location is nothrow move constructible iff std::string is nothrow move constructible");

static_assert(std::is_copy_assignable<location>::value, "id::location must be copy assignable");

static_assert(std::is_move_assignable<location>::value, "id::location must be move assignable");
static_assert(std::is_nothrow_move_assignable<std::string>::value == std::is_nothrow_move_assignable<location>::value,
              "id::c::location is nothrow move assignable iff std::string is nothrow move assignable");

#if !defined(__GNUC__) || __GNUC__ > 6
static_assert(std::is_swappable<location>::value, "id::location must be swappable");
static_assert(std::is_nothrow_swappable<std::string>::value == std::is_nothrow_swappable<location>::value,
              "id::c::location is nothrow swappable iff std::string is nothrow swappable");
#endif

} } // namespace id::c
