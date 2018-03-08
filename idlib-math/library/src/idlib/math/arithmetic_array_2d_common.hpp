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

#include "idlib/platform.hpp"

namespace idlib {
	
/// @tparam Element the element type
/// @tparam Width the width of the array
/// @tparam Height the height of the array
/// @tparam Zero type of a functor type returning the zero element value
/// @tparam Enabled for SFINAE
template <typename Element,
          size_t Width,
		  size_t Height,
		  typename Zero,
		  typename Enabled = void>
struct arithmetic_array_2d;

} // namespace idlib
