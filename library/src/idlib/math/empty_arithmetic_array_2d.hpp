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
#include "idlib/math/arithmetic_functor.hpp"

namespace idlib {

/// @brief Partial specialization of idlib::arithmetic_array_2d for empty arithmetic arrays.
/// @tparam Element the element type
/// @tparam Width the width of the array
/// @tparam Height the height of the array
/// @tparam Zero type of a functor type returning the zero element value
template <typename Element, size_t Width, size_t Height, typename Zero>
struct arithmetic_array_2d<Element, Width, Height, Zero,
                           std::enable_if_t<(Width == 0) || (Height == 0)>>
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
	{}
		
	arithmetic_array_2d(const arithmetic_array_2d& other) = default;
	
	arithmetic_array_2d(arithmetic_array_2d&& other) = default;
	
	arithmetic_array_2d& operator=(const arithmetic_array_2d& other) = default;
	
	arithmetic_array_2d& operator=(arithmetic_array_2d&& other) = default;
	
	arithmetic_array_2d& operator += (const arithmetic_array_2d& other)
	{ return *this; }

	arithmetic_array_2d& operator -= (const arithmetic_array_2d& other)
	{ return *this; }

	arithmetic_array_2d& operator *= (const element_type& other)
	{ return *this; }

	arithmetic_array_2d& operator /= (const element_type& other)
	{ return *this; }

}; // struct arithmetic_array_2d

template <typename Element, size_t Width, size_t Height, typename Zero>
struct arithmetic_binary_star_functor<arithmetic_array_2d<Element, Width, Height, Zero>,
                                      Element,
									  std::enable_if_t<(Width == 0) || (Height == 0)>>
{
    using B = Element;
    using A = arithmetic_array_2d<Element, Width, Height, Zero>;

    auto operator()(const A& a, const B& b) const
    { return A(); }
};

template <typename Element, size_t Width, size_t Height, typename Zero>
struct arithmetic_binary_slash_functor<arithmetic_array_2d<Element, Width, Height, Zero>,
                                       Element,
									   std::enable_if_t<(Width == 0) || (Height == 0)>>
{
    using B = Element;
    using A = arithmetic_array_2d<Element, Width, Height, Zero>;

    auto operator()(const A& a, const B& b) const
    { return A(); }
};

template <typename Element, size_t Width, size_t Height, typename Zero>
struct arithmetic_binary_plus_functor<arithmetic_array_2d<Element, Width, Height, Zero>,
                                      arithmetic_array_2d<Element, Width, Height, Zero>,
                                      std::enable_if_t<(Width == 0) || (Height == 0)>>
{
    using T = arithmetic_array_2d<Element, Width, Height, Zero>;

    auto operator()(const T& a, const T& b) const
    { return T(); }
};

template <typename Element, size_t Width, size_t Height, typename Zero>
struct arithmetic_binary_minus_functor<arithmetic_array_2d<Element, Width, Height, Zero>,
                                       arithmetic_array_2d<Element, Width, Height, Zero>,
                                       std::enable_if_t<(Width == 0) || (Height == 0)>>
{
    using T = arithmetic_array_2d<Element, Width, Height, Zero>;

    auto operator()(const T& a, const T& b) const
    { return T(); }
};

template <typename Element, size_t Width, size_t Height, typename Zero>
struct arithmetic_unary_plus_functor<arithmetic_array_2d<Element, Width, Height, Zero>,
                                     std::enable_if_t<(Width == 0) || (Height == 0)>>
{
    using T = arithmetic_array_2d<Element, Width, Height, Zero>;

    auto operator()(const T& a) const
    { return T(); }
};

template <typename Element, size_t Width, size_t Height, typename Zero>
struct arithmetic_unary_minus_functor<arithmetic_array_2d<Element, Width, Height, Zero>,
                                      std::enable_if_t<(Width == 0) || (Height == 0)>>
{
    using T = arithmetic_array_2d<Element, Width, Height, Zero>;

    auto operator()(const T& a) const
    { return T(); }
};

/// @todo When all compilers support it, use real fold expressions.
template <typename Element, size_t Width, size_t Height, typename Zero>
struct arithmetic_binary_equal_equal_functor<arithmetic_array_2d<Element, Width, Height, Zero>,
                                             arithmetic_array_2d<Element, Width, Height, Zero>,
											 std::enable_if_t<(Width == 0) || (Height == 0)>>
{
	using T = arithmetic_array_2d<Element, Width, Height, Zero>;
	
	bool operator()(const T& a, const T& b) const
	{ return true; }
};

} // namespace idlib
