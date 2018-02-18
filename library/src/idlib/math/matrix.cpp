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
#include "idlib/math/matrix.hpp"
#include "idlib/math/floating_point.hpp"
#include "idlib/math/one_zero.hpp"
#undef IDLIB_PRIVATE


template struct idlib::matrix<single, 3, 3>;
template struct idlib::matrix<single, 4, 4>;
/*
template struct idlib::arithmetic_array_2d<single, 0, 1, idlib::zero_functor<single>>;
template struct idlib::arithmetic_array_2d<single, 0, 2, idlib::zero_functor<single>>;
template struct idlib::arithmetic_array_2d<single, 0, 3, idlib::zero_functor<single>>;
template struct idlib::arithmetic_array_2d<single, 0, 4, idlib::zero_functor<single>>;

template struct idlib::arithmetic_array_2d<single, 1, 0, idlib::zero_functor<single>>;
template struct idlib::arithmetic_array_2d<single, 1, 1, idlib::zero_functor<single>>;
template struct idlib::arithmetic_array_2d<single, 1, 2, idlib::zero_functor<single>>;
template struct idlib::arithmetic_array_2d<single, 1, 3, idlib::zero_functor<single>>;
template struct idlib::arithmetic_array_2d<single, 1, 4, idlib::zero_functor<single>>;

template struct idlib::arithmetic_array_2d<single, 2, 0, idlib::zero_functor<single>>;
template struct idlib::arithmetic_array_2d<single, 2, 1, idlib::zero_functor<single>>;
template struct idlib::arithmetic_array_2d<single, 2, 2, idlib::zero_functor<single>>;
template struct idlib::arithmetic_array_2d<single, 2, 3, idlib::zero_functor<single>>;
template struct idlib::arithmetic_array_2d<single, 2, 4, idlib::zero_functor<single>>;

template struct idlib::arithmetic_array_2d<single, 3, 0, idlib::zero_functor<single>>;
template struct idlib::arithmetic_array_2d<single, 3, 1, idlib::zero_functor<single>>;
template struct idlib::arithmetic_array_2d<single, 3, 2, idlib::zero_functor<single>>;
template struct idlib::arithmetic_array_2d<single, 3, 3, idlib::zero_functor<single>>;
template struct idlib::arithmetic_array_2d<single, 3, 4, idlib::zero_functor<single>>;

template struct idlib::arithmetic_array_2d<single, 4, 0, idlib::zero_functor<single>>;
template struct idlib::arithmetic_array_2d<single, 4, 1, idlib::zero_functor<single>>;
template struct idlib::arithmetic_array_2d<single, 4, 2, idlib::zero_functor<single>>;
template struct idlib::arithmetic_array_2d<single, 4, 3, idlib::zero_functor<single>>;
template struct idlib::arithmetic_array_2d<single, 4, 4, idlib::zero_functor<single>>;


template struct idlib::arithmetic_array_2d<double, 0, 0, idlib::zero_functor<double>>;
template struct idlib::arithmetic_array_2d<double, 0, 1, idlib::zero_functor<double>>;
template struct idlib::arithmetic_array_2d<double, 0, 2, idlib::zero_functor<double>>;
template struct idlib::arithmetic_array_2d<double, 0, 3, idlib::zero_functor<double>>;
template struct idlib::arithmetic_array_2d<double, 0, 4, idlib::zero_functor<double>>;

template struct idlib::arithmetic_array_2d<double, 1, 0, idlib::zero_functor<double>>;
template struct idlib::arithmetic_array_2d<double, 1, 1, idlib::zero_functor<double>>;
template struct idlib::arithmetic_array_2d<double, 1, 2, idlib::zero_functor<double>>;
template struct idlib::arithmetic_array_2d<double, 1, 3, idlib::zero_functor<double>>;
template struct idlib::arithmetic_array_2d<double, 1, 4, idlib::zero_functor<double>>;

template struct idlib::arithmetic_array_2d<double, 2, 0, idlib::zero_functor<double>>;
template struct idlib::arithmetic_array_2d<double, 2, 1, idlib::zero_functor<double>>;
template struct idlib::arithmetic_array_2d<double, 2, 2, idlib::zero_functor<double>>;
template struct idlib::arithmetic_array_2d<double, 2, 3, idlib::zero_functor<double>>;
template struct idlib::arithmetic_array_2d<double, 2, 4, idlib::zero_functor<double>>;

template struct idlib::arithmetic_array_2d<double, 3, 0, idlib::zero_functor<double>>;
template struct idlib::arithmetic_array_2d<double, 3, 1, idlib::zero_functor<double>>;
template struct idlib::arithmetic_array_2d<double, 3, 2, idlib::zero_functor<double>>;
template struct idlib::arithmetic_array_2d<double, 3, 3, idlib::zero_functor<double>>;
template struct idlib::arithmetic_array_2d<double, 3, 4, idlib::zero_functor<double>>;

template struct idlib::arithmetic_array_2d<double, 4, 0, idlib::zero_functor<double>>;
template struct idlib::arithmetic_array_2d<double, 4, 1, idlib::zero_functor<double>>;
template struct idlib::arithmetic_array_2d<double, 4, 2, idlib::zero_functor<double>>;
template struct idlib::arithmetic_array_2d<double, 4, 3, idlib::zero_functor<double>>;
template struct idlib::arithmetic_array_2d<double, 4, 4, idlib::zero_functor<double>>;
*/