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

