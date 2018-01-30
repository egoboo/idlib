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

namespace idlib { namespace variadic { 

namespace detail {

// base case
template <class A>
constexpr A const &max(A const &a)
{ return a; }
  
// inductive case
template <class A, class...As> // requires SameType<A, As...>
constexpr A const &max(A const &a0, A const &a1, As const &...as)
{ return max(a0 > a1 ? a0 : a1, as...); }

} // namespace detail

// public interface
template <class A, class...As> // requires SameType<A, As...>
inline constexpr A const &max(A const &a, As const &... as)
{ return detail::max(a, as...); }

} } // namespace idlib::variadic
