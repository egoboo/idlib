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

/// @file idlib/math/operators.hpp
/// @brief functors representing language operators
/// @author Michael Heilmann

#pragma once

#include <utility>

namespace id {

/// @ingroup math
/// @brief Unary minus functor.
/// Deduces the argument and return types.
/// @code
/// id::unary_minus()(x)
/// @endcode
/// is equivalent to
/// @code
/// -x
/// @endcode
struct unary_minus
{
	template<class X>
	constexpr auto operator()(X&& x) const
		-> decltype(-std::forward<X>(x))
	{ return -std::forward<X>(x); }
};

/// @ingroup math
/// @brief Unary plus functor.
/// Deduces the argument and return types.
/// @code
/// id::unary_pluss()(x)
/// @endcode
/// is equivalent to
/// @code
/// +x
/// @endcode
struct unary_plus
{
	template <typename X>
	constexpr auto operator()(X&& x) const
		-> decltype(+std::forward<X>(x))
	{ return +std::forward<X>(x); }
};

/// @ingroup math
/// @brief Binary plus functor.
/// Deduces the argument and return types.
/// @code
/// id::binary_plus()(x, y)
/// @endcode
/// is equivalent to
/// @code
/// x + y
/// @endcode
struct binary_plus
{
	template <typename X, typename Y>
	constexpr auto operator()(X&& x, Y&& y) const
		-> decltype(std::forward<X>(x) + std::forward<Y>(y))
	{ return std::forward<X>(x) + std::forward<Y>(y); }
};

/// @ingroup math
/// @brief Binary minus functor.
/// Deduces the argument and return types.
/// @code
/// id::binary_minus()(x, y)
/// @endcode
/// is equivalent to
/// @code
/// x - y
/// @endcode
struct binary_minus
{
	template <typename X, typename Y>
	constexpr auto operator()(X&& x, Y&& y) const
		-> decltype(std::forward<X>(x) - std::forward<Y>(y))
	{ return std::forward<X>(x) - std::forward<Y>(y); }
};

/// @ingroup math
/// @brief Binary star functor.
/// Deduces the argument and return types.
/// @code
/// id::binary_star()(x, y)
/// @endcode
/// is equivalent to
/// @code
/// x * y
/// @endcode
struct binary_star
{
	template <typename X, typename Y>
	constexpr auto operator()(X&& x, Y&& y) const
		-> decltype(std::forward<X>(x) * std::forward<Y>(y))
	{ return std::forward<X>(x) * std::forward<Y>(y); }
};

/// @ingroup math
/// @brief Binary slash functor.
/// Deduces the argument and return types.
/// @code
/// id::binary_slash()(x, y)
/// @endcode
/// is equivalent to
/// @code
/// x / y
/// @endcode
struct binary_slash
{
	template <typename X, typename Y>
	constexpr auto operator()(X&& x, Y&& y) const
		-> decltype(std::forward<X>(x) / std::forward<Y>(y))
	{ return std::forward<X>(x) / std::forward<Y>(y); }
};

/// @ingroup math
/// @brief Binary equal equal functor.
/// Deduces the argument and return types.
/// @code
/// id::binary_equal_equal()(x, y)
/// @endcode
/// is equivalent to
/// @code
/// x == y
/// @endcode
struct binary_equal_equal
{
	template <typename X, typename Y>
	constexpr auto operator()(X&& x, Y&& y) const
		-> decltype(std::forward<X>(x) == std::forward<Y>(y))
	{ return std::forward<X>(x) == std::forward<Y>(y); }
};

} // namespace id
