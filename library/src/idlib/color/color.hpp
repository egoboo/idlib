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
