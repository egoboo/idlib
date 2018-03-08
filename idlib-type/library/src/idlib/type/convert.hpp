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

#include "idlib/type/clamped_single_traits.hpp"
#include "idlib/type/clamped_double_traits.hpp"
#include "idlib/type/uint8_traits.hpp"
#include "idlib/type/uint16_traits.hpp"
#include "idlib/type/uint32_traits.hpp"
#include "idlib/type/uint64_traits.hpp"

#include "idlib/type/internal/header.hpp"

template <typename Target, typename Source>
struct convert;

/// @name uint8 <-> clamped_single
/// @{

/// @brief Convert an @a uint8 value a @a clamped_single value.
template <>
struct convert<clamped_single_traits, uint8_traits>
{
    clamped_single_traits::underlying_type operator()(const uint8_traits::underlying_type& source) const
    {
        return std::max(std::min(clamped_single_traits::underlying_type(source) * 255.0f, 1.0f), 0.0f);
    }
};

/// @brief Convert an @a clamped_single value to a @a uint8 value.
template <>
struct convert<uint8_traits, clamped_single_traits>
{
    uint8_traits::underlying_type operator()(const clamped_single_traits::underlying_type& source) const
    {
        assert(0.0f <= source && source <= 1.0f);
        // Multiply y by 256.0f. This ensures that numbers very
        // close to 1.0f (e.g. 0.999f) are not mapped to 254 but
        // to 255 as desired. As a consequence, however, the case
        // in which y is really 1.0f must be handled separatedly.
        return static_cast<uint8_traits::underlying_type>(std::floor(source == 1.0f ? 255.0f : source * 256.0f));
    }
};

/// @}

/// @name uint8 <-> clamped_double
/// @{

/// @brief Convert an @a uint8 value a @a clamped_double value.
template <>
struct convert<clamped_double_traits, uint8_traits>
{
    clamped_double_traits::underlying_type operator()(const uint8_traits::underlying_type& source) const
    {
        return std::max(std::min(clamped_double_traits::underlying_type(source) * 255.0, 1.0), 0.0);
    }
};

/// @brief Convet an @a clamped_double value to a @a uint8 value.
template <>
struct convert<uint8_traits, clamped_double_traits>
{
    uint8_traits::underlying_type operator()(const clamped_double_traits::underlying_type& source) const
    {
        assert(0 <= source && source <= 1.0);
        // Multiply y by 256.0. This ensures that numbers very
        // close to 1.0 (e.g. 0.999) are not mapped to 254 but to
        // 255 as desired. As a consequence, however, the case in which
        // y is really 1.0f must be handled separatedly.
        return static_cast<uint8_traits::underlying_type>(std::floor(source == 1.0 ? 255.0 : source * 256.0));
    }
};

/// @}

#include "idlib/type/internal/footer.hpp"
