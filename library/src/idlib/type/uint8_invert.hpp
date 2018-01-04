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

#include "idlib/type/invert.hpp"
#include "idlib/type/uint8_traits.hpp"

#include "idlib/type/internal/header.hpp"

/// @brief Invert an @a uint8_traits value.
template <>
struct invert<uint8_traits>
{
	using traits = uint8_traits;

    traits::underlying_type operator()(const traits::underlying_type& v) const
    {
		return traits::range().max() - v;
    }
}; // struct invert

#include "idlib/type/internal/footer.hpp"
