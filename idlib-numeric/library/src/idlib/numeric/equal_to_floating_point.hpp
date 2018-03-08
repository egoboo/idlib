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

/// @file idlib/numeric/are_equal_floating_point.hpp
/// @brief Functionality to test if two floating point values are equal.
/// @author Michael Heilmann

#pragma once

#include <type_traits>
#include <cmath>

namespace idlib {

/// @ingroup numeric
/// @brief Enumerations of the outcome of an equality check for floating-point values.
enum class equality_check_result
{
    /// @brief The check did not determine wether the floating-point values are equal or not equal.
    undetermined,
    /// @brief The check determined that the floating-point values are equal.
    equal,
    /// @brief The check determined that the floating-point values are equal.
    not_equal,
};

/// @ingroup numeric
/// @brief Function which handles all cases of floating-point values comparison that are not "black
/// magic". If you are writing floating-point comparison code then always use this function before
/// your code. If it yields a meaningful result, then your code does not need to run.
/// @param x, y the floating point values
/// @return result::equal (result::not_equal) if @a x and @a y are determined to be equal (not equal).
///         result::undetermined is returned if this function has not determined wether @a x an @a y are equal or not equal.
/// @remark
/// The function returns result::equal if comparing @a and @a y using the the == operator  yields
/// logically @a true. Otherwise it proceeds and return result::not_equal if @a x and/or @a y are
/// /is NaN and. Otherwise it proceeds and returns result::undetermined.
template<class T>
typename std::enable_if_t<std::is_floating_point<T>::value, equality_check_result>
equal_to(T x, T y)
{
    if (x == y)
    { 
        return equality_check_result::equal;
    }
    if (std::isnan(x) || std::isnan(y))
    {
        return equality_check_result::not_equal;
    }
    return equality_check_result::undetermined;
}

} // namespace idlib
