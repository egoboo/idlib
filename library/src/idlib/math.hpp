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

/// @file idlib/math.hpp
/// @brief Master include file of the Idlib math library.
/// @author Michael Heilmann

#pragma once

#if !defined(IDLIB_PRIVATE) || IDLIB_PRIVATE != 1
#error(do not include directly, include `idlib/idlib.hpp` instead)
#endif

#include "idlib/math/traits.hpp"
#include "idlib/math/operators.hpp"
#include "idlib/math/float.hpp"
#include "idlib/math/dimensionality.hpp"
#include "idlib/math/interpolation_method.hpp"
#include "idlib/math/interpolate.hpp"
#include "idlib/math/interpolate_floating_point.hpp"
#include "idlib/math/mu.hpp"
#include "idlib/math/even_odd.hpp"
#include "idlib/math/one_zero.hpp"

#include "idlib/math/generator.hpp"
#include "idlib/math/constant_generator.hpp"
#include "idlib/math/conditional_generator.hpp"

#include "idlib/math/enclose.hpp"
#include "idlib/math/is_enclosing.hpp"
#include "idlib/math/is_intersecting.hpp"
#include "idlib/math/translate.hpp"
