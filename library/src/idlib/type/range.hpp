// Copyright Michael Heilmann 2016, 2017.
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
    /// @throw id::invalid_argument_exception @a min is greater than @a max
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
    { return id::clamp(value, min(), max()); }
    
}; // struct range

#include "idlib/type/internal/footer.hpp"
