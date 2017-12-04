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
