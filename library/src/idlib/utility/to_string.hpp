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
