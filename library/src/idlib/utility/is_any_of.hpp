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

/// @file idlib/utility/is_any_of.hpp
/// @brief SFINAE utilities: test if a type is in a list of types.
/// @author Michael Heilmann

#pragma once

#include <type_traits>

#include "idlib/utility/header.in"

/// @brief
/// @code
/// idlib::is_any_of<T,A0,A1,..., An>::value
/// @endcode
/// is equivalent to
/// @code
/// std::is_same<T,A0>::value || std::is_same<T,A1>::value || ... || std::is_same<T,An>
/// @endcode
template<typename T, typename U, typename... Us>
struct is_any_of :
	std::integral_constant<bool,
		std::conditional<std::is_same<T, U>::value,
			std::true_type,
			is_any_of<T, Us...>
		>::type::value>
{};

template<typename T, typename U>
struct is_any_of<T, U> : std::is_same<T, U>::type
{};

template <typename T, typename ... U>
constexpr bool is_any_of_v = is_any_of<T, U ...>::value;

#include "idlib/utility/footer.in"
