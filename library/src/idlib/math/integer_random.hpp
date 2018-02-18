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

#include "idlib/math/random.hpp"
#include "idlib/math/one_zero.hpp"

namespace idlib {
	
namespace internal {

template <typename T>
struct integer_random_functor
{
    static const interval<T> DEFAULT_INTERVAL;

    T operator()() const
    { return (*this)(DEFAULT_INTERVAL); }

    T operator()(const interval<T>& i) const
    { rng t; return (*this)(&t, i); }

    T operator()(rng *rng) const
    { return (*this)(rng, DEFAULT_INTERVAL); }

    T operator()(rng *rng, const interval<T>& i) const
    { return rng->next(i); }
}; // struct integer_random_functor

template <typename T>
const interval<T> integer_random_functor<T>::DEFAULT_INTERVAL(zero<T>(), one<T>());
	
} // namespace internal

/// @internal
template <>
struct random_functor<int, void> : public internal::integer_random_functor<int>
{};

/// @internal
template <>
struct random_functor<long, void> : public internal::integer_random_functor<long>
{};

/// @internal
template <>
struct random_functor<long long, void> : public internal::integer_random_functor<long long>
{};

} // namespace idlib
