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
    static const id::type::range<underlying_type>& range()
    {
        static const id::type::range<underlying_type> r(0.0f, 1.0f);
        return r;
    }
}; // struct clamped_single_traits

#include "idlib/type/internal/footer.hpp"
