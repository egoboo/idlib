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
#error(do not include directly, include `idlib/parsing_expressions/include.hpp` instead)
#endif

#include "idlib/parsing_expressions/sym.hpp"
#include "idlib/parsing_expressions/sym_range.hpp"
#include "idlib/parsing_expressions/ordered_choice.hpp"
#include "idlib/parsing_expressions/sequence.hpp"
#include "idlib/parsing_expressions/repetition.hpp"

#include "idlib/parsing_expressions/header.in"

/// @brief Parsing expression accepting @code{whitespace = ' '|'\t'}.
/// @tparam Sym the symbol type
template <typename Sym>
class whitespace
{
public:
    template <typename It>
    match<std::decay_t<It>> operator()(It at, It end) const
    {
        static const auto x = ordered_choice(sym<Sym>(' '), sym<Sym>('\t'));
        return x(at, end);
    }
};

/// @brief Parsing expression accepting @code{newline = '\n'|'\r'}.
/// @tparam Sym the symbol type
template <typename Sym>
class newline
{
public:
    template <typename It>
    match<std::decay_t<It>> operator()(It at, It end) const
    {
        static const auto x = ordered_choice(sym<Sym>('\n'), sym<Sym>('\r'));
        return x(at, end);
    }
};

/// @brief Parsing expression accepting @code{alpha_lowercase = 'a' .. 'z'}.
/// @tparam Sym the symbol type
template <typename Sym>
class alpha_lowercase
{
public:
    template <typename It>
    match<std::decay_t<It>> operator()(It at, It end) const
    {
        static const auto x = sym_range<Sym>('a', 'z');
        return x(at, end);
    }
};

/// @brief Parsing expression accepting @code{alpha_uppercase = 'A' .. 'Z'}.
/// @tparam Sym the symbol type
template <typename Sym>
class alpha_uppercase
{
public:
    template <typename It>
    match<std::decay_t<It>> operator()(It at, It end) const
    {
        static const auto x = sym_range<Sym>('A', 'Z');
        return x(at, end);
    }
};

/// @brief Parsing expression accepting @code{alpha = alpha_lowercase|alpha_uppercase}.
/// @tparam Sym the symbol type
template <typename Sym>
class alpha
{
public:
    template <typename It>
    match<std::decay_t<It>> operator()(It at, It end) const
    {
        static const auto x = ordered_choice(alpha_lowercase<Sym>(), alpha_uppercase<Sym>());
        return x(at, end);
    }
};

/// @brief Parsing expression accepting @code{digit = '0' .. '9'}.
/// @tparam Sym the symbol type
template <typename Sym>
class digit
{
public:
    template <typename It>
    match<std::decay_t<It>> operator()(It at, It end) const
    {
        static const auto x = sym_range<Sym>('0', '9');
        return x(at, end);
    }
};

/// @brief Parsing expression accepting @code{name = ('_'|alpha)('_'|alpha|digit)*}.
/// @tparam Sym the symbol type
template <typename Sym>
class name
{
public:
    template <typename It>
    match<std::decay_t<It>> operator()(It at, It end) const
    {
        static const auto w =
            sequence
            (
                ordered_choice
                (
                    alpha<char>(),
                    sym<char>('_')
                ),
                repetition
                (
                    ordered_choice
                    (
                        alpha<char>(),
                        digit<char>(),
                        sym<char>('_')
                    )
                )
            );
        return w(at, end);
    }
};

/// @brief Parsing expression accepting @code{qualified_name = name ('.' name)*}.
/// @tparam Sym the symbol type
template <typename Sym>
class qualified_name
{
public:
    template <typename It>
    match<std::decay_t<It>> operator()(It at, It end) const
    {
        static const auto w =
            sequence
            (
                name<char>(),
                repetition
                (
                    sequence
                    (
                        sym<char>('.'),
                        name<char>()
                    )
                )
            );
        return w(at, end);
    }
};

#include "idlib/parsing_expressions/footer.in"
