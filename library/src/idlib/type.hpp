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

/// @file idlib/type.hpp
/// @brief Master include file of the idlib type library.

#pragma once

#if !defined(IDLIB_PRIVATE) || IDLIB_PRIVATE != 1
#error(do not include directly, include `idlib/idlib.hpp` instead)
#endif

#include "idlib/type/clamped_single_traits.hpp"
#include "idlib/type/clamped_single_invert.hpp"
#include "idlib/type/clamped_single_scale.hpp"
#include "idlib/type/clamped_single_add.hpp"
#include "idlib/type/clamped_single_subtract.hpp"

#include "idlib/type/clamped_double_traits.hpp"
#include "idlib/type/clamped_double_invert.hpp"
#include "idlib/type/clamped_double_scale.hpp"
#include "idlib/type/clamped_double_add.hpp"
#include "idlib/type/clamped_double_subtract.hpp"

#include "idlib/type/uint8_traits.hpp"
#include "idlib/type/uint8_invert.hpp"
#include "idlib/type/uint8_scale.hpp"
#include "idlib/type/uint8_add.hpp"
#include "idlib/type/uint8_subtract.hpp"

#include "idlib/type/uint16_traits.hpp"
#include "idlib/type/uint16_invert.hpp"
#include "idlib/type/uint16_scale.hpp"
#include "idlib/type/uint16_add.hpp"
#include "idlib/type/uint16_subtract.hpp"

#include "idlib/type/uint32_traits.hpp"
#include "idlib/type/uint32_invert.hpp"
#include "idlib/type/uint32_scale.hpp"
#include "idlib/type/uint32_add.hpp"
#include "idlib/type/uint32_subtract.hpp"

#include "idlib/type/uint64_traits.hpp"
#include "idlib/type/uint64_invert.hpp"
#include "idlib/type/uint64_scale.hpp"
#include "idlib/type/uint64_add.hpp"
#include "idlib/type/uint64_subtract.hpp"

#include "idlib/type/convert.hpp"
