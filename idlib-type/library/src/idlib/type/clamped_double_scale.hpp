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

#include "idlib/type/scale.hpp"
#include "idlib/type/clamped_double_traits.hpp"

#include "idlib/type/internal/header.hpp"

/// @brief Scale an @a clamped_double_traits value.
template <>
struct scale<clamped_double_traits>
{
	using traits = clamped_double_traits;
    traits::underlying_type operator()(const traits::underlying_type& v, float s) const
    {
        return (*this)(v, double(s));
    }

    traits::underlying_type operator()(const traits::underlying_type& v, double s) const
    {
        static const auto& range = traits::range();
        auto u = v * s;
        return range.clamp(u);
    }
}; // struct scale

#include "idlib/type/internal/footer.hpp"
