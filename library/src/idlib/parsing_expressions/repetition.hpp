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
