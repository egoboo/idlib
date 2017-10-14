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

/// @file idlib/math/angle.hpp
/// @brief Angles.
/// @author Michael Heilmann

#pragma once

namespace id {

/// @tparam Syntax the type of the syntax (what values represent angles)
/// @tparam Semantics the type of the semantics (how are the values interpreted)
/// @tparam Enabled for SFINAE
template <typename Syntax, typename Semantics, typename Enabled = void>
struct angle;

} // namespace id
