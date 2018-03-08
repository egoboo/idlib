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
#undef IDLIB_PRIVATE

#include "idlib/numeric.hpp"

template struct idlib::angle<single, idlib::degrees>;
template struct idlib::lineary_interpolate_functor<idlib::angle<single, idlib::degrees>, single>;
template struct idlib::angle<double, idlib::degrees>;
template struct idlib::lineary_interpolate_functor<idlib::angle<double, idlib::degrees>, double>;
template struct idlib::angle<quadruple, idlib::degrees>;
template struct idlib::lineary_interpolate_functor<idlib::angle<quadruple, idlib::degrees>, quadruple>;

template struct idlib::angle<single, idlib::radians>;
template struct idlib::lineary_interpolate_functor<idlib::angle<single, idlib::radians>, single>;
template struct idlib::angle<double, idlib::radians>;
template struct idlib::lineary_interpolate_functor<idlib::angle<double, idlib::radians>, double>;
template struct idlib::angle<quadruple, idlib::radians>;
template struct idlib::lineary_interpolate_functor<idlib::angle<quadruple, idlib::radians>, quadruple>;

template struct idlib::angle<single, idlib::turns>;
template struct idlib::lineary_interpolate_functor<idlib::angle<single, idlib::turns>, single>;
template struct idlib::angle<double, idlib::turns>;
template struct idlib::lineary_interpolate_functor<idlib::angle<double, idlib::turns>, double>;
template struct idlib::angle<quadruple, idlib::turns>;
template struct idlib::lineary_interpolate_functor<idlib::angle<quadruple, idlib::turns>, quadruple>;
