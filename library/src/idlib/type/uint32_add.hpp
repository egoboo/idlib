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

#if !defined(IDLIB_PRIVATE) || IDLIB_PRIVATE != 1
#error(do not include directly, include `idlib/idlib.hpp` instead)
#endif

#include "idlib/type/add.hpp"
#include "idlib/type/uint32_traits.hpp"

#include "idlib/type/internal/header.hpp"

/// @brief Add @a uint32_traits values.
template <>
struct add<uint32_traits>
{
	using traits = uint32_traits;

    traits::underlying_type operator()(const traits::underlying_type& u, const traits::underlying_type& v) const
    {
		if (traits::range().max() - v < u)
		{
			// max - v < u iff max < u + v implies overflow.
			// overflow shall clamp to max.
			return traits::range().max();
		}
		return u + v;
    }
}; // struct add

#include "idlib/type/internal/footer.hpp"
