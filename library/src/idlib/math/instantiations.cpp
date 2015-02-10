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
#include "idlib/math/dimensionality.hpp"
#include "idlib/math/interpolation_method.hpp"
#include "idlib/math/interpolate.hpp"
#include "idlib/math/interpolate_floating_point.hpp"
#include "idlib/math/mu.hpp"
#include "idlib/math/even_odd.hpp"
#include "idlib/math/one_zero.hpp"
#undef IDLIB_PRIVATE

template class id::mu<float>;
template class id::mu<double>;

template struct id::interpolate_functor<float,id::interpolation_method::LINEAR>;
template struct id::interpolate_functor<double, id::interpolation_method::LINEAR>;

template class id::zero_functor<float>;
template class id::zero_functor<double>;
template class id::zero_functor<short>;
template class id::zero_functor<int>;
template class id::zero_functor<long>;

template class id::one_functor<float>;
template class id::one_functor<double>;
