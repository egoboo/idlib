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

public:
/// @brief The type of the red component.
using component_r = typename color_space_type::r::syntax::underlying_type;

private:
/// @brief The red component value.
/// @invariant Within the bounds of color_space_type::min() (inclusive) and color_space_type::max() (inclusive).
component_r r;

public:
/// @brief The type of the green component.
using component_g = typename color_space_type::g::syntax::underlying_type;

private:
/// @brief The green component value.
/// @invariant Within the bounds of color_space_type::min() (inclusive) and color_space_type::max() (inclusive).
component_g g;

public:
/// @brief The type of the blue component.
using component_b = typename color_space_type::b::syntax::underlying_type;

private:
/// @brief The blue component value.
/// @invariant Within the bounds of color_space::min() (inclusive) and color_space::max() (inclusive).
component_b b;
