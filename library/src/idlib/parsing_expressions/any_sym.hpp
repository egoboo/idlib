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
