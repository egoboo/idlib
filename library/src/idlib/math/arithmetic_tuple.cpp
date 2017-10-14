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

#define IDLIB_PRIVATE 1
#include "idlib/math/arithmetic_tuple.hpp"
#include "idlib/math/floating_point.hpp"
#include "idlib/math/one_zero.hpp"
#undef IDLIB_PRIVATE

template struct id::arithmetic_tuple<single, 0, id::zero_functor<single>>;
template struct id::arithmetic_tuple<single, 1, id::zero_functor<single>>;
template struct id::arithmetic_tuple<single, 2, id::zero_functor<single>>;
template struct id::arithmetic_tuple<single, 3, id::zero_functor<single>>;
template struct id::arithmetic_tuple<single, 4, id::zero_functor<single>>;

template struct id::arithmetic_tuple<double, 0, id::zero_functor<double>>;
template struct id::arithmetic_tuple<double, 1, id::zero_functor<double>>;
template struct id::arithmetic_tuple<double, 2, id::zero_functor<double>>;
template struct id::arithmetic_tuple<double, 3, id::zero_functor<double>>;
template struct id::arithmetic_tuple<double, 4, id::zero_functor<double>>;
