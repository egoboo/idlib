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

/// @file idlib/idlib.hpp
/// @brief Master include file for idlib.
/// @author Michael Heilmann

#pragma once

#define IDLIB_PRIVATE 1

// CRTP.
#include "idlib/crtp.hpp"

// singleton.
#include "idlib/singleton.hpp"

// parsing expressions.
#include "idlib/parsing_expressions.hpp"

// Text utilities.
#include "idlib/text.hpp"

// Define __ID_CURRENT_FILE__, __ID_CURRENT_LINE__ and __ID_CURRENT_FUNCTION__.
// Those constants will either be properly defined or not at all.
#include "idlib/CurrentFunction.inline"

// Debug assertions.
#include "idlib/DebugAssert.hpp"

// event library.
#include "idlib/event.hpp"

// signal library.
#include "idlib/signal.hpp"

// color library.
#include "idlib/color.hpp"

// math library.
#include "idlib/math.hpp"

// type library.
#include "idlib/type.hpp"

// language library.
#include "idlib/language.hpp"

// file system library.
#include "idlib/file_system.hpp"

// utility library.
#include "idlib/utility.hpp"

// range library.
#include "idlib/range.hpp"

// iterator library.
#include "idlib/iterator.hpp"

#undef IDLIB_PRIVATE
