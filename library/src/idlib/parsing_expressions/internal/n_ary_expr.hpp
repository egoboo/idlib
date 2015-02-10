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

#pragma once

#if !defined(IDLIB_PRIVATE) || IDLIB_PRIVATE != 1
#error(do not include directly, include `idlib/parsing_expressions/include.hpp` instead)
#endif

#include "idlib/parsing_expressions/internal/constructor_access_token.hpp"

#include "idlib/parsing_expressions/internal/header.in"

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

#include "idlib/parsing_expressions/internal/footer.in"
