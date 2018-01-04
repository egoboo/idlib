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

#include "idlib/type/subtract.hpp"
#include "idlib/type/clamped_single_traits.hpp"

#include "idlib/type/internal/header.hpp"

/// @brief Subtract a @a clamped_single_traits values.
template <>
struct subtract<clamped_single_traits>
{
    using traits = clamped_single_traits;
    traits::underlying_type operator()(const traits::underlying_type& u, const traits::underlying_type& v) const
    {
        auto w = u - v;
        if (w < traits::range().min())
        {
            return traits::range().min();
        }
        return w;
    }
}; // struct subtract

#include "idlib/type/internal/footer.hpp"
