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

namespace id {

/// @tparam T the target typedef
/// @tparam S the source typedef
/// @tparam E for SFINAE
template <typename T, typename S, typename E = void>
struct semantic_cast_functor {};

/// @brief Default implementation for identity conversion.
/// @tparam T the source and the target type
template <typename T>
struct semantic_cast_functor<T, T, void>
{
	auto operator()(const T& v) const
	{ return v; }
}; // struct semantic_cast_functor

template <typename T, typename S>
auto semantic_cast(const S& s)
{ return semantic_cast_functor<T, S, void>()(s); }

} // namespace id
