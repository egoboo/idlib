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

/// @file idlib/math/arithmetic_functor.hpp
/// @brief Arithmetic functor templates.
/// @detail Arithmetic functors allow for partial specialization and SFINAE for free operators.
/// The supported operators are unary minus, unary plus, binary plus, binary minus, binary star, and binary slash.
/// The following program demonstrates how to use the arithmetic functors to provide a binary plus operator for some vector class.
/// Example
/// @code
/// class my_vector
/// {
/// public:
///		float x;
///     float y;
///     my_vector(float x, float y) : x(x), y(y)
///     { }
///     ...
/// };
///
/// template<>
/// arithmetic_binary_plus_functor<my, my, void>
/// {
///    auto operator()(const my_vector& u, const my_vector& v) const
///    { return my_vector(a.x + b.x, a.y + b.y); 
/// }
///
/// void my_test()
/// {
///    auto r = my_vector(1,2) + my_vector(2,3);
///    ...
/// }
/// @endcode
/// @author Michael Heilmann

#pragma once

#include "idlib/platform.hpp"
#include <utility>

namespace idlib {

template <typename A, typename B = A, typename E = void>
struct arithmetic_binary_star_functor;

// Specialization for floating-point types.
template <typename T>
struct arithmetic_binary_star_functor<T, T, std::enable_if_t<std::is_floating_point<T>::value>>
{
    T operator()(T a, T b) const
    { return a * b; }
};

template <typename A, typename B = A, typename E = void>
struct arithmetic_binary_slash_functor;

// Specialization for floating-point types.
template <typename T>
struct arithmetic_binary_slash_functor<T, T, std::enable_if_t<std::is_floating_point<T>::value>>
{
    T operator()(T a, T b) const
    { return a / b; }
};

template <typename A, typename B = A, typename E = void>
struct arithmetic_binary_plus_functor;

// Specialization for floating-point types.
template <typename T>
struct arithmetic_binary_plus_functor<T, T, std::enable_if_t<std::is_floating_point<T>::value>>
{
    T operator()(T a, T b) const
    { return a + b; }
};
	
template <typename A, typename B = A, typename E = void>
struct arithmetic_binary_minus_functor;

// Specialization for floating-point types.
template <typename T>
struct arithmetic_binary_minus_functor<T, T, std::enable_if_t<std::is_floating_point<T>::value>>
{
	T operator()(T a, T b) const
	{ return a - b; }
};

template <typename A, typename E = void>
struct arithmetic_unary_plus_functor;

// Specialization for floating-point types.
template <typename T>
struct arithmetic_unary_plus_functor<T, std::enable_if_t<std::is_floating_point<T>::value>>
{
    T operator()(T a) const
    { return +a; }
};

template <typename A, typename E = void>
struct arithmetic_unary_minus_functor;

// Specialization for floating-point types.
template <typename T>
struct arithmetic_unary_minus_functor<T, std::enable_if_t<std::is_floating_point<T>::value>>
{
    T operator()(T a) const
    { return -a; }
};


template <typename A, typename B, typename E = void>
struct arithmetic_binary_equal_equal_functor;

// Specialization for floating-point types.
template <typename T>
struct arithmetic_binary_equal_equal_functor<T, T, std::enable_if_t<std::is_floating_point<T>::value>>
{
    bool operator()(T a, T b) const
    { return a == b; }
};

template <typename A, typename B>
auto operator*(const A& a, const B& b) -> decltype(arithmetic_binary_star_functor<A, B>()(a, b))
{
    return arithmetic_binary_star_functor<A, B>()(a, b);
}

template <typename A, typename B>
auto operator/(const A& a, const B& b) -> decltype(arithmetic_binary_slash_functor<A, B>()(a, b))
{
    return arithmetic_binary_slash_functor<A, B>()(a, b);
}

template <typename A, typename B>
auto operator+(const A& a, const B& b) -> decltype(arithmetic_binary_plus_functor<A, B>()(a, b))
{
    return arithmetic_binary_plus_functor<A, B>()(a, b);
}

template <typename A, typename B>
auto operator-(const A& a, const B& b) -> decltype(arithmetic_binary_minus_functor<A, B>()(a, b))
{
    return arithmetic_binary_minus_functor<A, B>()(a, b);
}

template <typename A>
auto operator+(const A& a) -> decltype(arithmetic_unary_plus_functor<A>()(a))
{
    return arithmetic_unary_plus_functor<A>()(a);
}

template <typename A>
auto operator-(const A& a) -> decltype(arithmetic_unary_minus_functor<A>()(a))
{
    return arithmetic_unary_minus_functor<A>()(a);
}

template <typename A, typename B>
auto operator==(const A& a, const B& b) -> decltype(arithmetic_binary_equal_equal_functor<A, B>()(a, b))
{
    return arithmetic_binary_equal_equal_functor<A, B>()(a, b);
}

template <typename A, typename B>
auto operator!=(const A& a, const B& b) -> decltype(!arithmetic_binary_equal_equal_functor<A, B>()(a, b))
{
    return !arithmetic_binary_equal_equal_functor<A, B>()(a, b);
}

} // namespace idlib
