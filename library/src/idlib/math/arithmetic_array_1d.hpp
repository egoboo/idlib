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

#include "idlib/utility/fold_expressions.hpp"
#include "idlib/math/arithmetic_functor.hpp"
#include "idlib/math/operators.hpp"
#include "idlib/math/one_zero.hpp"
#include "idlib/bool_pack.hpp"
#include <algorithm>

namespace idlib {

/// @brief Provide member constant value <tt>value</tt>.
/// That constant is equal to <tt>true</tt> if the argument types in the variadic template argument list are convertible into the specified target type.
/// Otherwise it is equal to <tt>false</tt>.
template <typename TargetType, typename ... ArgumentTypes>
using all_convertible = all_true<std::is_convertible<ArgumentTypes, TargetType>::value ...>;

/// @brief An arithmetic one-dimensional array of length N and element type E consists
/// of N values of type E which can be addressed by indices 0, ..., N -1. Arithmetic
/// arrays allow for performing standard arithmetic operations.
/// Let @a a and @a b be arrays of the same length and of element type @a E.
/// Let @a e be a value of type @a E.
/// The for all one- and two dimensional arrays, the following operations are defined:
/// - <c>a + b</c> (binary plus)
/// - <c>a - b</c> (binary minus)
/// - <c>+a</c> (unary plus)
/// - <c>-a</c> (unary minus)
/// - <c>a * e</c> (array element binary star)
/// - <c>a / e</c> (array element binary slash)
/// @tparam Element the element type
/// @tparam Length the length of the array
/// A partial specialization for empty arrays is provided.
/// @tparam Zero the zero functor type.
/// type of a functor type returning the zero element value
template <typename Element,
          size_t Length,
          typename Zero>
struct arithmetic_array_1d
{
	/// @brief The element type.
	using element_type = Element;

    /// @brief The zero functor type.
    using zero_type = Zero;

    /// @brief Get the length of this array.
    /// @return the length of this array
    constexpr static size_t length() noexcept
    { return Length; }

	/// @brief Get the number of elements.
	/// @return the number of elements
	constexpr static size_t number_of_elements() noexcept
	{ return length(); }

	/// @brief Default construct with the zero element value.
	arithmetic_array_1d()
	{ std::fill_n(&(m_elements[0]), number_of_elements(), zero_type()()); }
	
	/// @brief Construct this tuple with the specified element values.
	/// @param first, ... rest the element values
    /// @pre The number of specified element values must be equal to the size of the tuple type.
	template<typename X, typename ... Xs,
             typename = std::enable_if_t<((1 + sizeof...(Xs)) == number_of_elements()) &&
									      (all_true<std::is_convertible<typename std::decay<X>::type, element_type>::value>::value &&
                                           all_true<std::is_convertible<typename std::decay<Xs>::type, element_type>::value ...>::value)>>
	arithmetic_array_1d(X&& x, Xs&& ... xs) :
        m_elements{ static_cast<element_type>(x), static_cast<element_type>(xs) ... }
    { static_assert(number_of_elements() == 1 + sizeof ... (xs), "wrong number of arguments"); }

	arithmetic_array_1d(const arithmetic_array_1d& other) = default;
	
	arithmetic_array_1d(arithmetic_array_1d&& other) = default;
	
	arithmetic_array_1d& operator=(const arithmetic_array_1d& other) = default;
	
	arithmetic_array_1d& operator=(arithmetic_array_1d&& other) = default;

	arithmetic_array_1d& operator += (const arithmetic_array_1d& other)
	{ (*this) = (*this) + other; return *this; }

	arithmetic_array_1d& operator -= (const arithmetic_array_1d& other)
	{ (*this) = (*this) - other; return *this; }

	arithmetic_array_1d& operator *= (const element_type& other)
	{ (*this) = (*this) * other; return *this; }

	arithmetic_array_1d& operator /= (const element_type& other)
	{ (*this) = (*this) / other; return *this; }

	/// @{
	/// @brief Get the array element at the specified index.
	/// @param i the index
	/// @return the array element at the specified index
	/// @pre The index is within bounds.
	element_type& at(size_t i)
	{ return m_elements[i]; }

	element_type& operator()(size_t i)
	{ return m_elements[i]; }

	const element_type& at(size_t i) const
	{ return m_elements[i]; }

	const element_type& operator()(size_t i) const
	{ return m_elements[i]; }
	/// @}

	template <typename G>
	static arithmetic_array_1d generate(const G& g)
	{ return generate(g, std::make_index_sequence<number_of_elements()>{}); }
	
private:
	template <typename G, size_t...Is>
	static arithmetic_array_1d generate(const G& g, std::index_sequence<Is...>)
	{ return arithmetic_array_1d((g(Is))...); }

	/// @brief The elements.
	element_type m_elements[number_of_elements()];
	
}; // struct arithmetic_array_1d

template <typename Element, size_t Length, typename Zero>
struct arithmetic_binary_star_functor<arithmetic_array_1d<Element, Length, Zero>,
                                      Element>
{
    using B = Element;
    using A = arithmetic_array_1d<Element, Length, Zero>;

    auto operator()(const A& a, const B& b) const
    { return impl(a, b, std::make_index_sequence<Length>{}); }

private:
   template <size_t ... Is>
    auto impl(const A& a, const B& b, std::index_sequence<Is...>) const
    { return A((a(Is) * b)...); }
};

template <typename Element, size_t Length, typename Zero>
struct arithmetic_binary_slash_functor<arithmetic_array_1d<Element, Length, Zero>,
                                       Element>
{
    using B = Element;
    using A = arithmetic_array_1d<Element, Length, Zero>;

    auto operator()(const A& a, const B& b) const
    { return impl(a, b, std::make_index_sequence<Length>{}); }
	
private:
    template <size_t ... Is>
    auto impl(const A& a, const B& b, std::index_sequence<Is...>) const
    { return A((a(Is) / b)...); }
};

template <typename Element, size_t Length, typename Zero>
struct arithmetic_binary_plus_functor<arithmetic_array_1d<Element, Length, Zero>>
{
    using T = arithmetic_array_1d<Element, Length, Zero>;

    auto operator()(const T& a, const T& b) const
    { return impl(a, b, std::make_index_sequence<Length>{}); }
	
private:
    template <size_t ... Is>
    auto impl(const T& a, const T& b, std::index_sequence<Is...>) const
    { return T((a(Is) + b(Is))...); }
};

template <typename Element, size_t Length, typename Zero>
struct arithmetic_binary_minus_functor<arithmetic_array_1d<Element, Length, Zero>>
{
    using T = arithmetic_array_1d<Element, Length, Zero>;

    auto operator()(const T& a, const T& b) const
    { return impl(a, b, std::make_index_sequence<Length>{}); }
	
private:
    template <size_t ... Is>
    auto impl(const T& a, const T& b, std::index_sequence<Is...>) const
    { return T((a(Is) - b(Is))...); }
};

template <typename Element, size_t Length, typename Zero>
struct arithmetic_unary_plus_functor<arithmetic_array_1d<Element, Length, Zero>>
{
    using T = arithmetic_array_1d<Element, Length, Zero>;

    auto operator()(const T& a) const
    { return impl(a, std::make_index_sequence<Length>{}); }
	
private:
    template <size_t ... Is>
    auto impl(const T& a, std::index_sequence<Is...>) const
    { return T((+(a(Is)))...); }
};

template <typename Element, size_t Length, typename Zero>
struct arithmetic_unary_minus_functor<arithmetic_array_1d<Element, Length, Zero>>
{
    using T = arithmetic_array_1d<Element, Length, Zero>;

    auto operator()(const T& a) const
    { return impl(a, std::make_index_sequence<Length>{}); }
	
private:
    template <size_t ... Is>
    auto impl(const T& a, std::index_sequence<Is...>) const
    { return T((-(a(Is)))...); }
};

/// @todo When all compilers support it, use real fold expressions.
template <typename Element, size_t Length, typename Zero>
struct arithmetic_binary_equal_equal_functor<arithmetic_array_1d<Element, Length, Zero>,
                                             arithmetic_array_1d<Element, Length, Zero>>
{
	using T = arithmetic_array_1d<Element, Length, Zero>;
	
	bool operator()(const T& a, const T& b) const
	{ return impl(a, b, std::make_index_sequence<Length>{}); }
	
private:
	template <size_t...Is>
	static bool impl(const T& a, const T& b, std::index_sequence<Is...>)
	{ return and_fold_expr()((a(Is) == b(Is))...); }
};

/// @internal
/// @brief Partial specialization of idlib::arithmetic_array_1d for empty arrays.
template <typename Element, typename Zero>
struct arithmetic_array_1d<Element, 0, Zero>
{
	/// @brief The element type.
	using element_type = Element;

    /// @brief The zero functor type.
    using zero_type = Zero;

    /// @brief Get the length of this array.
    /// @return the length of this array
    constexpr static size_t length() noexcept
    { return 0; }

    /// @brief Get the number of elements.
    /// @return the number of elements
    constexpr static size_t number_of_elements() noexcept
    { return length(); }

	/// @brief Default construct this arithmetic tuple.
	arithmetic_array_1d()
	{}

	arithmetic_array_1d(const arithmetic_array_1d& other) = default;
	
    arithmetic_array_1d(arithmetic_array_1d&& other) = default;
	
    arithmetic_array_1d& operator=(const arithmetic_array_1d& other) = default;
	
    arithmetic_array_1d& operator=(arithmetic_array_1d&& other) = default;

	arithmetic_array_1d& operator += (const arithmetic_array_1d& other)
	{ return *this; }

	arithmetic_array_1d& operator -= (const arithmetic_array_1d& other)
	{ return *this; }

	arithmetic_array_1d& operator *= (const element_type& other)
	{ return *this; }
	
	arithmetic_array_1d& operator /= (const element_type& other)
	{ return *this; }

	template <typename G>
	static arithmetic_array_1d generate(const G& g)
	{ return arithmetic_array_1d(); }
	
}; // struct arithmetic_array_1d

template <typename Element, typename Zero>
struct arithmetic_binary_star_functor<arithmetic_array_1d<Element, 0, Zero>,
                                      Element>
{
    using B = Element;
    using A = arithmetic_array_1d<Element, 0, Zero>;

    auto operator()(const A& a, const B& b) const
    { return A(); }
};

template <typename Element, typename Zero>
struct arithmetic_binary_slash_functor<arithmetic_array_1d<Element, 0, Zero>,
                                       Element>
{
    using B = Element;
    using A = arithmetic_array_1d<Element, 0, Zero>;

    auto operator()(const A& a, const B& b) const
    { return A(); }
};

template <typename Element, typename Zero>
struct arithmetic_binary_plus_functor<arithmetic_array_1d<Element, 0, Zero>>
{
    using T = arithmetic_array_1d<Element, 0, Zero>;

    auto operator()(const T& a, const T& b) const
    { return T(); }
};

template <typename Element, typename Zero>
struct arithmetic_binary_minus_functor<arithmetic_array_1d<Element, 0, Zero>>
{
    using T = arithmetic_array_1d<Element, 0, Zero>;

    auto operator()(const T& a, const T& b) const
    { return T(); }
};

template <typename Element, typename Zero>
struct arithmetic_unary_plus_functor<arithmetic_array_1d<Element, 0, Zero>>
{
    using T = arithmetic_array_1d<Element, 0, Zero>;

    auto operator()(const T& a) const
    { return T(); }
};

template <typename Element, typename Zero>
struct arithmetic_unary_minus_functor<arithmetic_array_1d<Element, 0, Zero>>
{
    using T = arithmetic_array_1d<Element, 0, Zero>;

    auto operator()(const T& a) const
    { return T(); }
};

template <typename Element, typename Zero>
struct arithmetic_binary_equal_equal_functor<arithmetic_array_1d<Element, 0, Zero>,
                                             arithmetic_array_1d<Element, 0, Zero>>
{
	using T = arithmetic_array_1d<Element, 0, Zero>;
	
	bool operator()(const T& a, const T& b) const
	{ return true; }
};

} // namespace idlib
