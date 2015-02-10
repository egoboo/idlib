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

/// @file id/math/interpolate.hpp
/// @brief Functionality to interpolate between values.
/// @author Michael Heilmann

#pragma once

#include "idlib/math/interpolation_method.hpp"
#include "idlib/math/mu.hpp"
#include "idlib/math/one_zero.hpp"

namespace id {

/// @brief Functor which interpolates between values.
/// @tparam T the type of the values to interpolate between
/// @tparam M the interpolation method
/// @tparam E for SFINAE
template <typename T, interpolation_method M, typename E = void>
struct interpolate_functor;

} // namespace id
