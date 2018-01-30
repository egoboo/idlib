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

/// @file idlib/parsing_expressions/sym.hpp
/// @brief "symbol" parsing expression.
/// @author Michael Heilmann

#pragma once

#if !defined(IDLIB_PRIVATE) || IDLIB_PRIVATE != 1
#error(do not include directly, include `idlib/parsing_expressions/include.hpp` instead)
#endif

#include "idlib/parsing_expressions/internal/constructor_access_token.hpp"
#include "idlib/parsing_expressions/match.hpp"

#include "idlib/parsing_expressions/header.in"

/// @internal
/// @brief See idlib::option for more information.
/// @tparam Expr the expression type
template <typename Expr>
struct option_expr
{
private:
    /// @internal
    /// @brief The parsing expression.
    Expr m_expr;

public:
    /// @internal
    /// @brief Construct this parsing expression.
    /// @param expr the expression
    option_expr(internal::constructor_access_token, const Expr& expr) :
        m_expr(expr)
    {}

    template <typename It>
    match<std::decay_t<It>> operator()(It at, It end) const
    {
        auto result = m_expr(at, end);
        if (result)
        {
			return result;
        }
        else
        {
			return make_match(true, at, at);
        }
    }
};

/// @brief Create an option of a parsing expression.
/// The option of a parsing expression accepts regardless of wether the parsing expression acccepts.
/// @detail That is, the @a option of a parsing expressions @code{e}
/// is defined as
/// @code{option(e) = e?}.
/// @tparam Expr the type of the expression
/// @param expr the expression
/// @return the parsing expression
template <typename Expr>
option_expr<std::decay_t<Expr>> option(Expr&& expr)
{
    return option_expr<std::decay_t<Expr>>(internal::constructor_access_token{}, std::forward<Expr>(expr));
}

#include "idlib/parsing_expressions/footer.in"
