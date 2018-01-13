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

/// @file idlib/utility/non_copyable.hpp
/// @brief Make classes non-copyable.
/// @author Michael Heilmann

#pragma once

#if !defined(IDLIB_PRIVATE) || IDLIB_PRIVATE != 1
#error(do not include directly, include `idlib/idlib.hpp` instead)
#endif

#include "idlib/utility/header.in"

/// @brief Non-copyable mixing.
/// @detail Inherit from this class to make the inheriting descendant classes non-copyable.
/// The descendants are non-copyable because the copy constructors and assignment operators are deleted.
/// @detail Example usage
/// @code
/// class foo : public bar, private non_copyable
/// { ... }
/// @endcode
class non_copyable
{
protected:
	non_copyable() = default;
	~non_copyable() = default;
public:
    non_copyable(const non_copyable&) = delete;
    non_copyable& operator=(const non_copyable&) = delete;
}; // class non_copyable

#include "idlib/utility/footer.in"
