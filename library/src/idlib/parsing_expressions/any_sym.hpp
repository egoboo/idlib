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

/// @file idlib/parsing_expressions/any_sym.hpp
/// @brief "any symbol" parsing expression.
/// @author Michael Heilmann

#pragma once

#include "idlib/parsing_expressions/match.hpp"

#include "idlib/parsing_expressions/header.in"

/// @internal
/// @see id::any_sym for more information.
/// @tparam Sym the symbol type
template <typename Sym>
class any_sym_expr
{
public:
    /// @internal
    /// @brief Construct this parsing expression.
	any_sym_expr()
	{}

    template <typename Iterator>
    match<std::decay_t<Iterator>> operator()(Iterator at, Iterator end) const
    {
		if (at == end)
		{
			return make_match(false, at, at);
		}
		return make_match(true, at, std::next(at));
    }

}; // class any_sym_expr

/// @brief Create an any symbol parsing expression.
/// The any symbol parsing expression accepts any symbol.
/// @return the parsing expression
/// @tparam Sym the symbol type
template <typename Sym>
any_sym_expr<Sym> any_sym()
{
    return any_sym_expr<Sym>();
}

#include "idlib/parsing_expressions/footer.in"
