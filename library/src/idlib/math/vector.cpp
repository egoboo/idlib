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
