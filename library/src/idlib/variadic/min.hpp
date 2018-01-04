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

namespace id { namespace variadic { 

namespace detail {

// case
template <class A>
constexpr A const &min(A const &a)
{ return a; }
  
// variadic inductive case
template <class A, class...As> // requires SameType<A, As...>
constexpr A const &min(A const &a0, A const &a1, As const &...as)
{ return min(a0 < a1 ? a0 : a1, as...); }

} // namespace detail

// public interface
template <class A, class...As> // requires SameType<A, As...>
inline constexpr A const &min(A const &a, As const &...as)
{ return detail::min(a, as...); }

} } // namespace id::variadic
