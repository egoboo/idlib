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

/// @file idlib/non_copyable/non_copyable.hpp
/// @brief Make classes non-copyable.
/// @author Michael Heilmann

#pragma once

#if !defined(IDLIB_PRIVATE) || IDLIB_PRIVATE != 1
#error(do not include directly, include `idlib/non_copyable.hpp` instead)
#endif

#include "idlib/platform.hpp"

namespace idlib {

/// @brief Non-copyable mixing.
/// @details Inherit from this class to make the inheriting descendants non-copyable.
/// The descendants are non-copyable because the copy constructors and assignment operators are deleted.
/// The default constructor and the default destructor are in protected scope as they should only be accessed from descendants.
/// They are not private scope as private scope emits superfluous diagnostics.
/// @details Example usage
/// @code
/// class foo : public bar, private non_copyable
/// { ... }
/// @endcode
class non_copyable
{
protected:
    constexpr non_copyable() = default;
    ~non_copyable() = default;

public:
    non_copyable(const non_copyable&) = delete;
    non_copyable& operator=(const non_copyable&) = delete;

}; // class non_copyable

} // namespace idlib
