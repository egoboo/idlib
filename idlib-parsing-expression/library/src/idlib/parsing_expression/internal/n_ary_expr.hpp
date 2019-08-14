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

#pragma once

#if !defined(IDLIB_PRIVATE) || IDLIB_PRIVATE != 1
#error(do not include directly, include `idlib/parsing_expression.hpp` instead)
#endif

#include "idlib/parsing_expression/internal/constructor_access_token.hpp"
#include <type_traits>
#include <tuple>

#include "idlib/parsing_expression/internal/header.in"

/// @internal
/// @brief An \f$n\f$-ary parsing expression (where \f$n>0\f$).
/// @param Op the tuple operation
/// @tparam Expr the type of the first expression
/// @tparam Exprs ... the type of the remaining expressions
template <typename Op, typename Expr, typename ... Exprs>
class n_ary_expr
{
protected:
    /// @internal
    /// @brief The parsing expressions.
    std::tuple<Expr, Exprs ...> m_exprs;

public:
    /// @internal
    /// @brief Construct this $n$-ary parsing expression (where $n > 0$).
    /// @param expr the first expression
    /// @param exprs the remaining expressions
    n_ary_expr(constructor_access_token, const Expr& expr, const Exprs& ... exprs) :
        m_exprs{expr, exprs ...}
    {}
}; // class n_ary_expr

#include "idlib/parsing_expression/internal/footer.in"
