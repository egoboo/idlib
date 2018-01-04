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

/// @file idlib/parsing_expressions/match.hpp
/// @brief A match is the result of an evaluation of a parsing expression grammar over an input.
/// @author Michael Heilmann

#pragma once

#if !defined(IDLIB_PRIVATE) || IDLIB_PRIVATE != 1
#error(do not include directly, include `idlib/parsing_expressions/include.hpp` instead)
#endif

#include "idlib/range.hpp"

#include "idlib/parsing_expressions/header.in"

template <typename Iterator>
struct match
{
	using iterator_type = Iterator;
private:
	bool m_outcome;
	id::iterator_range<iterator_type> m_range;
public:
	match(bool outcome, id::iterator_range<iterator_type> range) :
		m_outcome(outcome), m_range(range)
	{}
	/// @brief Get the range of this match.
	/// @return this range of this match
	const id::iterator_range<iterator_type>& range() const
	{
		return m_range;
	}
	/// @brief Get if the match is a success or a failure.
	/// @return @a true if the match is a success, @a false if the match is  failure
	explicit operator bool() const noexcept
	{
		return m_outcome;
	}
};

template <typename Iterator>
inline constexpr match<std::decay_t<Iterator>> make_match(bool outcome, const Iterator& begin, const Iterator& end)
{
	return match<std::decay_t<Iterator>>(outcome, id::make_iterator_range(begin, end));
}

template <typename Range>
inline constexpr match<typename Range::iterator_type> make_match(bool outcome, const Range& range)
{
    return match<typename Range::iterator_type>(outcome, range);
}

#include "idlib/parsing_expressions/footer.in"
