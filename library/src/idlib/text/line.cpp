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

#define IDLIB_PRIVATE 1
#include "idlib/text/line.hpp"
#undef IDLIB_PRIVATE

namespace id {
	
text_line::text_line() :
	m_range(0, 0), m_width(0), m_height(0)
{}

text_line::text_line(const text_range& range) :
	m_range(range), m_width(0), m_height(0)
{}

text_range text_line::get_range() const
{ return m_range; }

#if defined(ID_TEXT_LINE_MUTABLE) && 1 == ID_TEXT_LINE_MUTABLE
void text_line::set_range(const text_range& range)
{ m_range = range; }
#endif

int text_line::get_width() const
{ return m_width; }

#if defined(ID_TEXT_LINE_MUTABLE) && 1 == ID_TEXT_LINE_MUTABLE
void text_line::set_width(int width)
{ m_width = width; }
#endif

int text_line::get_height() const
{ return m_height; }

#if defined(ID_TEXT_LINE_MUTABLE) && 1 == ID_TEXT_LINE_MUTABLE
void text_line::set_height(int height)
{ m_height = height; }
#endif
	
} // namespace id
