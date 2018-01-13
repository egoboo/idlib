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

#pragma once

#include "idlib/math/interval.hpp"

namespace id {

// Forward declaration.
struct rng_implementation;
	
/// @ingroup math
/// @brief Mersenne Twiser random number generator.
/// @remark This class is not copyable, only movable.
struct rng
{
	/// @brief Construct this random number generator.
	rng();
	/// @brief Destruct this random number generator.
	~rng();
	/// @brief Move-construct this random number generator.
	rng(rng&&);
	rng(const rng&) = delete; // not copyable

	/// @brief Move-assign this random number generator.
	rng& operator=(rng&&); // movable	
	rng& operator=(const rng&) = delete; // not copyable

	
	/// @{
    /// @brief Generate a random floating point value within the bounds of a floating point interval.
    /// @param interval the interval
    /// @return a random floating-point value within the bounds of <c>interval.lower()</c> (inclusive) and <c>interval.upper()</c> (inclusive)

    single next(const interval<single>& interval);

    double next(const interval<double>& interval);
	
	quadruple next(const interval<quadruple>& interval);
	
	/// @}
	
	/// @{
    /// @brief Generate a random integer within the bounds of a integer interval.
    /// @param interval the interval
    /// @return a random integer value within the bounds of <c>interval.lower()</c> (inclusive) and <c>interval.upper()</c> (inclusive)

	int next(const interval<int>& interval);
	
	/// @}
	
private:
	std::unique_ptr<rng_implementation> m_implementation;

}; // struct rng

/// @brief Functor generating a random value.
/// @tparam T the type of the value
template <typename T>
struct random_functor;

template <typename T, typename ... As>
auto random(As&& ... args) -> decltype(random_functor<T>()(std::forward<As>(args) ...))
{ return random_functor<T>()(std::forward<As>(args) ...); }

} // namespace id
