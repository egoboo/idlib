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

/// @file idlib/DebugAssert.hpp
/// @brief Debug assertion functionality.
/// @author Michael Heilmann

#pragma once

#include "idlib/utility/assertion_failed_error.hpp"

/// @brief Macro raising an exception if an assertion fails.
/// @param assertion the assertion
/// @throw idlib::assertion_failed_error the assertion fails
/// @remark This macro evaluates to the empty statement if #_DEBUG is not defined.
#if defined(_DEBUG)
    #define ID_ASSERT(assertion) \
	    if(!(assertion)) { \
		    throw idlib::assertion_failed_error(__FILE__, __LINE__, #assertion); \
        }
#else
    #define ID_ASSERT(assertion) /* Empty statement. */;
#endif