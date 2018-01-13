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
