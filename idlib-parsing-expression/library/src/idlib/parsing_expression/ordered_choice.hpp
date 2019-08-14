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

#include "idlib/parsing_expression/internal/n_ary_expr.hpp"
#include "idlib/parsing_expression/match.hpp"

#include "idlib/parsing_expression/header.in"

struct tuple_op_ordered_choice
{
private:
    // Terminates the iteration.
    // This is utility code for iterating over an std::tuple.
    template<typename Tuple,
             typename Function,
             typename Iterator>
    match<std::decay_t<Iterator>>
    for_each
        (
            Tuple&& t,
            Function f,
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
        return make_match(false, at, at);
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
            return result;
        }
        return for_each(std::forward<Tuple>(t), f, at, end, std::integral_constant<size_t, Index + 1>()); // Advance.
    }

public:
    // The iteration.
    // This is utility code for iterating over an std::tuple.
    template<typename Tuple,
             typename Function,
             typename Iterator>
    match<std::decay_t<Iterator>>
    for_each
        (
            Tuple&& t,
            Function f,
            Iterator at,
            Iterator end
        ) const
    {
        return for_each(std::forward<Tuple>(t), f, at, end, std::integral_constant<size_t, 0>());
    }

    tuple_op_ordered_choice()
    {}
};

/// @internal
/// @brief See idlib::ordered_choice for more information.
/// @tparam Expr the type of the first expression
/// @tparam Exprs ... the type of the remaining expressions
template <typename Expr, typename ... Exprs>
class ordered_choice_expr : public internal::n_ary_expr<tuple_op_ordered_choice, Expr, Exprs ...>
{
public:
    /// @internal
    /// @brief Construct this parsing expression.
    /// @param expr the first expression
    /// @param exprs the remaining expressions
    ordered_choice_expr(internal::constructor_access_token, const Expr& expr, const Exprs& ... exprs) :
        internal::n_ary_expr<tuple_op_ordered_choice, Expr, Exprs ...>(internal::constructor_access_token{}, expr, 
                             exprs ...)
    {}

    struct f {
      template<typename T, typename It>
      auto operator()(const T& expr, It at, It end) const
      {
        auto result = expr(at, end);
        return result ? result : make_match(false, at, at);
      }
    };

    template <typename It>
    idlib::parsing_expression::match<std::decay_t<It>> operator()(It at, It end) const
    {
        static const tuple_op_ordered_choice op;

        auto result = op.for_each(this->m_exprs, f{},
                                  at, 
                                  end);
        return result;
    }
};

/// @brief Create the ordered choice of one or more parsing expressions.
/// The ordered choice of a one or more parsing expressions accepts if at least one of the parsing expressions accepts.
/// If several of these parsing expressions would accept, the first (in left to right order) accepting parsing expression is considered as accepting.
/// @detail That is, the @a choice of @code{n > 0} parsing expressions @code{e1}, ..., @code{en}
/// is defined as
/// @code{ordered_choice(e1, ..., en) = e1 / ...  / en}.
/// @tparam Expr the type of the first expression
/// @tparam Exprs ... the types of the remaining expressions
/// @param expr the first expression
/// @param exprs the remaining expressions
/// @return the parsing expression
template <typename Expr, typename ... Exprs>
ordered_choice_expr<std::decay_t<Expr>, std::decay_t<Exprs> ...> ordered_choice(Expr&& expr, Exprs&& ... exprs)
{
    return ordered_choice_expr<std::decay_t<Expr>, std::decay_t<Exprs> ...>(internal::constructor_access_token{}, std::forward<Expr>(expr), std::forward<Exprs>(exprs) ...);
}

#include "idlib/parsing_expression/footer.in"
