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

/// @file idlib/hll/location.cpp
/// @brief Definition of a location in a text.
/// @author Michael Heilmann

#pragma push_macro("IDLIB_PRIVATE")
#undef IDLIB_PRIVATE
#define IDLIB_PRIVATE (1)

#include "idlib/hll/location.hpp"

#undef IDLIB_PRIVATE
#pragma pop_macro("IDLIB_PRIVATE")

namespace idlib::hll {

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

} // namespace idlib::hll
