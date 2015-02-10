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

/// @file idlib/parsing_expressions/repetition.hpp
/// @brief "repetition" parsing expression.
/// @author Michael Heilmann

#pragma once

#if !defined(IDLIB_PRIVATE) || IDLIB_PRIVATE != 1
#error(do not include directly, include `idlib/parsing_expressions/include.hpp` instead)
#endif

#include "idlib/parsing_expressions/internal/constructor_access_token.hpp"
#include "idlib/parsing_expressions/match.hpp"

#include "idlib/parsing_expressions/header.in"

/// @internal
/// @brief See id::repetition for more information.
/// @tparam Expr the type of the expression
template <typename Expr>
struct repetition_expr
{
private:
    /// @internal
    /// @brief The parsing expression.
    Expr m_expr;

public:
    /// @internal
    /// @brief Construct this parsing expression.
    /// @param expr the expression
    repetition_expr(internal::constructor_access_token, const Expr& expr) :
        m_expr(expr)
    {}

    template <typename It>
    match<std::decay_t<It>> operator()(It at, It end) const
    {
		auto result = make_match(true, at, at);
        while (true)
        {
            auto next_result = m_expr(result.range().end(), end);
            if (next_result)
            {
                result = make_match(true, at, next_result.range().end());
            }
            else
            {
                break;
            }
        }
        return result;
    }
};

/// @brief Create a repetition of a parsing expression.
/// The repetition of a parsing expression accepts if the parsing expression accepts zero or more times.
/// @detail That is, the @a repetition of a parsing expressions @code{e}
/// is defined as
/// @code{repetition(e) = e*}.
/// @tparam Expr the type of the expression
/// @param expr the expression
/// @return the parsing expression
template <typename Expr>
repetition_expr<std::decay_t<Expr>> repetition(Expr&& expr)
{
    return repetition_expr<std::decay_t<Expr>>(internal::constructor_access_token{}, std::forward<Expr>(expr));
}

#include "idlib/parsing_expressions/footer.in"
