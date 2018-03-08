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

/// @file idlib/numeric/mu.hpp
/// @brief Type representing of values within the bounds of idlib::zero and idlib::one.
/// @author Michael Heilmann

#pragma once

#if !defined(IDLIB_PRIVATE) || IDLIB_PRIVATE != 1
#error(do not include directly, include `idlib/numeric.hpp` instead)
#endif

namespace idlib {

/// @ingroup math
/// @brief Representation of \f$\mu\f$ (mu).
/// @detail The greek letter \f$\mu\f$ (mu) is the name for the interpolation parameter in interpolation.
/// @detail Objects of type @a mu are caches and contracts at the same time:
/// - they are caches as they store two values of which one is one minus the other value (cache)
/// - they guarantee that both values are within the bounds of \f$[0,1]\f$
/// @remark Specializations for @a float and @a double are provided.
/// @tparam T the value type. Must implement idlib::zero and idlib::one.
/// @tparam Enabled for SFINAE
template <typename T, typename Enabled = void>
struct mu;

} // namespace idlib
