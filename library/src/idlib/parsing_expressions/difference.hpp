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
