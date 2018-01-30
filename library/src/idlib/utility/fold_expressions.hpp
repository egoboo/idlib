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

namespace idlib {

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

} // namespace idlib
