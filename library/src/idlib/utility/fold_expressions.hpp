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

/// @file idlib/utility/fold_expressions.hpp
/// @brief Replacement for C++ fold expressions for compilers that do not support them yet. That is, all compilers.
/// @detail Replacements for the most important &&, ||, +, and - fold expressions are provided.
/// @author Michael Heilmann
/// @remark
/// A functor
/// @code
/// struct op_fold_expr
/// {
///   private:
///	    template <class T>
///	    constexpr auto impl(T&& x) const
///     { return x; }
///     template <class First, class... Rest>
///     constexpr auto impl(T&& x, Ts&& ... xs) const
///     { return x op impl(std::forward<Ts>(xs) ...); }
///   public:
///     template <class... Ts>
///     constexpr auto operator()(Ts&&... xs) const
///     { return impl(std::forward<Ts>(xs) ...); }
/// };
/// @endcode
/// could be rewritten using fold expressions
/// @code
/// struct op_fold_expr
/// {
///   public:
///     template <class... Ts>
///     constexpr auto operator()(Ts&&... xs) const
///     { return (op ... xs); }
/// };
/// @endcode
/// Obviously fold expressions make these functors redundant.

#pragma once

#include <utility>

namespace id {

/// Functor for and'ing together all arguments (without fold expressions).
/// We could use
/// @code
/// template <class... Ts>
/// constexpr auto operator()(Ts&&... xs) const
/// { return (xs && ...); }
/// @endcode
struct and_fold_expr
{
private:
	template <class T>
	constexpr auto impl(T&& x) const
	{ return x; }

	template <class T, class... Ts>
	constexpr auto impl(T&& x, Ts&& ... xs) const
	{ return x && impl(std::forward<Ts>(xs) ...); }

public:
	template <class... Ts>
	constexpr auto operator()(Ts&&... xs) const
	{ return impl(std::forward<Ts>(xs) ...); }
};

/// Functor for or'ing together all arguments (without fold expressions).
/// We could use
/// @code
/// template <class... Ts>
/// constexpr auto operator()(Ts&&... xs) const
/// { return (xs || ...); }
/// @endcode
struct or_fold_expr
{
private:
	template <class T>
	constexpr auto impl(T&& x) const
	{ return x; }

	template <class T, class... Ts>
	constexpr auto impl(T&& x, Ts&& ... xs) const
	{ return x || impl(std::forward<Ts>(xs) ...); }

public:
	template <class... Ts>
	constexpr auto operator()(Ts&&... xs) const
	{ return impl(std::forward<Ts>(xs) ...); }
};

/// Functor for or'ing together all arguments (without fold expressions).
/// We could use
/// @code
/// template <class... Ts>
/// constexpr auto operator()(Ts&&... xs) const
/// { return (xs + ...); }
/// @endcode
struct plus_fold_expr
{
private:
	template <class T>
	constexpr auto impl(T&& x) const
	{ return x; }

	template <class T, class... Ts>
	constexpr auto impl(T&& x, Ts&& ... xs) const
	{ return x + impl(std::forward<Ts>(xs) ...); }

public:
	template <class... Ts>
	constexpr auto operator()(Ts&&... xs) const
	{ return impl(std::forward<Ts>(xs) ...); }
};

/// Functor for or'ing together all arguments (without fold expressions).
/// We could use
/// @code
/// template <class... Ts>
/// constexpr auto operator()(Ts&&... xs) const
/// { return (xs + ...); }
/// @endcode
struct minus_fold_expr
{
private:
	template <class T>
	constexpr auto impl(T&& x) const
	{ return x; }

	template <class T, class... Ts>
	constexpr auto impl(T&& x, Ts&& ... xs) const
	{ return x - impl(xs ...); }

public:
	template <class... Ts>
	constexpr auto operator()(Ts&&... xs) const
	{ return impl(std::forward<Ts>(xs) ...); }
};

} // namespace id
