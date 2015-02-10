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

/// @file idlib/parsing_expressions/any_sym.hpp
/// @brief "any symbol" parsing expression.
/// @author Michael Heilmann

#include "idlib/utility/platform.hpp"

#include "idlib/parsing_expressions/header.in"

/// @internal
/// @brief See id::difference for more information.
/// @tparam Expression1 the expression type of the first expression
/// @tparam Expression2 the expression type of the second expression
template <typename Expression1, typename Expression2>
class difference_expression
{
private:
    /// @brief The first expression.
    Expression1 m_expression1;
    /// @brief The second expression.
    Expression2 m_expression2;
public:
    /// @internal
    /// @brief Construct this parsing expression.
    /// @param expression1 the first expression
    /// @param expression2 the second expression
    difference_expression(Expression1 expression1, Expression2 expression2) :
        m_expression1(expression1), m_expression2(expression2)
    {}

    template <typename Iterator>
    match<std::decay_t<Iterator>> operator()(Iterator at, Iterator end) const
    {
        auto result1 = m_expression1(at, end);
        if (result1)
        {
            auto result2 = m_expression2(at, end);
            if (!result2)
            {
                return result1;
            }
        }
		return make_match(false, at, at);
    }

}; // class difference_expr

/// @brief Create a difference of a parsing expression and another parsing expression.
/// The difference of a parsing expression and another parsing expression accepts if the former accepts and the latter does not accept.
/// @tparam Expression1 the type of the first expression
/// @tparam Expression2 the type of the second expression
/// @param expression1 the first expression
/// @param expression2 the second expression
/// @return the parsing expression
template <typename Expression1, typename Expression2>
difference_expression<Expression1, Expression2> difference(Expression1 expression1, Expression2 expression2)
{
    return difference_expression<Expression1, Expression2>(expression1, expression2);
}

#include "idlib/parsing_expressions/footer.in"
