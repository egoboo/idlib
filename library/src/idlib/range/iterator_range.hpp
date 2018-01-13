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

/// @file idlib/range/iterator_range.hpp
/// @brief Root of the exception hierarchy.
/// @author Michael Heilmann

#pragma once

#if !defined(IDLIB_PRIVATE) || IDLIB_PRIVATE != 1
#error(do not include directly, include `idlib/range.hpp` instead)
#endif

#include "idlib/utility/platform.hpp"

#include "idlib/range/header.in"

/// @brief A range adapter for two iterators
/// @tparam Iterator the iterator type.
/// @DefaultConstructible
/// @CopyConstructible
template <typename Iterator>
struct iterator_range
{
public:
	using iterator_type = Iterator;
private:
	iterator_type m_begin;
	iterator_type m_end;

public:
	/// @brief Default construct this iterator range.
	iterator_range() :
		m_begin(), m_end()
	{}

	/// @brief Construct this iterator range.
	/// @param begin, end the iterator pair
	iterator_range(iterator_type begin, iterator_type end) :
		m_begin(begin), m_end(end)
	{}

	iterator_range(const iterator_range&) = default;
	iterator_range& operator=(const iterator_range&) = default;

	/// @{
	/// @brief Get the iterator to the beginning.
	/// @return the iterator to the beginning
	const iterator_type& begin() const { return m_begin; }
	const iterator_type& cbegin() const { return m_begin; }
	/// @}

	/// @{
	/// @brief Get the iterator to the end.
	/// @return the iterator to the end
	const iterator_type& end() const { return m_end; }
	const iterator_type& cend() const { return m_end; }
	/// @}
};

/// @brief Create an iterator range.
/// @tparam Iterator the iterator type
/// @param begin, end the iterator pair
/// @return the iterator range wrapping the iterator pair
template <typename Iterator>
iterator_range<std::decay_t<Iterator>> make_iterator_range(const Iterator& begin, const Iterator& end)
{
	return iterator_range<std::decay_t<Iterator>>(begin, end);
}

#include "idlib/range/footer.in"
