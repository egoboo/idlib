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

/// @file idlib/parsing_expressions/sym_range.hpp
/// @brief "range" parsing expression.
/// @author Michael Heilmann

#pragma once

#if !defined(IDLIB_PRIVATE) || IDLIB_PRIVATE != 1
#error(do not include directly, include `idlib/parsing_expressions/include.hpp` instead)
#endif

#include "idlib/parsing_expressions/match.hpp"

#include "idlib/parsing_expressions/header.in"

/// @internal
/// @brief Parsing expression accepting a range of symbols.
/// @tparam Symbol the symbol type
template <typename Symbol>
struct sym_range_expr
{
private:
    /// @internal
    /// @brief The first symbol (incl.).
    Symbol m_first;

    /// @internal
    /// @brief The last symbol (incl.).
    Symbol m_last;

public:
    /// @internal
    /// @brief Construct this parsing expression.
    /// @param first the first symbol (incl.)
    /// @param last the last symbol (incl.)
    sym_range_expr(Symbol first, Symbol last) :
        m_first(first), m_last(last)
    {}

    template <typename Iterator>
    match<std::decay_t<Iterator>> operator()(Iterator at, Iterator end) const
    {
        if (at != end && (m_first <= *at && *at <= m_last))
        {
			return make_match(true, at, std::next(at));
        }
        else
        {
			return make_match(false, at, at);
        }
    }
};

/// @brief Create a parsing expression accepting a range of symbols.
/// @tparam Symbol the symbol type
/// @param first the first symbol (incl.)
/// @param last the last symbol (incl.)
/// @return the parsing expression
template <typename Symbol>
sym_range_expr<Symbol> sym_range(Symbol first, Symbol last)
{
    return sym_range_expr<Symbol>(first, last);
}

#include "idlib/parsing_expressions/footer.in"
