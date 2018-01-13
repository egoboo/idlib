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

/// @brief A 64 bit, unsigned, 2's complement binary integer.
struct uint64_traits
{
    /// @brief The underlying type.
    using underlying_type = uint64_t;
    /// @brief Get the range.
    /// @return the range
    static const id::type::range<underlying_type>& range()
    {
        static const id::type::range<underlying_type> r(std::numeric_limits<underlying_type>::min(),
                                                        std::numeric_limits<underlying_type>::max());
        return r;
    }
}; // struct uint64_traits

#include "idlib/type/internal/footer.hpp"
