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

/// @file idlib/DebugAssert.hpp
/// @brief Debug assertion functionality.
/// @author Michael Heilmann

#pragma once

#include "idlib/utility/assertion_failed_error.hpp"

/// @brief Macro raising an exception if an assertion fails.
/// @param assertion the assertion
/// @throw id::assertion_failed_error the assertion fails
/// @remark This macro evaluates to the empty statement if #_DEBUG is not defined.
#if defined(_DEBUG)
    #define ID_ASSERT(assertion) \
	    if(!(assertion)) { \
		    throw id::assertion_failed_error(__FILE__, __LINE__, #assertion); \
        }
#else
    #define ID_ASSERT(assertion) /* Empty statement. */;
#endif