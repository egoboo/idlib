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

/// @file idlib/language.hpp
/// @brief Master include file of the Idlib language library.
/// @author Michael Heilmann

#pragma once

#pragma push_macro("IDLIB_PRIVATE")
#if !defined(IDLIB_PRIVATE)
#define IDLIB_PRIVATE 1
#endif

#include "idlib/language/compilation_error.hpp"
#include "idlib/language/location.hpp"
#include "idlib/language/qualified_name.hpp"
#include "idlib/language/token.hpp"

#include "idlib/language/classify.hpp"
#include "idlib/language/decoder.hpp"
#include "idlib/language/encoder.hpp"

#include "idlib/language/decoder-boolean.hpp"
#include "idlib/language/decoder-character.hpp"
#include "idlib/language/decoder-integer.hpp"
#include "idlib/language/decoder-natural.hpp"
#include "idlib/language/decoder-real.hpp"
#include "idlib/language/decoder-string.hpp"
#include "idlib/language/encoders.hpp"

#undef IDLIB_PRIVATE
#pragma pop_macro("IDLIB_PRIVATE")

