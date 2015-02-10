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

/// @file idlib/math/float.hpp
/// @brief Basic functionality for classifying and comparing floating point values.
/// @author Michael Heilmann

#pragma once

#include <type_traits>
#include <cmath>

namespace id {
	
/// @brief Get if a floating point value is not a number.
/// @param x the floating point value
/// @return @a true if the floating point value @a x is not a number, @a false otherwise
template<class T>
std::enable_if_t<std::is_floating_point<T>::value, bool>
is_not_a_number(T x)
{
	return (std::fpclassify(x) == FP_NAN);
}

/// @brief Get if a floating point value is positive infinity.
/// @param x the floating point value
/// @return @a true if the floating point value @a x is positive infinity, @a false otherwise
template<class T>
std::enable_if_t<std::is_floating_point<T>::value, bool>
is_positive_infinity(T x)
{
	return (x > 0 && std::fpclassify(x) == FP_INFINITE);
}

/// @brief Get if a floating point value is negative infinity.
/// @param x the floating point value
/// @return @a true if the floating point value @a x is negative infinity, @a false otherwise
template<class T>
std::enable_if_t<std::is_floating_point<T>::value, bool>
is_negative_infinity(T x)
{
	return (x < 0 && std::fpclassify(x) == FP_INFINITE);
}

/// @brief Get if a floating point value is infinity.
/// @param x the floating point value
/// @return @a true if the floating point value @a x is infinity, @a false otherwise
template<class T>
std::enable_if_t<std::is_floating_point<T>::value, bool>
is_infinity(T x)
{
	return (std::fpclassify(x) == FP_INFINITE);
}

/// @brief Get if a floating point value is bad.
/// @param x the floating point value
/// @return @a true if a the floating point value @a x is bad, @a false otherwise
/// @remark A floating point value is bad if its infinity or not a number.
template<class T>
std::enable_if_t<std::is_floating_point<T>::value, bool>
is_bad(T x)
{
	return is_infinity(x) || is_not_a_number(x);
}

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
	
} // namespace id
