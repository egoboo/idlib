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
#include "idlib/math/one_zero.hpp"
//#include "idlib/math/floating_point.hpp"
//#include "idlib/utility/platform.hpp"
#undef IDLIB_PRIVATE

//
//template struct id::zero_functor<single>;
//template struct id::zero_functor<double>;
//template struct id::zero_functor<quadruple>;
template struct id::zero_functor<short>;
template struct id::zero_functor<int>;
template struct id::zero_functor<long>;

//
//template struct id::one_functor<single>;
//template struct id::one_functor<double>;
//template struct id::one_functor<quadruple>;
template struct id::one_functor<short>;
template struct id::one_functor<int>;
template struct id::one_functor<long>;
