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

/// @file idlib/math/clamp.hpp
/// @brief Replacement for std::clamp until C++17 is fully supported.
/// Directly copied from http://en.cppreference.com/w/cpp/algorithm/clamp.
/// @author Michael Heilmann

#pragma once

#include "idlib/utility/platform.hpp"

namespace id {

template<class T, class Compare>
constexpr const T& clamp(const T& value, const T& low, const T& high, Compare compare)
{
    return assert(!compare(high, low)), compare(value, low) ? low : compare(high, value) ? high : value;
}
	
template<class T>
constexpr const T& clamp(const T& value, const T& low, const T& high)
{
	return id::clamp(value, low, high, std::less<T>());
}

} // namespace id
