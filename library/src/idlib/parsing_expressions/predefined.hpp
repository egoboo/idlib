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
