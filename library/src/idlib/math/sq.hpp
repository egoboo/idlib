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

namespace id {
	
/// @brief Functor computing the square (NOT the square root).
/// @remark Specializations for @a single, @a double, and @a quadruple are provided.
/// @tparam T the type
/// @tparam E for SFINAE
template <typename T, typename E = void>
struct sq_functor;

template <typename T>
auto sq(const T& v)
{ return sq_functor<T, void>()(v); }

template <typename T>
struct sq_functor<T, std::enable_if_t<std::is_floating_point<T>::value>>
{
	T operator()(T x) const
	{ return x * x; }
}; // struct sq_functor

template <typename T>
struct sq_functor<T, std::enable_if_t<std::is_same<T, int>::value>>
{
	T operator()(T x) const
	{
		return x * x;
	}
}; // struct sq_functor

} // namespace id
