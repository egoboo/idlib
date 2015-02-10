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

/// @file idlib/utility/to_string.hpp
/// @brief Functor for converting values to strings.
/// @author Michael Heilmann

#pragma once

#include "idlib/utility/is_any_of.hpp"

#include "idlib/utility/header.in"

/// @brief Functor for converting a value to a string.
/// @tparam Type the type
/// @tparam Enabled for SFINAE
template <typename Type, typename Enabled = void>
struct to_string;

template <typename Type>
struct to_string<Type, std::enable_if_t<is_any_of<Type, int, long, long long, unsigned int, unsigned long, unsigned long long, float, double, long double>::value>>
{
	using type = Type;
	std::string operator()(const type& value) const
	{
		return std::to_string(value);
	}
}; // struct to_string

#include "idlib/utility/footer.in"
