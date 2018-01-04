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
