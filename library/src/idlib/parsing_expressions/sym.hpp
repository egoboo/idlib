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

/// @file idlib/parsing_expressions/sym.hpp
/// @brief "symbol" parsing expression.
/// @author Michael Heilmann

#pragma once

#if !defined(IDLIB_PRIVATE) || IDLIB_PRIVATE != 1
#error(do not include directly, include `idlib/parsing_expressions/include.hpp` instead)
#endif

#include "idlib/parsing_expressions/match.hpp"

#include "idlib/parsing_expressions/header.in"

/// @internal
/// @brief Parsing expression accepting a symbol.
/// @tparam Symbol the symbol type
template <typename Symbol>
struct sym_expr
{
private:
    /// @internal
    /// @brief The symbol.
    Symbol m_x;

public:
    /// @internal
    /// @brief Construct this parsing expression.
    /// @param x the symbol
    sym_expr(Symbol x) :
        m_x(x)
    {}

    template <typename Iterator>
    match<std::decay_t<Iterator>> operator()(Iterator at, Iterator end) const
    {
        if (at != end && m_x == *at)
        {
			return make_match(true, at, std::next(at));
        }
        else
        {
			return make_match(false, at, at);
        }
    }
};

/// @brief Create a parsing expression accepting a symbol.
/// @tparam Symbol the symbol type
/// @param symbol the symbol
/// @return the parsing expression
template <typename Symbol>
sym_expr<Symbol> sym(Symbol symbol)
{
    return sym_expr<Symbol>(symbol);
}

#include "idlib/parsing_expressions/footer.in"
