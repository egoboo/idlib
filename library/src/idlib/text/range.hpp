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

/// @file idlib/text/range.hpp
/// @brief Information on a text range in a text.
/// @author Michael Heilmann

#pragma once

#if !defined(IDLIB_PRIVATE) || IDLIB_PRIVATE != 1
#error(do not include directly, include `idlib/idlib.hpp` instead)
#endif

#include <cstddef>
#include <type_traits>

/// @brief If defined to @a 1, text ranges are mutable i.e. provide setters.
#define ID_TEXT_RANGE_MUTABLE (0)

namespace id {

/// @brief Information on a text range in a text.
/// @remarks Consists of the start index and the length of the range.
class text_range
{
public:
    /// @brief Construct this text range with the specified values.
    /// @param start the codepoint at which this text range starts at
    /// @param length the length of this text range in codepoints
    text_range(std::size_t start, std::size_t length) noexcept;

public:
    /// @brief Construct this text range with the values of another text range.
    /// @param other the other text range
    text_range(const text_range& other) noexcept;

    /// @brief Assign this text range with the values of another text range.
    /// @param other the other text range
    /// @return this text range
    text_range& operator=(const text_range& other) noexcept;

public:
    /// @brief Get if this text range is empty.
    /// @return @a true if this text range is empty, @a false otherwise
    bool is_empty() const noexcept;

public:
    /// @brief Get the codepoint at which the text range starts.
    /// @return the codepoint at which the text range starts
    std::size_t get_start() const noexcept;

#if defined(ID_TEXT_RANGE_MUTABLE) && 1 == ID_TEXT_RANGE_MUTABLE
    /// @brief Set the codepoint at which this text range starts.
    /// @param start the codepoint at which this text range starts
    void set_start(std::size_t start) noexcept;
#endif

    /// @brief Get the length of this text range in codepoints.
    /// @return the length of this text range in codepoints
    std::size_t get_length() const noexcept;

#if defined(ID_TEXT_RANGE_MUTABLE) && 1 == ID_TEXT_RANGE_MUTABLE
    /// @brief Set the length of this text range in codepoints.
    /// @param length the length of this text range in codepoints
    void set_length(std::size_t length) noexcept;
#endif

private:
    /// @brief The codepoint at which the text range starts.
    std::size_t start;

    /// @brief The length of the text range in codepoints.
    std::size_t length;

}; // class text_range

static_assert(std::is_copy_constructible<text_range>::value, "id::text_range must be copy constructible");
static_assert(std::is_move_constructible<text_range>::value, "id::text_range must be move constructible");
static_assert(std::is_copy_assignable<text_range>::value, "id::text_range must be copy assignable");
static_assert(std::is_move_assignable<text_range>::value, "id::text_range must be move assignable");

} // namespace id
