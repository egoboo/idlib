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

#include "idlib/math/arithmetic_array_2d_common.hpp"
#include "idlib/utility/fold_expressions.hpp"
#include "idlib/math/arithmetic_functor.hpp"
#include "idlib/math/one_zero.hpp"
#include "idlib/math/random.hpp"
#include "idlib/bool_pack.hpp"
#include <algorithm>

namespace idlib {

/// @brief Partial specialization of idlib::math::arithmetic_array_2d for non-empty arithmetic arrays.
/// @tparam Element the element type
/// @tparam Width the width of the array
/// @tparam Height the height of the array
/// @tparam Zero type of a functor type returning the zero element value
template <typename Element, size_t Width, size_t Height, typename Zero>
struct arithmetic_array_2d<Element, Width, Height, Zero,
                           std::enable_if_t<(Width > 0) && (Height > 0)>>
{
	/// @brief The element type.
	using element_type = Element;
	
	/// @brief The zero functor type.
	using zero_type = Zero;

	/// @brief Get the width.
	/// @return the width
	constexpr static size_t width() noexcept
	{ return Width; }
	
	/// @brief Get the height.
	/// @return the height
	constexpr static size_t height() noexcept
	{ return Height; }
	
	/// @brief Get the number of elements.
	/// @return the number of elements
	constexpr static size_t number_of_elements() noexcept
	{ return width() * height(); }
	
	/// @brief Default construct with the zero element value.
	arithmetic_array_2d()
	{ std::fill_n(&(m_elements_1d[0]), number_of_elements(), zero_type()()); }
	
	/// @brief Construct this tuple with the specified element values.
	/// @param first, ... rest the element values
    /// @pre The number of specified element values must be equal to the size of the tuple type.
	template<typename X, typename ... Xs,
             typename =  std::enable_if_t<((1 + sizeof...(Xs)) == number_of_elements()) &&
										   (std::is_convertible<typename std::decay<X>::type, element_type>::value &&
                                            all_true<std::is_convertible<typename std::decay<Xs>::type, element_type>::value ...>::value)>>
	arithmetic_array_2d(X&& x, Xs&& ... xs) :
        m_elements_1d{ static_cast<element_type>(x), static_cast<element_type>(xs) ... }
    { static_assert(number_of_elements() == 1 + sizeof ... (xs), "wrong number of arguments"); }
	
	arithmetic_array_2d(const arithmetic_array_2d& other) = default;
	
	arithmetic_array_2d(arithmetic_array_2d&& other) = default;
	
	arithmetic_array_2d& operator=(const arithmetic_array_2d& other) = default;
	
	arithmetic_array_2d& operator=(arithmetic_array_2d&& other) = default;
	
	arithmetic_array_2d& operator += (const arithmetic_array_2d& other)
	{ (*this) = (*this) + other; return *this; }

	arithmetic_array_2d& operator -= (const arithmetic_array_2d& other)
	{ (*this) = (*this) - other; return *this; }

	arithmetic_array_2d& operator *= (const element_type& other)
	{ (*this) = (*this) * other; return *this; }

	arithmetic_array_2d& operator /= (const element_type& other)
	{ (*this) = (*this) / other; return *this; }

	/// @{
	/// @brief Get the array element at the specified one-dimensional index.
	/// @param i the one-dimensional index
	/// @return the array element at the specified one-dimensional index
	/// @pre The index is within bounds.
	element_type& at(size_t i)
	{ return m_elements_1d[i]; }

	element_type& operator()(size_t i)
	{ return m_elements_1d[i]; }

	const element_type& at(size_t i) const
	{ return m_elements_1d[i]; }

	const element_type& operator()(size_t i) const
	{ return m_elements_1d[i]; }
	/// @}
	
	/// @{
	/// @brief Get the array element at the two-dimensional index.
	/// @param i, j the two-dimensional index
	/// @param
	/// @return the array element at the specified two-dimensional index
	/// @pre The index is within bounds.
	element_type& at(size_t i, size_t j)
	{ return m_elements_1d[i]; }

	element_type& operator()(size_t i, size_t j)
	{ return m_elements_1d[i]; }

	const element_type& at(size_t i, size_t j) const
	{ return m_elements_2d[i][j]; }

	const element_type& operator()(size_t i, size_t j) const
	{ return m_elements_2d[i][j]; }
	/// @}
	
private:
    union
	{
        element_type m_elements_1d[number_of_elements()];
        element_type m_elements_2d[width()][height()];
    }; // union

}; // struct arithmetic_array_2d

template <typename Element, size_t Width, size_t Height, typename Zero>
struct arithmetic_binary_star_functor<arithmetic_array_2d<Element, Width, Height, Zero>,
                                      Element,
									  std::enable_if_t<(Width > 0) && (Height > 0)>>
{
    using B = Element;
    using A = arithmetic_array_2d<Element, Width, Height, Zero>;

    auto operator()(const A& a, const B& b) const
    { return impl(a, b, std::make_index_sequence<Width * Height>{}); }

private:
   template <size_t ... Is>
    auto impl(const A& a, const B& b, std::index_sequence<Is...>) const
    { return A((a(Is) * b)...); }
};

template <typename Element, size_t Width, size_t Height, typename Zero>
struct arithmetic_binary_slash_functor<arithmetic_array_2d<Element, Width, Height, Zero>,
                                       Element,
									   std::enable_if_t<(Width > 0) && (Height > 0)>>
{
    using B = Element;
    using A = arithmetic_array_2d<Element, Width, Height, Zero>;

    auto operator()(const A& a, const B& b) const
    { return impl(a, b, std::make_index_sequence<Width * Height>{}); }
	
private:
    template <size_t ... Is>
    auto impl(const A& a, const B& b, std::index_sequence<Is...>) const
    { return A((a(Is) / b)...); }
};

template <typename Element, size_t Width, size_t Height, typename Zero>
struct arithmetic_binary_plus_functor<arithmetic_array_2d<Element, Width, Height, Zero>,
                                      arithmetic_array_2d<Element, Width, Height, Zero>,
                                      std::enable_if_t<(Width > 0) && (Height > 0)>>
{
    using T = arithmetic_array_2d<Element, Width, Height, Zero>;

    auto operator()(const T& a, const T& b) const
    { return impl(a, b, std::make_index_sequence<Width * Height>{}); }
	
private:
    template <size_t ... Is>
    auto impl(const T& a, const T& b, std::index_sequence<Is...>) const
    { return T((a(Is) + b(Is))...); }
};

template <typename Element, size_t Width, size_t Height, typename Zero>
struct arithmetic_binary_minus_functor<arithmetic_array_2d<Element, Width, Height, Zero>,
                                       arithmetic_array_2d<Element, Width, Height, Zero>,
                                       std::enable_if_t<(Width > 0) && (Height > 0)>>
{
    using T = arithmetic_array_2d<Element, Width, Height, Zero>;

    auto operator()(const T& a, const T& b) const
    { return impl(a, b, std::make_index_sequence<Width * Height>{}); }
	
private:
    template <size_t ... Is>
    auto impl(const T& a, const T& b, std::index_sequence<Is...>) const
    { return T((a(Is) - b(Is))...); }
};

template <typename Element, size_t Width, size_t Height, typename Zero>
struct arithmetic_unary_plus_functor<arithmetic_array_2d<Element, Width, Height, Zero>,
                                     std::enable_if_t<(Width > 0) && (Height > 0)>>
{
    using T = arithmetic_array_2d<Element, Width, Height, Zero>;

    auto operator()(const T& a) const
    { return impl(a, std::make_index_sequence<Width * Height>{}); }
	
private:
    template <size_t ... Is>
    auto impl(const T& a, std::index_sequence<Is...>) const
    { return T((+(a(Is)))...); }
};

template <typename Element, size_t Width, size_t Height, typename Zero>
struct arithmetic_unary_minus_functor<arithmetic_array_2d<Element, Width, Height, Zero>,
                                      std::enable_if_t<(Width > 0) && (Height > 0)>>
{
    using T = arithmetic_array_2d<Element, Width, Height, Zero>;

    auto operator()(const T& a) const
    { return impl(a, std::make_index_sequence<Width * Height>{}); }
	
private:
    template <size_t ... Is>
    auto impl(const T& a, std::index_sequence<Is...>) const
    { return T((-(a(Is)))...); }
};

/// @todo When all compilers support it, use real fold expressions.
template <typename Element, size_t Width, size_t Height, typename Zero>
struct arithmetic_binary_equal_equal_functor<arithmetic_array_2d<Element, Width, Height, Zero>,
                                             arithmetic_array_2d<Element, Width, Height, Zero>,
											 std::enable_if_t<(Width > 0) && (Height > 0)>>
{
	using T = arithmetic_array_2d<Element, Width, Height, Zero>;
	
	bool operator()(const T& a, const T& b) const
	{ return impl(a, b, std::make_index_sequence<Width * Height>{}); }
	
private:
	template <size_t...Is>
	static bool impl(const T& a, const T& b, std::index_sequence<Is...>)
	{ return and_fold_expr()((a(Is) == b(Is))...); }
};

/// @internal
template <typename Element, size_t Width, size_t Height, typename Zero>
struct random_functor<arithmetic_array_2d<Element, Width, Height, Zero>,
                      std::enable_if_t<(Width > 0) && (Height > 0)>>
{
    using element_type = Element;

    using array_type = arithmetic_array_2d<Element, Width, Height, Zero>;

    static const interval<element_type> DEFAULT_INTERVAL;
  
	array_type operator()() const
    {
		rng rng;
        return (*this)(&rng, DEFAULT_INTERVAL);
    }
	
	array_type operator()(rng *rng) const
	{ return (*this)(rng, DEFAULT_INTERVAL); }

    array_type operator()(const interval<element_type>& interval) const
    { 
		rng rng;
		return (*this)(&rng, interval);
	}
	
    array_type operator()(rng *rng, const interval<element_type>& interval) const
    {
        return impl(rng, interval, std::make_index_sequence<Width * Height>{});
    }

private:
	template<std::size_t...Is>
	array_type impl(rng *rng, const interval<element_type>& interval, std::index_sequence<Is ...>) const
	{ return array_type(impl(rng, interval, Is) ...); }
	
	element_type impl(rng *rng, const interval<element_type>& interval, size_t i) const
	{ return rng->next(interval); }
}; // struct random_functor

template <typename Element, size_t Width, size_t Height, typename Zero>
const interval<Element> random_functor<arithmetic_array_2d<Element, Width, Height, Zero>,std::enable_if_t<(Width > 0) && (Height > 0)>>::DEFAULT_INTERVAL(zero<Element>(), one<Element>());

} // namespace idlib
