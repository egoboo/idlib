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