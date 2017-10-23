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

/// @file idlib/location.cpp
/// @brief Definition of a location in a text.
/// @author Michael Heilmann

#define IDLIB_PRIVATE 1
#include "idlib/language/location.hpp"
#undef IDLIB_PRIVATE

namespace id { namespace c {

location::location(const std::string& file_name, const size_t line_number)
    : m_file_name(file_name), m_line_number(line_number)
{}

location::location(const location& other)
    : m_file_name(other.m_file_name), m_line_number(other.m_line_number)
{}

location::location(location&& other) noexcept(std::is_nothrow_move_constructible<std::string>::value)
    : m_file_name(std::move(other.m_file_name)), m_line_number(std::move(other.m_line_number))
{}

location& location::operator=(const location& other)
{
    m_file_name = other.m_file_name;
    m_line_number = other.m_line_number;
    return *this;
}

location& location::operator=(location&& other) noexcept(std::is_nothrow_move_assignable<std::string>::value)
{
    m_file_name = std::move(other.m_file_name);
    m_line_number = std::move(other.m_line_number);
    return *this;
}

bool location::operator==(const location& other) const
{
    return m_file_name == other.m_file_name
        && m_line_number == other.m_line_number;
}

bool location::operator!=(const location&other) const
{
    return !((*this) == other);
}

const std::string& location::file_name() const noexcept
{
    return m_file_name;
}

size_t location::line_number() const noexcept
{
    return m_line_number;
}

} } // namespace id::c
