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

#pragma once

#if !defined(IDLIB_PRIVATE) || IDLIB_PRIVATE != 1
#error(do not include directly, include `idlib/idlib.hpp` instead)
#endif

#include "idlib/type/range.hpp"

#include "idlib/type/internal/header.hpp"

/// @brief An IEEE-754 single precision floating-point value clamped to the bounds of 0 (inclusive) and 1 (inclusive).
struct clamped_single_traits
{
    /// @brief The underlying type.
    using underlying_type = float;
    /// @brief Get the range.
    /// @return the range
    static const idlib::type::range<underlying_type>& range()
    {
        static const idlib::type::range<underlying_type> r(0.0f, 1.0f);
        return r;
    }
}; // struct clamped_single_traits

#include "idlib/type/internal/footer.hpp"
