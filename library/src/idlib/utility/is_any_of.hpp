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

/// @file idlib/utility/is_any_of.hpp
/// @brief SFINAE utilities: test if a type is in a list of types.
/// @author Michael Heilmann

#pragma once

#include <type_traits>

#include "idlib/utility/header.in"

/// @brief
/// @code
/// id::is_any_of<T,A0,A1,..., An>::value
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
