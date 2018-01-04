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
