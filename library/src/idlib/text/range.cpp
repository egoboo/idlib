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

/// @file idlib/text/range.cpp
/// @brief Information on a text range in a text.
/// @author Michael Heilmann

#define IDLIB_PRIVATE 1
#include "idlib/text/range.hpp"
#undef IDLIB_PRIVATE

namespace id {

text_range::text_range(std::size_t start, std::size_t length) noexcept :
	start(start), length(length)
{}

text_range::text_range(const text_range& other) noexcept :
	start(other.start), length(other.length)
{}

text_range& text_range::operator=(const text_range& other) noexcept
{
	start = other.start;
	length = other.length;
	return *this;
}

bool text_range::is_empty() const noexcept
{
	return 0 == get_length();	
}

std::size_t text_range::get_start() const noexcept
{
	return start;
}

#if defined(ID_TEXT_RANGE_MUTABLE) && 1 == ID_TEXT_RANGE_MUTABLE
void text_range::set_start(std::size_t start) noexcept
{
	this->start = start;
}
#endif

std::size_t text_range::get_length() const noexcept
{
	return length;
}

#if defined(ID_TEXT_RANGE_MUTABLE) && 1 == ID_TEXT_RANGE_MUTABLE
void text_range::set_length(std::size_t length) noexcept
{
	this->length = length;
}
#endif

} // namespace id
