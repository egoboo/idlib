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

/// @file idlib/math/units.hpp
/// @brief Types denoting units
/// @author Michael Heilmann

#pragma once

namespace id {

/// @brief Type of a unit in which angles are measured.
/// Denotes the unit "degree" with its canonical range of \f$[0, 360)\f$.
/// If \f$x\f$ is an angle in degrees then
/// - \f$x \cdot \frac{1}{360}\f$ is the equivalent angle in turns and
/// - \f$x \cdot \frac{2\pi}{360}\f$ is the equivalent angle in radians.
struct degrees
{};

/// @brief Type of a unit in which angles are measured.
/// Denotes the unit "radian" with its canonical range of \f$[0, 2\pi)\f$.
/// If \f$x\f$ is an angle in radians then
/// - \f$x \cdot \frac{1}{2\pi}\f$ is the equivalent angle in turns and
/// - \f$x \cdot \frac{360}{2\pi}\f$ is the equivalent angle in degrees.
struct radians
{};

/// @brief Type of a unit in which angles are measured.
/// Denotes the unit "turn" with its canonical range of \f$[0,1)\f$.
/// Let \f$x\f$ be an angle in turns then
/// - \f$x \cdot 360\f$   is the equivalent angle in degrees and
/// - \f$x \cdot 2\pi\f$  is the equivalent angle in radians.
struct turns
{};

/// @brief Type of a unit in which angles are measured.
/// Denotes the unit "facing" with its canonical range of \f$[0,N)\f$ where \f$N\f$ is the maximum value of an underlying unsigned integer type \f$T\f$.
/// Let \f$x\f$ be an angle in facings then \f$x/M\f$ is the equivalent angle in turns. 
struct facings
{};

} // namespace id
