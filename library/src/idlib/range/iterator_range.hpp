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
