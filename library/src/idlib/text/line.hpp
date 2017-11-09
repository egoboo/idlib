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

/// @file idlib/text/line.hpp
/// @brief Information on a text line in a text.
/// @author Michael Heilmann

#pragma once

#if !defined(IDLIB_PRIVATE) || IDLIB_PRIVATE != 1
#error(do not include directly, include `idlib/idlib.hpp` instead)
#endif

#include "idlib/text/range.hpp"

/// @brief If defined to @a 1, text ranges are mutable i.e. provide setters.
#define ID_TEXT_LINE_MUTABLE (1)

namespace id {

/// @brief Information on a text line of a text.
/// @remarks Consists of the range and the width and the height of the line.
class text_line
{
public:
	/// @brief Construct a text line with a range of <0,0> and a width and a height of @a 0.
	text_line();
	
	/// @brief Construct a text line with the specified range and a width and a height of @a 0.
	text_line(const text_range& range);
	
	/// @brief Get the range of this text line.
	/// @return the range
	text_range get_range() const;
	
#if defined(ID_TEXT_LINE_MUTABLE) && 1 == ID_TEXT_LINE_MUTABLE
	/// @brief Set the range of this text line.
	/// @param range the range
	void set_range(const text_range& range);
#endif
	
	/// @brief Get the width of the text line.
	/// @return the width
	int get_width() const;
	
#if defined(ID_TEXT_LINE_MUTABLE) && 1 == ID_TEXT_LINE_MUTABLE
	/// @brief Set the width of the text line.
	/// @param width the width
	void set_width(int width);
#endif
	
	/// @brief Get the height of the text line.
	/// @return the height
	int get_height() const;

#if defined(ID_TEXT_LINE_MUTABLE) && 1 == ID_TEXT_LINE_MUTABLE
	/// @brief Set the height of the text line.
	/// @param height the height
	void set_height(int height);
#endif
	
private:
	text_range m_range; ///< @brief The text range of this text line.
	int m_width;        ///< @brief The width of this text line.
	int m_height;       ///< @brief The height of this text line.
	
}; // class text_line

static_assert(std::is_copy_constructible<text_line>::value, "id::text_line must be copy constructible");
static_assert(std::is_move_constructible<text_line>::value, "id::text_line must be move constructible");
static_assert(std::is_copy_assignable<text_line>::value, "id::text_line must be copy assignable");
static_assert(std::is_move_assignable<text_line>::value, "id::text_line must be move assignable");

} // namespace id
