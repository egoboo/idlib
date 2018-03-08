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
#include "idlib/math/arithmetic_array_1d.hpp"
#undef IDLIB_PRIVATE

#include "idlib/numeric.hpp"

template struct idlib::arithmetic_array_1d<single, 0, idlib::zero_functor<single>>;
template struct idlib::arithmetic_array_1d<single, 1, idlib::zero_functor<single>>;
template struct idlib::arithmetic_array_1d<single, 2, idlib::zero_functor<single>>;
template struct idlib::arithmetic_array_1d<single, 3, idlib::zero_functor<single>>;
template struct idlib::arithmetic_array_1d<single, 4, idlib::zero_functor<single>>;

template struct idlib::arithmetic_array_1d<double, 0, idlib::zero_functor<double>>;
template struct idlib::arithmetic_array_1d<double, 1, idlib::zero_functor<double>>;
template struct idlib::arithmetic_array_1d<double, 2, idlib::zero_functor<double>>;
template struct idlib::arithmetic_array_1d<double, 3, idlib::zero_functor<double>>;
template struct idlib::arithmetic_array_1d<double, 4, idlib::zero_functor<double>>;
