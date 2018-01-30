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

#include "idlib/math/clamp.hpp"

#include "idlib/type/internal/header.hpp"

/// @brief A range.
template <typename Type>
struct range
{
public:
    /// @brief The type.
    using type = Type;

private:
    /// @brief The minimum value.
    type m_min;

    /// @brief The maximum value.
    type m_max;

public:
    /// @brief Construct this range.
    /// @param min the minimum value
    /// @param max the maximum value
    /// @throw idlib::invalid_argument_exception @a min is greater than @a max
    /// @todo Actually raise an exception.
    range(const type& min, const type& max) :
        m_min(min), m_max(max)
    {}

    /// @brief Get the minimum value.
    /// @return the minimum value
    const type& min() const
    { return m_min; }

    /// @brief Get the maximum value.
    /// @return the maximum value
    const type& max() const
    { return m_max; }

    /// @brief Get if a value is inside this range.
    /// @param value the value
    bool inside(const type& value) const
    { return min() <= value && value <= max(); }

    /// @brief Get if a value is outside this range.
    bool outside(const type& value) const
    { return min() > value || value > max();  }

    /// @brief Clamp a value to this range.
    /// @param value the value
    /// @return the clamped value
    const type& clamp(const type& value) const
    { return idlib::clamp(value, min(), max()); }
    
}; // struct range

#include "idlib/type/internal/footer.hpp"
