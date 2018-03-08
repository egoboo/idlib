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

#if !defined(IDLIB_PRIVATE) || IDLIB_PRIVATE != 1
#error(do not include directly, include `idlib/numeric.hpp` instead)
#endif

namespace idlib {
	
/// @brief Functor computing the square root (NOT the square).
/// @remark Specializations for @a single, @a double, and @a quadruple are provided.
/// @tparam T the type
/// @tparam Enabled for SFINAE
template <typename T, typename Enabled = void>
struct sqrt_functor;

/// @brief The function corresponding to idlib::sqrt_functor.
template <typename T>
auto sqrt(const T& v)
{ return sq_functor<T>()(v); }

} // namespace idlib
