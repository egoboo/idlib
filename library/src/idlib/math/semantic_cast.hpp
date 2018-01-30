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

namespace idlib {

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

} // namespace idlib
