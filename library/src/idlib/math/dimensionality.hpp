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

#pragma once

#include <cstddef>

namespace id {

/// @brief Test whether @a N fulfils the <em>dimensionality concept</em>.
/// Provides the member constant value which is equal to @a true, if @a N
/// fulfils the <em>dimensionality concept</em>.
/// Otherwise @a value is equal to @a false.
/// @tparam N the value to test
template <size_t N>
struct is_dimensionality
{
	static constexpr bool value = true;
	
	constexpr operator bool() const
	{
		return value;
	}
};

template <>
struct is_dimensionality<0>
{
	static constexpr bool value = false;
	
	constexpr operator bool() const
	{
		return value;
	}
};

/// @code
/// template<size_t N>
/// constexpr bool is_dimensionality_v = is_dimensionality<N>::value;
/// @endcode
template<size_t N>
constexpr bool is_dimensionality_v = is_dimensionality<N>::value;

} // namespace id