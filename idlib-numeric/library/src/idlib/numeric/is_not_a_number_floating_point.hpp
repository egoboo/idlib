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

/// @file idlib/numeric/is_not_a_number_floating_point.hpp
/// @brief Functionality to determine if a floating point value is not a number.
/// @author Michael Heilmann

#pragma once

#include <type_traits>
#include <cmath>

namespace idlib {

/// @ingroup numeric
/// @brief Get if a floating point value is not a number.
/// @param x the floating point value
/// @return @a true if the floating point value @a x is not a number, @a false otherwise
template<class T>
std::enable_if_t<std::is_floating_point<T>::value, bool>
is_not_a_number(T x)
{ return (std::fpclassify(x) == FP_NAN); }

} // namespace idlib
