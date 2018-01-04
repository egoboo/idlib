// Copyright Michael Heilmann 2016, 2017, 2018.
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

#include "idlib/math/random.hpp"
#include "idlib/math/one_zero.hpp"

namespace id {
	
namespace internal {

template <typename T>
struct floating_point_random_functor
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
}; // struct floating_point_random_functor

template <typename T>
const interval<T> floating_point_random_functor<T>::DEFAULT_INTERVAL(zero<T>(), one<T>());
	
} // namespace internal

/// @internal
template <>
struct random_functor<single> : public internal::floating_point_random_functor<single>
{};

/// @internal
template <>
struct random_functor<double> : public internal::floating_point_random_functor<double>
{};

/// @internal
template <>
struct random_functor<quadruple> : public internal::floating_point_random_functor<quadruple>
{};

} // namespace id
