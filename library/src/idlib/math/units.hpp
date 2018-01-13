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
