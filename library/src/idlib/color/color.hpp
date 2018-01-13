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

/// @file idlib/color/Colour.hpp
/// @brief Colours.
/// @author Michael Heilmann

#pragma once

#if !defined(IDLIB_PRIVATE) || IDLIB_PRIVATE != 1
#error(do not include directly, include `idlib/idlib.hpp` instead)
#endif

#include "idlib/color/space.hpp"

/// If defined and @a 1, then colors allow for setting the component values.
#define ID_COLOR_SETTERS (1)

/// If defined and @a 1 and #ID_COLOR_SETTERS is defined and @a 1,
/// then short setters are provided.
/// For example, the setter setRed has the short setter setR.
#define ID_COLOR_SHORT_SETTERS (1)

/// If defined and @a 1 and #ID_COLOR_GETTERS is defined and @a 1,
/// then short getters are provided.
/// For example, the getter getRed has the short getter getR.
#define ID_COLOR_SHORT_GETTERS (1)

namespace id {

template <typename ColorSpace, typename Enabled = void>
struct color;

} // namespace id
