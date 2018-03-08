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

/// @file idlib/parsing_expression/sequence.hpp
/// @brief "sequence" parsing expression.
/// @author Michael Heilmann

#pragma once

#if !defined(IDLIB_PRIVATE) || IDLIB_PRIVATE != 1
#error(do not include directly, include `idlib/parsing_expression.hpp` instead)
#endif

#include "idlib/parsing_expression/internal/n_ary_expr.hpp"
#include "idlib/parsing_expression/match.hpp"

#include "idlib/parsing_expression/header.in"

struct tuple_op_sequence
{
private:
    // Terminates the iteration.
    // This is utility code for iterating over an std::tuple.
    template<typename Tuple, typename Function, typename Iterator>
    match<std::decay_t<Iterator>>
    for_each
        (
            Tuple&&,
            Function,
            Iterator at,
            Iterator end,
            std::integral_constant
                <
                    size_t,
                    std::tuple_size
                        <
                            std::remove_reference_t<Tuple>
                        >::value
                >
        ) const
    {
		return make_match(true, idlib::make_iterator_range(at, at));
    }

    // Drives the iteration.
    // This is utility code for iterating over an std::tuple.
    template<std::size_t Index,
             typename Tuple,
             typename Function,
             typename Iterator,
             typename = std::enable_if_t
                            <
                                Index != std::tuple_size
                                            <
                                                std::remove_reference_t<Tuple>
                                            >::value
                            >
            >
    match<std::decay_t<Iterator>>
    for_each
        (
            Tuple&& t,
            Function f,
            Iterator at,
            Iterator end,
            std::integral_constant<size_t, Index>
        ) const
    {
        auto result = f(std::get<Index>(t), at, end);
        if (result)
        {
            return for_each(std::forward<Tuple>(t), f, result.range().end(), end, std::integral_constant<size_t, Index + 1>()); // Advance.
        }
		return make_match(false, idlib::make_iterator_range(at, at));
    }

public:
    // The iteration.
    // This is utility code for iterating over an std::tuple.
    template<typename Tuple,
             typename Function,
             typename It>
    match<std::decay_t<It>>
    for_each
        (
            Tuple&& t,
            Function f,
            It at,
            It end
        ) const
    {
        return for_each(std::forward<Tuple>(t), f, at, end, std::integral_constant<size_t, 0>());
    }

    tuple_op_sequence()
    {}
};

/// @internal
/// @brief See idlib::sequence for more information.
/// @tparam Expr the type of the first expression
/// @tparam Exprs ... the type of the remaining expressions
template <typename Expression, typename ... Expressions>
struct sequence_expr : public internal::n_ary_expr<tuple_op_sequence, Expression, Expressions ...>
{
public:
    /// @internal
    /// @brief Construct this parsing expression.
    /// @param expression the first expression
    /// @param expressions the remaining expressions
    sequence_expr(internal::constructor_access_token, const Expression& expression, const Expressions& ... expressions) :
        internal::n_ary_expr<tuple_op_sequence, Expression, Expressions ...>(internal::constructor_access_token{}, expression, expressions ...)
    {}

    template <typename Iterator>
    match<std::decay_t<Iterator>> operator()(Iterator at, Iterator end) const
    {
        static const tuple_op_sequence op;
        auto result = op.for_each(this->m_exprs,
                                  [](const auto& expr, Iterator at, Iterator end) 
                                    {
                                        return expr(at, end);
                                    },
                                  at, 
                                  end);
        if (result)
        {
			return make_match(true, idlib::make_iterator_range(at, result.range().end()));
        }
		return make_match(false, idlib::make_iterator_range(at, at));
    }
};

/// @brief Create the sequence of a one or more parsing expressions.
/// The sequence of one or more parsing expressions accepts if all parsing expression of one or more parsing expressions accept.
/// @detail That is, the @a sequence of @code{n > 0} parsing expressions @code{e1}, ..., @code{en}
/// is defined as
/// @code{sequence(e1, ..., en) = e1 ...  en}.
/// @tparam Expression the type of the first expression
/// @tparam Expressions ... the types of the remaining expressions
/// @param expression the first expression
/// @param expressions the remaining expressions
/// @return the parsing expression
template <typename Expression, typename ... Expressions>
sequence_expr<std::decay_t<Expression>, std::decay_t<Expressions> ...> sequence(Expression&& expression, Expressions&& ... expressions)
{
    return sequence_expr<std::decay_t<Expression>, std::decay_t<Expressions> ...>(internal::constructor_access_token{}, std::forward<Expression>(expression), std::forward<Expressions>(expressions) ...);
}

#include "idlib/parsing_expression/footer.in"
