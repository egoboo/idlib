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

/// @file idlib/parsing_expression/match.hpp
/// @brief A match is the result of an evaluation of a parsing expression grammar over an input.
/// @author Michael Heilmann

#pragma once

#if !defined(IDLIB_PRIVATE) || IDLIB_PRIVATE != 1
#error(do not include directly, include `idlib/parsing_expression.hpp` instead)
#endif

#include "idlib/iterator_range.hpp"
#include <type_traits>

#include "idlib/parsing_expression/header.in"

template <typename Iterator>
struct match
{
    using iterator_type = Iterator;
private:
    bool m_outcome;
    idlib::iterator_range<iterator_type> m_range;
public:
    match(bool outcome, idlib::iterator_range<iterator_type> range) :
        m_outcome(outcome), m_range(range)
    {}
    /// @brief Get the range of this match.
    /// @return this range of this match
    const idlib::iterator_range<iterator_type>& range() const
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
    return match<std::decay_t<Iterator>>(outcome, idlib::make_iterator_range(begin, end));
}

template <typename Range>
inline constexpr match<typename Range::iterator_type> make_match(bool outcome, const Range& range)
{
    return match<typename Range::iterator_type>(outcome, range);
}

#include "idlib/parsing_expression/footer.in"
