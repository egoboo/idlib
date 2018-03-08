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

/// @file idlib/numeric.hpp
/// @brief Master include file of the Idlib numeric library.
/// @author Michael Heilmann

#pragma once

#pragma push_macro("IDLIB_PRIVATE")
#undef IDLIB_PRIVATE
#define IDLIB_PRIVATE 1

#include "idlib/numeric/zero.hpp"
#include "idlib/numeric/zero_floating_point.hpp"
#include "idlib/numeric/zero_integer.hpp"

#include "idlib/numeric/one.hpp"
#include "idlib/numeric/one_floating_point.hpp"
#include "idlib/numeric/one_integer.hpp"

#include "idlib/numeric/interval.hpp"
#include "idlib/numeric/interval_floating_point.hpp"
#include "idlib/numeric/interval_integer.hpp"

#include "idlib/numeric/is_positive.hpp"
#include "idlib/numeric/is_positive_floating_point.hpp"
#include "idlib/numeric/is_positive_integer.hpp"

#include "idlib/numeric/is_negative.hpp"
#include "idlib/numeric/is_negative_floating_point.hpp"
#include "idlib/numeric/is_negative_integer.hpp"

#include "idlib/numeric/is_infinity_floating_point.hpp"
#include "idlib/numeric/is_negative_infinity_floating_point.hpp"
#include "idlib/numeric/is_positive_infinity_floating_point.hpp"
#include "idlib/numeric/is_not_a_number_floating_point.hpp"

#include "idlib/numeric/is_bad_floating_point.hpp"
#include "idlib/numeric/equal_to_floating_point.hpp"

#include "idlib/numeric/mu.hpp"
#include "idlib/numeric/mu_floating_point.hpp"

#include "idlib/numeric/interpolate.hpp"
#include "idlib/numeric/interpolate_floating_point.hpp"

#include "idlib/numeric/is_even.hpp"
#include "idlib/numeric/is_even_integer.hpp"

#include "idlib/numeric/is_odd.hpp"

#include "idlib/numeric/sq.hpp"
#include "idlib/numeric/sq_floating_point.hpp"
#include "idlib/numeric/sq_integer.hpp"

#include "idlib/numeric/sqrt.hpp"
#include "idlib/numeric/sqrt_floating_point.hpp"

#include "idlib/numeric/random.hpp"
#include "idlib/numeric/random_floating_point.hpp"
#include "idlib/numeric/random_integer.hpp"

#include "idlib/numeric/fraction.hpp"

#include "idlib/numeric/clamp.hpp"

#include "idlib/numeric/invert.hpp"

#undef IDLIB_PRIVATE
#pragma pop_macro("IDLIB_PRIVATE")
