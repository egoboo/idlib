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
#include "idlib/math/vector.hpp"
#include "idlib/math/floating_point.hpp"
#undef IDLIB_PRIVATE

template struct id::vector<single, 1>;
template struct id::vector<single, 2>;
template struct id::vector<single, 3>;
template struct id::vector<single, 4>;

template struct id::vector<double, 1>;
template struct id::vector<double, 2>;
template struct id::vector<double, 3>;
template struct id::vector<double, 4>;

template struct id::vector<quadruple, 1>;
template struct id::vector<quadruple, 2>;
template struct id::vector<quadruple, 3>;
template struct id::vector<quadruple, 4>;

template struct id::lineary_interpolate_functor<id::vector<single, 1>, single>;
template struct id::lineary_interpolate_functor<id::vector<single, 2>, single>;
template struct id::lineary_interpolate_functor<id::vector<single, 3>, single>;
template struct id::lineary_interpolate_functor<id::vector<single, 4>, single>;

template struct id::lineary_interpolate_functor<id::vector<double, 1>, double>;
template struct id::lineary_interpolate_functor<id::vector<double, 2>, double>;
template struct id::lineary_interpolate_functor<id::vector<double, 3>, double>;
template struct id::lineary_interpolate_functor<id::vector<double, 4>, double>;

template struct id::lineary_interpolate_functor<id::vector<quadruple, 1>, quadruple>;
template struct id::lineary_interpolate_functor<id::vector<quadruple, 2>, quadruple>;
template struct id::lineary_interpolate_functor<id::vector<quadruple, 3>, quadruple>;
template struct id::lineary_interpolate_functor<id::vector<quadruple, 4>, quadruple>;

template struct id::cross_product_functor<id::vector<single, 3>>;
template struct id::cross_product_functor<id::vector<double, 3>>;
template struct id::cross_product_functor<id::vector<quadruple, 3>>;

template struct id::dot_product_functor<id::vector<single, 1>>;
template struct id::dot_product_functor<id::vector<single, 2>>;
template struct id::dot_product_functor<id::vector<single, 3>>;
template struct id::dot_product_functor<id::vector<single, 4>>;

template struct id::dot_product_functor<id::vector<double, 1>>;
template struct id::dot_product_functor<id::vector<double, 2>>;
template struct id::dot_product_functor<id::vector<double, 3>>;
template struct id::dot_product_functor<id::vector<double, 4>>;

template struct id::dot_product_functor<id::vector<quadruple, 1>>;
template struct id::dot_product_functor<id::vector<quadruple, 2>>;
template struct id::dot_product_functor<id::vector<quadruple, 3>>;
template struct id::dot_product_functor<id::vector<quadruple, 4>>;
