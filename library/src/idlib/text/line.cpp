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
