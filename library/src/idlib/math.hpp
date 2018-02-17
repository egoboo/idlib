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

/// @file idlib/math.hpp
/// @brief Master include file of the Idlib math library.
/// @author Michael Heilmann

#pragma once

#pragma push_macro("IDLIB_PRIVATE")
#undef IDLIB_PRIVATE
#define IDLIB_PRIVATE 1

#include "idlib/math/arithmetic_array_1d.hpp"
#include "idlib/math/arithmetic_array_2d.hpp"
#include "idlib/math/arithmetic_functor.hpp"

#include "idlib/math/angle.hpp"
#include "idlib/math/angle-degrees-radians-turns.hpp"

#include "idlib/math/sq.hpp"
#include "idlib/math/sqrt.hpp"

#include "idlib/math/semantic_cast.hpp"

#include "idlib/math/geometry/include.hpp"

#include "idlib/math/floating_point.hpp"
#include "idlib/math/floating_point_random.hpp"
#include "idlib/math/integer_random.hpp"

#include "idlib/math/operators.hpp"
#include "idlib/math/dimensionality.hpp"
#include "idlib/math/units.hpp"
#include "idlib/math/fraction.hpp"
#include "idlib/math/interpolate.hpp"

#include "idlib/math/mu.hpp"
#include "idlib/math/even_odd.hpp"
#include "idlib/math/one_zero.hpp"

#include "idlib/math/random.hpp"

#include "idlib/math/generator.hpp"
#include "idlib/math/constant_generator.hpp"
#include "idlib/math/conditional_generator.hpp"

#include "idlib/math/enclose.hpp"
#include "idlib/math/is_enclosing.hpp"
#include "idlib/math/is_intersecting.hpp"
#include "idlib/math/translate.hpp"

#include "idlib/math/point.hpp"
#include "idlib/math/vector.hpp"

#pragma pop_macro("IDLIB_PRIVATE")
