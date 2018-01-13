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

/// @file idlib/math/angle-degrees-radians-turns.cpp
/// @brief Implementation of floating-point angles in degrees/radians/turns.
/// @author Michael Heilmann

#define IDLIB_PRIVATE 1
#include "idlib/math/angle-degrees-radians-turns.hpp"
#include "idlib/math/floating_point.hpp"
#undef IDLIB_PRIVATE

template struct id::angle<single, id::degrees>;
template struct id::lineary_interpolate_functor<id::angle<single, id::degrees>, single>;
template struct id::angle<double, id::degrees>;
template struct id::lineary_interpolate_functor<id::angle<double, id::degrees>, double>;
template struct id::angle<quadruple, id::degrees>;
template struct id::lineary_interpolate_functor<id::angle<quadruple, id::degrees>, quadruple>;

template struct id::angle<single, id::radians>;
template struct id::lineary_interpolate_functor<id::angle<single, id::radians>, single>;
template struct id::angle<double, id::radians>;
template struct id::lineary_interpolate_functor<id::angle<double, id::radians>, double>;
template struct id::angle<quadruple, id::radians>;
template struct id::lineary_interpolate_functor<id::angle<quadruple, id::radians>, quadruple>;

template struct id::angle<single, id::turns>;
template struct id::lineary_interpolate_functor<id::angle<single, id::turns>, single>;
template struct id::angle<double, id::turns>;
template struct id::lineary_interpolate_functor<id::angle<double, id::turns>, double>;
template struct id::angle<quadruple, id::turns>;
template struct id::lineary_interpolate_functor<id::angle<quadruple, id::turns>, quadruple>;
