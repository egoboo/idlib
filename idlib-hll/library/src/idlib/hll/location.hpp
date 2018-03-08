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

/// @file idlib/hll/location.hpp
/// @brief Definition of a location in a text.
/// @author Michael Heilmann

#pragma once

#if !defined(IDLIB_PRIVATE) || IDLIB_PRIVATE != 1
#error(do not include directly, include `idlib/hll.hpp` instead)
#endif

#include "idlib/crtp.hpp"
#include <string>
#include <type_traits>

namespace idlib::hll {

/// @brief A location is identified by a file name and line number within that file.
class location final
{
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

private:
    /// @brief The file name of the file.
    std::string m_file_name;

    /// @brief The line number of a line within the file.
    size_t m_line_number;

}; // class location

static_assert(std::is_copy_constructible<location>::value, "idlib::hll::location must be copy constructible");

static_assert(std::is_move_constructible<location>::value, "idlib::hll::location must be move constructible");
static_assert(std::is_nothrow_move_constructible<std::string>::value == std::is_nothrow_move_constructible<location>::value,
              "idlib::hll::location is nothrow move constructible iff std::string is nothrow move constructible");

static_assert(std::is_copy_assignable<location>::value, "idlib::hll::location must be copy assignable");

static_assert(std::is_move_assignable<location>::value, "idlib::hll::location must be move assignable");
static_assert(std::is_nothrow_move_assignable<std::string>::value == std::is_nothrow_move_assignable<location>::value,
              "idlib::hll::location is nothrow move assignable iff std::string is nothrow move assignable");

#if !defined(__GNUC__) || __GNUC__ > 6
static_assert(std::is_swappable<location>::value, "idlib::hll::location must be swappable");
static_assert(std::is_nothrow_swappable<std::string>::value == std::is_nothrow_swappable<location>::value,
              "idlib::hll::location is nothrow swappable iff std::string is nothrow swappable");
#endif

} // namespace idlib::c
